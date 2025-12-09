#include "PCGPointContent.h" 


//int32 APCGPointContent::TotalPointDataPoints = 0;
//int32 APCGPointContent::ExpectedTotalPoints = 0;
//FDateTime APCGPointContent::StartTime = FDateTime::UtcNow();
//bool APCGPointContent::bTimerStarted = false;
bool APCGPointContent::bGlobalMeshesInitialized = false;
TMap<FString, UStaticMesh*> APCGPointContent::GlobalMeshesPerType;
//TMap<FString, UInstancedStaticMeshComponent*> APCGPointContent::GlobalInstancedMeshMap;
//TWeakObjectPtr<AActor> APCGPointContent::GlobalParentActor = nullptr;


APCGPointContent::APCGPointContent()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 3.0f;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	CullByCategory.Add(EVegetationCategory::Tree, FCullRange(0, 1200000));
	CullByCategory.Add(EVegetationCategory::Shrub, FCullRange(0, 120000));
	CullByCategory.Add(EVegetationCategory::Bushes, FCullRange(0, 120000));
	CullByCategory.Add(EVegetationCategory::RockPile, FCullRange(0, 120000));

}

void APCGPointContent::BeginPlay() {
	Super::BeginPlay();
}

//function to check whether the indices are created in the table or not
void APCGPointContent::EnsurePointsDataSpatialIndices()
{
	if (DBSubsystem->IsOpen()) {
		DBSubsystem->Execute(TEXT("CREATE INDEX IF NOT EXISTS idx_PointsData_Shapefile ON PointsData(ShapefileID)"));
		DBSubsystem->Execute(TEXT("CREATE INDEX IF NOT EXISTS idx_PointsData_Lat_Lon ON PointsData(Latitude, Longitude)"));
		DBSubsystem->Execute(TEXT("CREATE INDEX IF NOT EXISTS idx_PointsData_Tile ON PointsData(TileX, TileY)"));
	}
}

// Get mesh for a specific name on game thread.
UStaticMesh* APCGPointContent::GetOrLoadMeshForType_GameThread(const FString& CleanedName)
{
	if (!BlueprintRegistry) return nullptr;

	if (UStaticMesh* Existing = StaticMeshesPerType.FindRef(CleanedName))
	{
		return Existing;
	}

	// Find the matching blueprint once
	//TSubclassOf<AActor> MatchedBPClass = nullptr;
	//for (const TSoftClassPtr<AActor>& SoftBP : BlueprintRegistry->BlueprintClasses)
	//{
	//    FString AssetName = SoftBP.GetAssetName().ToLower();
	//    AssetName.RemoveFromEnd(TEXT("_c"));
	//    if (AssetName.Equals(TEXT("pd_") + CleanedName))
	//    {
	//        MatchedBPClass = SoftBP.LoadSynchronous(); 
	//        break;
	//    }
	//}

	//if (!MatchedBPClass)
	//{
	//    UE_LOG(LogTemp, Error, TEXT("No blueprint found in registry for model: %s"), *CleanedName);
	//    return nullptr;
	//}

	PreWarmMeshesFromRegistry(GetWorld(), BlueprintRegistry);

	// Extract one static mesh from the BP and cache it
	//UStaticMesh* Mesh = ExtractMeshFromBlueprint(MatchedBPClass); 
	//if (!Mesh)
	//{
	//    UE_LOG(LogTemp, Error, TEXT("No mesh extracted from blueprint: %s"), *CleanedName);
	//    return nullptr;
	//}
	if (UStaticMesh* const* FoundMesh = GlobalMeshesPerType.Find(CleanedName)) {
		UStaticMesh* Mesh = *FoundMesh;
		StaticMeshesPerType.Add(CleanedName, Mesh);
		return Mesh;
	}

	//StaticMeshesPerType.Add(CleanedName, Mesh);
	return nullptr;
}

// Get or create an HISM for a the nbme + Mesh 
UInstancedStaticMeshComponent* APCGPointContent::GetOrCreateHISM_GameThread(const FString& CleanedName, UStaticMesh* Mesh)
{
	if (!Mesh) return nullptr;

	UInstancedStaticMeshComponent* HISM = nullptr;
	if (UInstancedStaticMeshComponent** Found = InstancedMeshMap.Find(CleanedName))
	{
		HISM = *Found;
	}

	else {
		const EVegetationCategory Category = GetCategoryForModel(CleanedName);
		const FCullRange* Range = CullByCategory.Find(Category);

		HISM = NewObject<UInstancedStaticMeshComponent>(this);
		HISM->SetStaticMesh(Mesh);
		HISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		HISM->SetMobility(EComponentMobility::Movable);
		HISM->SetCanEverAffectNavigation(false);
		HISM->SetCullDistances(0, 800000); //8km
		//HISM->LDMaxDrawDistance = 500000.0f;
		HISM->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		HISM->RegisterComponent();
		AddInstanceComponent(HISM);

		InstancedMeshMap.Add(CleanedName, HISM);

	}



	return HISM;
}

//Initialize Content for Point Data
void APCGPointContent::InitializeContent()
{
	CesiumGeoreference = ACesiumGeoreference::GetDefaultGeoreference(GetWorld());
	Tileset = Cast<ACesium3DTileset>(UGameplayStatics::GetActorOfClass(GetWorld(), ACesium3DTileset::StaticClass()));

	const FString RegistryPath = TEXT("/Game/PCGData/PointDataAssets/BP_Registry.BP_Registry");


	UBlueprintRegistery* LoadedRegistry = Cast<UBlueprintRegistery>(
		StaticLoadObject(UBlueprintRegistery::StaticClass(), nullptr, *RegistryPath)
	);


	if (LoadedRegistry)
	{
		BlueprintRegistry = LoadedRegistry;
		UE_LOG(LogTemp, Warning, TEXT("Successfully loaded BP_Registry asset."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load BP_Registry from path: %s"), *RegistryPath);
	}

	GI = GetWorld() ? GetWorld()->GetGameInstance() : nullptr;
	DBSubsystem = GI->GetSubsystem<UPcgSQLiteSubsystem>();
	EnsurePointsDataSpatialIndices();
}

// Function to check if lat/long is valid or not
inline bool IsValidLonLat(float LongDeg, float LatDeg) {
	if (!FMath::IsFinite(LongDeg) || !FMath::IsFinite(LatDeg))
		return false;
	if (LongDeg < -180.0f || LongDeg> 180.0f)
		return false;
	if (LatDeg < -90.0f || LatDeg > 90.0f)
		return false;

	return true;

}

//First Pipeline: Populate Shape file raw data in the List structure
void APCGPointContent::InitializePCGPointData(const FShapeRawData& Raw)
{
	InitializeContent();
	for (int32 i = 0; i < Raw.Attributes.Num(); ++i)
	{

		const auto& A = Raw.Attributes[i];
		auto GetSafeString = [&](const FString& key) ->FString {
			return A.Contains(key) ? A[key] : TEXT("");
			};

		auto GetSafeInt = [&](const FString& key) -> int32 {
			return A.Contains(key) ? FCString::Atoi(*A[key]) : 0;

			};

		auto GetSafeFloat = [&](const FString& key) -> float {
			return A.Contains(key) ? FCString::Atof(*A[key]) : 0.0f;

			};

		auto GetSafeDouble = [&](const FString& key) -> double {
			return A.Contains(key) ? FCString::Atod(*A[key]) : 0.0f;

			};

		FVegetationPointData temp;
		temp.Id = GetSafeInt("id");
		temp.Name = A["Name"];
		temp.Lat = GetSafeDouble("lat");
		temp.Long = GetSafeDouble("long");
		temp.Elev = GetSafeFloat("Elev");
		temp.Height = GetSafeFloat("Height");
		temp.Scale = GetSafeFloat("Scale");
		temp.Rotation = GetSafeFloat("Rotation");
		temp.Code = GetSafeString("code");
		temp.Model = GetSafeString("Model");
		temp.FileName = Raw.CollectionName;
		temp.State = GetSafeString("State");
		temp.Altitude = GetSafeFloat("Altitude");
		temp.KindID = GetSafeInt("KindID");
		temp.KindDesc = GetSafeString("KindDesc");
		temp.DomainID = GetSafeInt("DomainID");
		temp.DomainDesc = GetSafeString("DomainDesc");
		temp.CountryID = GetSafeInt("CountryID");
		temp.CountryDes = GetSafeString("CountryDes");
		temp.CategoryID = GetSafeInt("CategoryID");
		temp.CategoryDe = GetSafeString("CategoryDe");
		temp.SubCategID = GetSafeInt("SubCategID");
		temp.SubCategDe = GetSafeString("SubCategDe");
		temp.SpecificID = GetSafeInt("SpecificID");
		temp.SpecificDe = GetSafeString("SpecificDe");
		temp.EntityEnum = A.Contains("EntityEnum") ? A["EntityEnum"] : TEXT("");
		temp.Location = Raw.Geometries[i].IsValidIndex(0) ? Raw.Geometries[i][0] : FVector::ZeroVector;

		if (IsValidLonLat(temp.Long, temp.Lat)) {
			PointDataList.Add(temp);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Invalid Lat/Long: (%f, %f) at ID: %d "), temp.Lat, temp.Long, temp.Id);
		}
	}
}

// Second Pipline: Spawn Point Data in batches and threads
void APCGPointContent::SpawnPCGPointDataOfDatabase()
{

	if (!CesiumGeoreference)
	{
		UE_LOG(LogTemp, Error, TEXT("CesiumGeoreference is null."));
		return;
	}

	//if (!bTimerStarted)
	//{
	//    StartTime = FDateTime::UtcNow();
	//    bTimerStarted = true;
	//}

	if (PointDataList.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PCG point data available to spawn."));
		return;
	}


	// ExpectedTotalPoints += PointDataList.Num();

	TMap<FString, TArray<const FVegetationPointData*>> Buckets;
	Buckets.Reserve(32);
	for (const FVegetationPointData& Data : PointDataList)
	{
		const FString CleanedName = Data.Model.Replace(TEXT(" "), TEXT("")).ToLower();
		Buckets.FindOrAdd(CleanedName).Add(&Data);
	}

	TMap<FString, UInstancedStaticMeshComponent*> PerTypeHISM;
	PerTypeHISM.Reserve(Buckets.Num());

	for (const TPair<FString, TArray<const FVegetationPointData*>>& Pair : Buckets)
	{
		const FString& CleanedName = Pair.Key;

		UStaticMesh* Mesh = GetOrLoadMeshForType_GameThread(CleanedName); // loads only once per type
		if (!Mesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("Skipping type '%s' due to missing mesh."), *CleanedName);
			continue;
		}
		Pair.Value[0]->SubCategDe;
		UInstancedStaticMeshComponent* HISM = GetOrCreateHISM_GameThread(CleanedName, Mesh);
		if (!HISM)
		{
			UE_LOG(LogTemp, Warning, TEXT("Skipping type '%s' due to HISM create failure."), *CleanedName);
			continue;
		}

		PerTypeHISM.Add(CleanedName, HISM);
	}

	static const int32 kBatchSize = 5000;

	// Thread-safe counter to track completions and update your timing HUD/logs
	TAtomic<int32> PointsCommitted(0);

	// For each type bucket, schedule batches on the thread pool
	for (const TPair<FString, TArray<const FVegetationPointData*>>& Pair : Buckets)
	{
		const FString& CleanedName = Pair.Key;

		UInstancedStaticMeshComponent* const* HISMPtr = PerTypeHISM.Find(CleanedName);
		if (!HISMPtr) continue;
		UInstancedStaticMeshComponent* HISM = *HISMPtr;

		const TArray<const FVegetationPointData*>& Items = Pair.Value;
		const int32 Total = Items.Num();

		for (int32 StartIdx = 0; StartIdx < Total; StartIdx += kBatchSize)
		{
			const int32 Count = FMath::Min(kBatchSize, Total - StartIdx);

			// Slice for the batch (just pointers; cheap to copy)
			TArray<const FVegetationPointData*> Slice;
			Slice.Reserve(Count);
			for (int32 i = 0; i < Count; ++i)
			{
				Slice.Add(Items[StartIdx + i]);
			}

			// Kick worker task to compute transforms
			Async(EAsyncExecution::ThreadPool, [this, CleanedName, HISM, Slice, &PointsCommitted]()
				{
					// Build transforms OFF the game thread (pure math only!)
					TArray<FTransform> Transforms;
					Transforms.Reserve(Slice.Num());

					for (const FVegetationPointData* Data : Slice)
					{
						// Note: If CesiumGeoreference::Transform... is pure math (it usually is), this is safe.
						// If you ever find it touching engine state, move it to the game thread block below.
						const FVector LLH((double)Data->Long, (double)Data->Lat, (double)Data->Elev);
						const FVector WorldLocation = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(LLH);

						const FVector FinalScale(Data->Scale / 100.f);
						const FRotator FinalRotation(0.0f, Data->Rotation, 0.0f);

						Transforms.Emplace(FinalRotation, WorldLocation, FinalScale);
					}

					// Commit the batch on the GAME THREAD
					AsyncTask(ENamedThreads::GameThread, [this, CleanedName, HISM, Transforms = MoveTemp(Transforms), &PointsCommitted]()
						{
							if (!IsValid(HISM))
							{
								UE_LOG(LogTemp, Warning, TEXT("HISM for '%s' vanished before batch commit."), *CleanedName);
								return;
							}

							HISM->AddInstances(Transforms, /*bShouldReturnIndices*/ true, /*bWorldSpace*/ true);

							const int32 Added = Transforms.Num();
							const int32 NewTotal = (PointsCommitted += Added);
							//APCGPointContent::TotalPointDataPoints += Added;

							//// If we've hit or exceeded the expected total, finalize timing once
							//if (ExpectedTotalPoints > 0 && NewTotal >= ExpectedTotalPoints)
							//{
							//    const FTimespan Elapsed = FDateTime::UtcNow() - StartTime;

							//    if (GEngine)
							//    {
							//        GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("Total Point Data Points: %d"), NewTotal));
							//        GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, FString::Printf(TEXT("Total Time(s) Point Data: %f"), Elapsed.GetTotalSeconds()));
							//    }

							//    UE_LOG(LogTemp, Log, TEXT("Total Point Data Points: %d"), NewTotal);
							//    UE_LOG(LogTemp, Log, TEXT("Total Execution Time(Point Data): %.2f"), Elapsed.GetTotalSeconds());

							//    // reset counters
							//    APCGPointContent::TotalPointDataPoints = 0;
							//    ExpectedTotalPoints = 0;
							//    StartTime = FDateTime::MinValue();
							//    bTimerStarted = false;
							//}
						});
				});
		}
	}

}

// First Pipeline: Calculate Height for Point Data and Spawn in batches and threads
void APCGPointContent::SpawnPCGPointData_CesiumSamplerBatched()
{
	if (!CesiumGeoreference)
	{
		UE_LOG(LogTemp, Error, TEXT("CesiumGeoreference is null."));
		return;
	}

	//if (!bTimerStarted)
	//{
	//    StartTime = FDateTime::UtcNow();
	//    bTimerStarted = true;
	//}

	if (PointDataList.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("No PCG point data available to spawn."));
		return;
	}

	//ExpectedTotalPoints += PointDataList.Num();



	TSet<FString> UniqueTypes;
	UniqueTypes.Reserve(64);

	for (const FVegetationPointData& Data : PointDataList) {
		UniqueTypes.Add(Data.Model.Replace(TEXT(" "), TEXT("")).ToLower());
	}

	TMap<FString, UInstancedStaticMeshComponent*> PerTypeHISM;
	PerTypeHISM.Reserve(UniqueTypes.Num());

	for (const FString& CleanedName : UniqueTypes)
	{
		UStaticMesh* Mesh = GetOrLoadMeshForType_GameThread(CleanedName); // loads only once per type
		if (!Mesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("Skipping type '%s' due to missing mesh."), *CleanedName);
			continue;
		}
		UInstancedStaticMeshComponent* HISM = GetOrCreateHISM_GameThread(CleanedName, Mesh);
		if (!HISM)
		{
			UE_LOG(LogTemp, Warning, TEXT("Skipping type '%s' due to HISM create failure."), *CleanedName);
			continue;
		}
		PerTypeHISM.Add(CleanedName, HISM);
	}

	static const int32 kBatchSize = 5000; // tune based on your data; 5–20k is usually a good range

	struct FSamplerMeta {
		int32 id = -1;
		FString CleanedName;
		float Scale;
		float Rotation;
		const FVegetationPointData* Source = nullptr;
	};

	for (int32 StartIdx = 0; StartIdx < PointDataList.Num(); StartIdx += kBatchSize)
	{
		const int32 Count = FMath::Min(kBatchSize, PointDataList.Num() - StartIdx);

		TArray<FSamplerMeta> MetaPerIndex;
		MetaPerIndex.Reserve(Count);
		TArray<FVector> Positions;
		Positions.Reserve(Count);


		for (int32 i = 0; i < Count; ++i)
		{

			const FVegetationPointData& Data = PointDataList[StartIdx + i];
			Positions.Add(FVector(Data.Long, Data.Lat, 0));
			FSamplerMeta M;
			M.id = Data.Id;
			M.CleanedName = Data.Model.Replace(TEXT(" "), TEXT("")).ToLower();
			M.Scale = Data.Scale;
			M.Rotation = Data.Rotation;
			M.Source = &Data;
			MetaPerIndex.Add(M);

		}


		FCesiumSampleHeightMostDetailedCallback CesiumCallback;
		CesiumCallback.BindLambda(
			[this, PerTypeHISM, MetaPerIndex](ACesium3DTileset*, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& Warnings)
			{

				if (Warnings.Num() > 0) {
					for (const FString& W : Warnings) {
						UE_LOG(LogTemp, Error, TEXT("Cesium Warning: %s"), *W);
					}
				}

				TArray<FCesiumSampleHeightResult> ResultsCopy = Results;

				Async(EAsyncExecution::ThreadPool, [this, PerTypeHISM, ResultsCopy, MetaPerIndex]()
					{

						TMap<FString, TArray<FTransform>> PerTypeTransforms;
						PerTypeTransforms.Reserve(PerTypeHISM.Num());

						const int32 N = FMath::Min(ResultsCopy.Num(), MetaPerIndex.Num());

						for (int32 i = 0; i < N; i++) {
							const auto& R = ResultsCopy[i];
							if (!R.SampleSuccess) {
								TotalFailedPoints++;
								const FSamplerMeta& M = MetaPerIndex[i];
								FailedSamplePoints.Add(*M.Source);
								UE_LOG(LogTemp, Error, TEXT("Point Data Height Sampling Fails for Point id:%d at Long/Lat: (%.6f, %.6f)"), M.id, R.LongitudeLatitudeHeight[0], R.LongitudeLatitudeHeight[1]);
								continue;
							}
							TotalSuccessPoints++;
							const FVector World = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(R.LongitudeLatitudeHeight);
							const FSamplerMeta& M = MetaPerIndex[i];
							const FVector S(M.Scale / 100.0f);
							const FRotator Rot(0.0f, M.Rotation, 0.0f);

							PerTypeTransforms.FindOrAdd(M.CleanedName).Emplace(Rot, World, S);

							// db insert :
							FVegetationPointData DBData = *M.Source;
							DBData.Elev = R.LongitudeLatitudeHeight.Z;
							InsertPointDataFeaturesToDB(DBData);

							//if (ExpectedTotalPoints - TotalFailedPoints == TotalSuccessPoints) {
							//    ReSampleFailedPointsAndSpawnPCGPointData_CesiumSamplerBatched();
							//}
						}


						PendingCesiumBatches--;

						AsyncTask(ENamedThreads::GameThread, [this, PerTypeTransforms = MoveTemp(PerTypeTransforms), PerTypeHISM]()
							{

								for (const TPair<FString, TArray<FTransform>>& Pair : PerTypeTransforms) {
									const FString& CleanedName = Pair.Key;
									const TArray<FTransform>& Transforms = Pair.Value;

									if (Transforms.Num() == 0) continue;

									UInstancedStaticMeshComponent* const* HISMPtr = PerTypeHISM.Find(CleanedName);
									if (!HISMPtr) continue;

									UInstancedStaticMeshComponent* HISM = *HISMPtr;
									HISM->AddInstances(Transforms, false, true);
								}

								//if (ExpectedTotalPoints - TotalFailedPoints == TotalSuccessPoints) {
								//    ReSampleFailedPointsAndSpawnPCGPointData_CesiumSamplerBatched();
								//}
							});
					});

			});
		PendingCesiumBatches++;
		Tileset->SampleHeightMostDetailed(Positions, CesiumCallback);

	}

}

// First Pipeline: Insert Point Data features to Database
bool APCGPointContent::InsertPointDataFeaturesToDB(const FVegetationPointData& Data)
{
	if (!GI) return false;
	if (!DBSubsystem || !DBSubsystem->IsOpen())
	{
		UE_LOG(LogTemp, Error, TEXT("InsertPolygonPointsToDB: DB subsystem not available/open"));
		return false;
	}
	// DBSubsystem->GetDatabase().Execute(TEXT("BEGIN TRANSACTION;"));
	const double TileSizeDeg = 0.05;
	const int32 TileX = FMath::FloorToInt(Data.Long / TileSizeDeg);
	const int32 TileY = FMath::FloorToInt(Data.Lat / TileSizeDeg);

	FString SQL = FString::Format(
		TEXT("INSERT INTO PointsData (ShapefileID ,PointID,Latitude ,Longitude ,ELevation ,Name ,Scale ,Rotation,Model ,State,TileX,TileY) "
			"VALUES ('{0}', {1}, {2}, {3}, {4}, '{5}', {6}, {7}, '{8}', '{9}',{10},{11});"),
		{
			*Data.FileName,
			Data.Id,
			FString::Printf(TEXT("%.15f"), Data.Lat),
			FString::Printf(TEXT("%.15f"), Data.Long),
			FString::Printf(TEXT("%.15f"), Data.Elev),
			*Data.Name,
			Data.Scale,
			Data.Rotation,
			*Data.Model,
			*Data.State,
			TileX,
			TileY
		}
	);
	//if (Data.Id == 3000) {
	//    UE_LOG(LogTemp, Error, TEXT("Long/Lat: (%f, %f)"), Data.Long, Data.Lat);
	//}

	bool result = DBSubsystem->Execute(SQL);
	//  DBSubsystem->CommitTransaction();
	if (result) {
		UE_LOG(LogTemp, Log, TEXT("Inserted features for shapefile %s and Point %d into PointDataFeatures table"), *Data.FileName, Data.Id);
	}
	//else {
	//    UE_LOG(LogTemp, Error, TEXT("Failed to insert features for shapefile %s and Point %d into PointDataFeatures table"), *Data.FileName, Data.Id);
	//}
	return true;

}

// Second Pipline: Load PointData from Database (Asynchronous thread)
void APCGPointContent::LoadPointDataFromDatabase(const FString& ShapefileID) {
	if (!GI) return;
	if (!DBSubsystem || !DBSubsystem->IsOpen())
	{
		UE_LOG(LogTemp, Error, TEXT("LoadPointDataFromDatabase: DB subsystem not available/open"));
		return;
	}

	// TArray<FVegetationPointData> Points;
	const FString ShapeFileIDCopy = ShapefileID;
	Async(EAsyncExecution::ThreadPool, [this, ShapeFileIDCopy]()
		{
			TArray<FVegetationPointData> LocalPoints;
			LocalPoints.Reserve(100000);
			FString PointsSQL = FString::Printf(TEXT("SELECT ShapefileID ,PointID,Latitude ,Longitude ,ELevation ,Name ,Scale ,Rotation,Model ,State FROM PointsData WHERE ShapefileID='%s';"), *ShapeFileIDCopy);
			DBSubsystem->ExecuteWithCallback(PointsSQL, [&LocalPoints](const FSQLitePreparedStatement& Statement) -> ESQLitePreparedStatementExecuteRowResult
				{

					FVegetationPointData P;
					Statement.GetColumnValueByName(TEXT("ShapefileID"), P.FileName);
					Statement.GetColumnValueByName(TEXT("PointID"), P.Id);
					Statement.GetColumnValueByName(TEXT("Latitude"), P.Lat);
					Statement.GetColumnValueByName(TEXT("Longitude"), P.Long);
					Statement.GetColumnValueByName(TEXT("ELevation"), P.Elev);
					Statement.GetColumnValueByName(TEXT("Name"), P.Name);
					Statement.GetColumnValueByName(TEXT("Scale"), P.Scale);
					Statement.GetColumnValueByName(TEXT("Rotation"), P.Rotation);
					Statement.GetColumnValueByName(TEXT("Model"), P.Model);
					Statement.GetColumnValueByName(TEXT("State"), P.State);

					//PointDataList.Add(P);
					LocalPoints.Add(MoveTemp(P));
					return ESQLitePreparedStatementExecuteRowResult::Continue;
				});

			AsyncTask(ENamedThreads::GameThread, [this, Points = MoveTemp(LocalPoints)]() mutable {
				PointDataList = MoveTemp(Points);
				SpawnPCGPointDataOfDatabase();
				});
		});
}

EVegetationCategory APCGPointContent::GetCategoryForModel(const FString& SubCategDes)
{

	if (SubCategDes.Contains(TEXT("Tree")))
		return EVegetationCategory::Tree;
	if (SubCategDes.Contains(TEXT("Bushes")))
		return EVegetationCategory::Bushes;
	if (SubCategDes.Contains(TEXT("RockPile")))
		return EVegetationCategory::RockPile;
	if (SubCategDes.Contains(TEXT("Shrub")))
		return EVegetationCategory::Shrub;

	return EVegetationCategory::Other;
}

//Load the BP_Registery once
void APCGPointContent::PreWarmMeshesFromRegistry(UWorld* World, UBlueprintRegistery* Registery) {
	if (bGlobalMeshesInitialized) return;
	bGlobalMeshesInitialized = true;
	TSubclassOf<AActor> MatchedBPClass = nullptr;
	for (const TSoftClassPtr<AActor>& SoftBP : BlueprintRegistry->BlueprintClasses)
	{
		MatchedBPClass = SoftBP.LoadSynchronous();
		FString AssetName = SoftBP.GetAssetName().ToLower();
		if (!AssetName.StartsWith(TEXT("pd_"))) continue;
		const FString CleanedName = AssetName.RightChop(3);
		UStaticMesh* FoundMesh = ExtractMeshFromBlueprint(MatchedBPClass);
		if (FoundMesh) {
			GlobalMeshesPerType.Add(CleanedName.LeftChop(2), FoundMesh);
		}
	}
}

//Extract Static Mesh from PD_ classes in PCGPointContent folder in content browser
UStaticMesh* APCGPointContent::ExtractMeshFromBlueprint(TSubclassOf<AActor> BPClass)
{
	if (!BPClass) return nullptr;

	AActor* TempActor = GetWorld()->SpawnActor<AActor>(BPClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (!TempActor) return nullptr;

	UStaticMesh* FoundMesh = nullptr;
	TArray<UStaticMeshComponent*> MeshComponents;
	TempActor->GetComponents<UStaticMeshComponent>(MeshComponents);

	for (UStaticMeshComponent* Comp : MeshComponents)
	{
		if (Comp->GetStaticMesh())
		{
			FoundMesh = Comp->GetStaticMesh();
			break;
		}
	}

	TempActor->Destroy();
	return FoundMesh;
}

// Toggle visiblility
void APCGPointContent::ToggleVisibility(bool bVisible) {
	for (auto& Pair : InstancedMeshMap)
	{
		UInstancedStaticMeshComponent* HISMC = Pair.Value;
		HISMC->SetVisibility(bVisible, true);
		HISMC->SetHiddenInGame(!bVisible);
	}
}

//Set cull distances
void APCGPointContent::SetCullDistance(float distanceInMeters) {
	for (auto& Pair : InstancedMeshMap)
	{
		UInstancedStaticMeshComponent* HISMC = Pair.Value;
		HISMC->SetCullDistances(0, distanceInMeters * 100);
	}
}


/*------------------------------Runtime Loading from DB fucntion--------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------*/

//function to enable/disable runtime db streaming from manager
void APCGPointContent::EnableStreaming(bool bInStreaming, float InRadiusKm, float InMinRequery)
{
	bStreamingEnabled = bInStreaming;
	QueryRadiusKm = InRadiusKm;
	MinRequeryDistanceKm = InMinRequery;
	bHasLastQueryCenter = false;
}

//Set shapfile id to stream data fromdb at runtime
void APCGPointContent::SetStreamingShapeFileId(FString InStreamingShapeFileID)
{
	StreamingShapeFileId = InStreamingShapeFileID;
}

// function to load nearby points based on distance from the db
void APCGPointContent::RequestPointsInRadiusAsync()
{
	if (!DBSubsystem) return;

	const double CenterLat = LastQueryLat;
	const double CenterLon = LastQueryLon;
	const double RadiusKm = QueryRadiusKm;
	const FString LocalShapeFileID = StreamingShapeFileId;

	TWeakObjectPtr<UPcgSQLiteSubsystem> WeakDBSubystem(DBSubsystem);
	TWeakObjectPtr<APCGPointContent> Weakthis(this);

	Async(EAsyncExecution::ThreadPool, [Weakthis, WeakDBSubystem, LocalShapeFileID, CenterLat, CenterLon, RadiusKm]()
		{
			if (!WeakDBSubystem.IsValid()) return;

			UPcgSQLiteSubsystem* DBSub = WeakDBSubystem.Get();

			constexpr double EarthRadiusKm = 6371.0;
			const double dLat = (RadiusKm / EarthRadiusKm) * (180.0 / PI);
			const double dLon = dLat / FMath::Cos(FMath::DegreesToRadians(CenterLat));


			const double MinLat = CenterLat - dLat;
			const double MaxLat = CenterLat + dLat;
			const double MinLon = CenterLon - dLon;
			const double MaxLon = CenterLon + dLon;


			//FString Sql;
			//if (!LocalShapeFileID.IsEmpty()) {
			//	Sql = FString::Printf(TEXT("SELECT ShapefileID ,PointID,Latitude ,Longitude ,ELevation ,Name ,Scale ,Rotation,Model ,State FROM PointsData WHERE ShapefileID='%s' AND Latitude BETWEEN %f AND %F AND LONGITUDE BETWEEN %F AND %f;"), *LocalShapeFileID, MinLat, MaxLat, MinLon, MaxLon);
			//}
			//else {
			//	Sql = FString::Printf(TEXT("SELECT ShapefileID ,PointID,Latitude ,Longitude ,ELevation ,Name ,Scale ,Rotation,Model ,State FROM PointsData WHERE Latitude BETWEEN %f AND %F AND LONGITUDE BETWEEN %F AND %f;"), MinLat, MaxLat, MinLon, MaxLon);
			//}


			FString Sql;
			if (!LocalShapeFileID.IsEmpty())
			{
				Sql = FString::Printf(
					TEXT("SELECT ShapefileID, PointID, Latitude, Longitude, Elevation, Name, Scale, Rotation, Model, State "
						"FROM PointsData "
						"WHERE ShapefileID='%s' "
						"AND Latitude BETWEEN %f AND %f "
						"AND Longitude BETWEEN %f AND %f;"),
					*LocalShapeFileID,
					MinLat, MaxLat,
					MinLon, MaxLon
				);
			}
			else
			{
				Sql = FString::Printf(
					TEXT("SELECT ShapefileID, PointID, Latitude, Longitude, Elevation, Name, Scale, Rotation, Model, State "
						"FROM PointsData "
						"WHERE Latitude BETWEEN %f AND %f "
						"AND Longitude BETWEEN %f AND %f;"),
					MinLat, MaxLat,
					MinLon, MaxLon
				);
			}


			TArray<FVegetationPointData> Results;
			Results.Reserve(100000);

			DBSub->ExecuteWithCallback(Sql, [&Results](const FSQLitePreparedStatement& Statement) -> ESQLitePreparedStatementExecuteRowResult
				{
					FVegetationPointData P;
					Statement.GetColumnValueByName(TEXT("ShapefileID"), P.FileName);
					Statement.GetColumnValueByName(TEXT("PointID"), P.Id);
					Statement.GetColumnValueByName(TEXT("Latitude"), P.Lat);
					Statement.GetColumnValueByName(TEXT("Longitude"), P.Long);
					Statement.GetColumnValueByName(TEXT("ELevation"), P.Elev);
					Statement.GetColumnValueByName(TEXT("Name"), P.Name);
					Statement.GetColumnValueByName(TEXT("Scale"), P.Scale);
					Statement.GetColumnValueByName(TEXT("Rotation"), P.Rotation);
					Statement.GetColumnValueByName(TEXT("Model"), P.Model);
					Statement.GetColumnValueByName(TEXT("State"), P.State);
					Results.Add(MoveTemp(P));

					return ESQLitePreparedStatementExecuteRowResult::Continue;
				});

			AsyncTask(ENamedThreads::GameThread, [Weakthis, Results = MoveTemp(Results)]() mutable {
				if (!Weakthis.IsValid()) return;
				Weakthis->OnPointsLoadedFromDB(MoveTemp(Results));
				});
		});

}

//Spawn PointData loaded from db in the scene 
void APCGPointContent::OnPointsLoadedFromDB(TArray<FVegetationPointData>&& Results)
{
	PointDataList.Reset();
	ClearAllSpanwnedInstances();
	if (Results.Num() == 0) return;
	PointDataList = MoveTemp(Results);
	SpawnPCGPointDataOfDatabase();
}

//Clear All spawned instances 
void APCGPointContent::ClearAllSpanwnedInstances()
{
	for (auto& Pair : InstancedMeshMap) {
		if (UInstancedStaticMeshComponent* HISM = Pair.Value) {
			HISM->ClearInstances();
		}
	}
}

double APCGPointContent::Haversinekm(double Lat1Deg, double Lon1Deg, double Lat2Deg, double Lon2Deg)
{
	constexpr double EarthRadiusKm = 6371.0;

	const double Lat1Rad = FMath::DegreesToRadians(Lat1Deg);
	const double Lon1Rad = FMath::DegreesToRadians(Lon1Deg);
	const double Lat2Rad = FMath::DegreesToRadians(Lat2Deg);
	const double Lon2Rad = FMath::DegreesToRadians(Lon2Deg);
	const double DLat = Lat2Rad - Lat1Rad;
	const double DLon = Lon2Rad - Lon1Rad;

	const double a =
		FMath::Sin(DLat / 2.0) * FMath::Sin(DLat / 2.0f)
		+ FMath::Cos(Lat1Rad) * FMath::Cos(Lat2Rad)
		* FMath::Sin(DLon / 2.0) * FMath::Sin(DLon / 2.0);

	const double c = 2.0 * FMath::Atan2(FMath::Sqrt(a), FMath::Sqrt(1.0 - a));
	return EarthRadiusKm * c;
}

void APCGPointContent::Tick(float DeltaSeconds) {

	if (!bStreamingEnabled || !CesiumGeoreference) return;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	const FVector PlayerLocation = PlayerPawn->GetActorLocation();

	const FVector PlayerLLH = CesiumGeoreference->TransformUnrealPositionToLongitudeLatitudeHeight(PlayerLocation);
	const double CurrentLat = PlayerLLH.Y;
	const double CurrentLon = PlayerLLH.X;

	if (!bHasLastQueryCenter) {
		LastQueryLat = CurrentLat;
		LastQueryLon = CurrentLon;
		bHasLastQueryCenter = true;
		RequestPointsInRadiusAsync();
		return;
	}

	const double DistanceKm = Haversinekm(LastQueryLat, LastQueryLon, CurrentLat, CurrentLon);
	if (DistanceKm >= MinRequeryDistanceKm) {
		LastQueryLat = CurrentLat;
		LastQueryLon = CurrentLon;
		RequestPointsInRadiusAsync();
	}
}



/*------------------------------Tiles--------------------------------
-------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------*/


void APCGPointContent::ComputerDesiredTiles(TSet<FIntPoint>& OutDesiredTiles) const {

	OutDesiredTiles.Reset();
	const double TileSizeDeg = 0.05;

	const double CenterLat = LastQueryLat;
	const double CenterLon = LastQueryLon;
	const double RadiusKm = QueryRadiusKm;
	constexpr double EarthRadiusKm = 6371.0;

	const double dLat = (RadiusKm / EarthRadiusKm) * (180.0 / PI);
	const double dLon = dLat / FMath::Cos(FMath::DegreesToRadians(CenterLat));

	const double MinLat = CenterLat - dLat;
	const double MaxLat = CenterLat + dLat;
	const double MinLon = CenterLon - dLon;
	const double MaxLon = CenterLon + dLon;

	const int32 MinTileX = FMath::FloorToInt(MinLon / TileSizeDeg);
	const int32 MaxTileX = FMath::FloorToInt(MinLon / TileSizeDeg);

	const int32 MinTileY = FMath::FloorToInt(MinLat / TileSizeDeg);
	const int32 MaxTileY = FMath::FloorToInt(MaxLat / TileSizeDeg);

	for (int32 X = MinTileX; X <= MaxTileX; ++X) {
		for (int32 Y = MinTileY; Y <= MaxTileY; ++Y) {
			OutDesiredTiles.Add(FIntPoint(X, Y));
		}
	}

}

void APCGPointContent::UpdateStreamingTiles() {
	if (!DBSubsystem) return;

	TSet<FIntPoint> DesiredTiles;
	ComputerDesiredTiles(DesiredTiles);

	TSet<FIntPoint> CurrentTiles;
	LoadedTiles.GetKeys(CurrentTiles);

	TSet<FIntPoint> TilesToLoad = CurrentTiles.Difference(DesiredTiles);
	TSet<FIntPoint> TilesToUnload = DesiredTiles.Difference(CurrentTiles);

	for (const FIntPoint& TileKey : TilesToLoad) {
		UnloadTile(TileKey);
	}

	for (const FIntPoint& TileKey : TilesToLoad) {
		if (PendingTileLoads.Contains(TileKey)) continue;
		PendingTileLoads.Add(TileKey);
		RequestTileAsync(TileKey);
	}
}

void APCGPointContent::RequestTileAsync(const FIntPoint& TileKey) {

	if (!DBSubsystem) return;

	const int32 TileX = TileKey.X;
	const int32 TileY = TileKey.Y;

	const FString LocalShapeFileID = StreamingShapeFileId;

	TWeakObjectPtr<UPcgSQLiteSubsystem> WeakDBSubystem(DBSubsystem);
	TWeakObjectPtr<APCGPointContent> Weakthis(this);

	Async(EAsyncExecution::ThreadPool, [Weakthis, WeakDBSubystem, LocalShapeFileID, TileX, TileY, TileKey]()
		{
			if (!WeakDBSubystem.IsValid()) return;

			UPcgSQLiteSubsystem* DBSub = WeakDBSubystem.Get();


			FString Sql;
			if (!LocalShapeFileID.IsEmpty()) {
				Sql = FString::Printf(TEXT("SELECT ShapefileID ,PointID,Latitude ,Longitude ,ELevation ,Name ,Scale ,Rotation,Model ,State FROM PointsData WHERE ShapefileID='%s' AND TileX = %d AND TileY= %d;"), *LocalShapeFileID, TileX, TileY);
			}
			else {
				Sql = FString::Printf(TEXT("SELECT ShapefileID ,PointID,Latitude ,Longitude ,ELevation ,Name ,Scale ,Rotation,Model ,State FROM PointsData AND TileX = %d AND TileY= %d;"), TileX, TileY);
			}


			TArray<FVegetationPointData> Results;
			Results.Reserve(100000);

			DBSub->ExecuteWithCallback(Sql, [&Results](const FSQLitePreparedStatement& Statement) -> ESQLitePreparedStatementExecuteRowResult
				{
					FVegetationPointData P;
					Statement.GetColumnValueByName(TEXT("ShapefileID"), P.FileName);
					Statement.GetColumnValueByName(TEXT("PointID"), P.Id);
					Statement.GetColumnValueByName(TEXT("Latitude"), P.Lat);
					Statement.GetColumnValueByName(TEXT("Longitude"), P.Long);
					Statement.GetColumnValueByName(TEXT("ELevation"), P.Elev);
					Statement.GetColumnValueByName(TEXT("Name"), P.Name);
					Statement.GetColumnValueByName(TEXT("Scale"), P.Scale);
					Statement.GetColumnValueByName(TEXT("Rotation"), P.Rotation);
					Statement.GetColumnValueByName(TEXT("Model"), P.Model);
					Statement.GetColumnValueByName(TEXT("State"), P.State);
					Results.Add(MoveTemp(P));

					return ESQLitePreparedStatementExecuteRowResult::Continue;
				});

			AsyncTask(ENamedThreads::GameThread, [Weakthis, TileKey, Results = MoveTemp(Results)]() mutable {
				if (!Weakthis.IsValid()) return;
				Weakthis->PendingTileLoads.Remove(TileKey);
				Weakthis->OnTilesPointLoaded_GameThread(TileKey, MoveTemp(Results));
				});
		});


}

void APCGPointContent::OnTilesPointLoaded_GameThread(const FIntPoint& TileKey, TArray<FVegetationPointData>&& TilePoints) {
	TSet<FIntPoint> DesiredTiles;
	ComputerDesiredTiles(DesiredTiles);
	if (!DesiredTiles.Contains(TileKey)) {
		return;
	}
	if (TilePoints.Num() == 0) {
		return;
	}
	if (LoadedTiles.Contains(TileKey)) {
		return;
	}
	SpawnTilePoints(TileKey, TilePoints);
}

void APCGPointContent::SpawnTilePoints(const FIntPoint& TileKey, TArray<FVegetationPointData>& TilePoints) {

	if (!CesiumGeoreference || TilePoints.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("No PCG point data available to spawn."));
		UE_LOG(LogTemp, Error, TEXT("CesiumGeoreference is null."));
		return;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = MakeUniqueObjectName(GetWorld(), AActor::StaticClass(), *FString::Printf(TEXT("PointTile_%d_%d"), TileKey.X, TileKey.Y));
	AActor* TileActor = GetWorld()->SpawnActor<AActor>(
		AActor::StaticClass(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		SpawnParams);
	if (TileActor)
	{
		USceneComponent* SceneRoot = NewObject<USceneComponent>(TileActor);
		SceneRoot->SetupAttachment(nullptr);
		SceneRoot->RegisterComponent();
		TileActor->SetRootComponent(SceneRoot);

#if WITH_EDITOR
		TileActor->SetActorLabel(FString::Printf(TEXT("PointTile_(%d,%d)"), TileKey.X, TileKey.Y));
#endif
	}

	TMap<FString, TArray<const FVegetationPointData*>> Buckets;
	Buckets.Reserve(32);
	for (const FVegetationPointData& Data : PointDataList)
	{
		const FString CleanedName = Data.Model.Replace(TEXT(" "), TEXT("")).ToLower();
		Buckets.FindOrAdd(CleanedName).Add(&Data);
	}

	TMap<FString, UInstancedStaticMeshComponent*> PerTypeHISM;
	PerTypeHISM.Reserve(Buckets.Num());

	FLoadedTileInfo TileInfo;
	TileInfo.TileX = TileKey.X;
	TileInfo.TileY = TileKey.Y;
	TileInfo.ParentActor = TileActor;
	for (const TPair<FString, TArray<const FVegetationPointData*>>& Pair : Buckets)
	{
		const FString& CleanedName = Pair.Key;

		UStaticMesh* Mesh = GetOrLoadMeshForType_GameThread(CleanedName); // loads only once per type
		if (!Mesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("Skipping type '%s' due to missing mesh."), *CleanedName);
			continue;
		}

		UInstancedStaticMeshComponent* HISM = NewObject<UInstancedStaticMeshComponent>(TileActor);
		HISM->SetStaticMesh(Mesh);
		HISM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		HISM->SetMobility(EComponentMobility::Movable);
		HISM->SetCanEverAffectNavigation(false);
		//HISM->SetCullDistances(0, 800000); //10km
		//HISM->LDMaxDrawDistance = 500000.0f;
		HISM->AttachToComponent(TileActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
		HISM->RegisterComponent();
		TileActor->AddInstanceComponent(HISM);
		PerTypeHISM.Add(CleanedName, HISM);
		TileInfo.InstancedMeshMap.Add(CleanedName, HISM);
	}
	LoadedTiles.Add(TileKey, TileInfo);

	static const int32 kBatchSize = 5000;

	// Thread-safe counter to track completions and update your timing HUD/logs
	TAtomic<int32> PointsCommitted(0);

	// For each type bucket, schedule batches on the thread pool
	for (const TPair<FString, TArray<const FVegetationPointData*>>& Pair : Buckets)
	{
		const FString& CleanedName = Pair.Key;

		UInstancedStaticMeshComponent* const* HISMPtr = PerTypeHISM.Find(CleanedName);
		if (!HISMPtr) continue;
		UInstancedStaticMeshComponent* HISM = *HISMPtr;

		const TArray<const FVegetationPointData*>& Items = Pair.Value;
		const int32 Total = Items.Num();

		for (int32 StartIdx = 0; StartIdx < Total; StartIdx += kBatchSize)
		{
			const int32 Count = FMath::Min(kBatchSize, Total - StartIdx);

			// Slice for the batch (just pointers; cheap to copy)
			TArray<const FVegetationPointData*> Slice;
			Slice.Reserve(Count);
			for (int32 i = 0; i < Count; ++i)
			{
				Slice.Add(Items[StartIdx + i]);
			}

			Async(EAsyncExecution::ThreadPool, [this, CleanedName, HISM, Slice, &PointsCommitted]()
				{
					TArray<FTransform> Transforms;
					Transforms.Reserve(Slice.Num());

					for (const FVegetationPointData* Data : Slice)
					{

						const FVector LLH((double)Data->Long, (double)Data->Lat, (double)Data->Elev);
						const FVector WorldLocation = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(LLH);

						const FVector FinalScale(Data->Scale / 100.f);
						const FRotator FinalRotation(0.0f, Data->Rotation, 0.0f);

						Transforms.Emplace(FinalRotation, WorldLocation, FinalScale);
					}


					AsyncTask(ENamedThreads::GameThread, [this, CleanedName, HISM, Transforms = MoveTemp(Transforms), &PointsCommitted]()
						{
							if (!IsValid(HISM))
							{
								UE_LOG(LogTemp, Warning, TEXT("HISM for '%s' vanished before batch commit."), *CleanedName);
								return;
							}

							HISM->AddInstances(Transforms, /*bShouldReturnIndices*/ true, /*bWorldSpace*/ true);

							const int32 Added = Transforms.Num();
							const int32 NewTotal = (PointsCommitted += Added);

						});
				});
		}
	}


}

void APCGPointContent::UnloadTile(const FIntPoint& TileKey) {

	if (FLoadedTileInfo* Info = LoadedTiles.Find(TileKey)) {
		if (Info->ParentActor) {
			Info->ParentActor->Destroy();
		}
		LoadedTiles.Remove(TileKey);
	}
}



























//--------------------------Extra functions------------------------------------

//FActorSpawnParameters Params;
//Params.Owner = this;
//TArray<FVector> Points;
//for (auto& Point : PointDataList) {
//	Points.Add(CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(Point.Long, Point.Long, Point.Elev)));
//}
//
//APolygonHiGenActor* HiGenActor = GetWorld()->SpawnActor<APolygonHiGenActor>(
//	APolygonHiGenActor::StaticClass(),
//	Points[0],
//	FRotator::ZeroRotator,
//	Params);
//
//
//#if WITH_EDITOR
//HiGenActor->SetActorLabel("Point_Testing");
//#endif
//
//
//HiGenActor->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
//
//HiGenActor->Positions = Points;
//FVector BoxExtents = FVector(20000000, 20000000, 20000000);
//HiGenActor->BoxExtents = BoxExtents;
//FString GraphName = "Test";
//HiGenActor->GraphName = GraphName;
//HiGenActor->AssignHiGenGraph();
//
//return;
// Get / Create asingle Parent actor to contains HISM/ISM inside of it.
//AActor* APCGPointContent::GetOrCreateGlobalParentActor(UWorld* World)
//{
//	if (GlobalParentActor.IsValid()) {
//		return GlobalParentActor.Get();
//	}
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.Name = MakeUniqueObjectName(World, AActor::StaticClass(), TEXT("PCGPoint_GlobalParent"));
//
//	AActor* NewParent = World->SpawnActor<AActor>(
//		AActor::StaticClass(),
//		FVector::ZeroVector,
//		FRotator::ZeroRotator,
//		SpawnParams);
//
//	if (NewParent)
//	{
//		USceneComponent* SceneRoot = NewObject<USceneComponent>(NewParent);
//		SceneRoot->SetupAttachment(nullptr);
//		SceneRoot->RegisterComponent();
//		NewParent->SetRootComponent(SceneRoot);
//
//#if WITH_EDITOR
//		NewParent->SetActorLabel(TEXT("PCGPoint_GlobalParent"));
//#endif
//		GlobalParentActor = NewParent;
//	}
//	return NewParent;
//}

//void APCGPointContent::SpawnPCGPointData()
//{
//
//	//if (!bTimerStarted) {
//	//    StartTime = FDateTime::UtcNow();
//	//    bTimerStarted = true;
//
//	//}
//
//	if (PointDataList.Num() == 0)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("No PCG point data available to spawn."));
//		return;
//	}
//
//	//ExpectedTotalPoints += PointDataList.Num();
//
//	//TotalPointDataPoints += PointDataList.Num();
//
//	FString BaseName = PointDataList[0].FileName;
//	FName DesiredName(*BaseName);
//
//	// Generate a unique name in the current world (Outer)
//	FName UniqueName = MakeUniqueObjectName(GetWorld(), AActor::StaticClass(), DesiredName);
//
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.Name = UniqueName;
//
//	ParentActor = GetWorld()->SpawnActor<AActor>(
//		AActor::StaticClass(),
//		FVector::ZeroVector,
//		FRotator::ZeroRotator,
//		SpawnParams);
//	if (ParentActor)
//	{
//		USceneComponent* SceneRoot = NewObject<USceneComponent>(ParentActor);
//		SceneRoot->SetupAttachment(nullptr);
//		SceneRoot->RegisterComponent();
//		ParentActor->SetRootComponent(SceneRoot);
//
//#if WITH_EDITOR
//		ParentActor->SetActorLabel(TEXT("PCG Point Parent"));
//#endif
//	}
//
//	for (FVegetationPointData& Data : PointDataList)
//	{
//		// SpawnPointDataOnTerrainUsingElevData(Data);
//		SpawnPointDataOnTerrainUsingCesiumSampler_HISM(Data);
//		// SpawnPointDataOnTerrainUsingElevData_HISM(Data);
//		 //SpawnPointDataOnTerrainUsingElevData_HISM(Data);
//		 //PCGPointContent::TotalPointDataPoints++;
//		 //SpawnPointDataOnTerrainUsingCesiumSampler(Data);
//	}
//
//}
//void APCGPointContent::ReSampleFailedPointsAndSpawnPCGPointData_CesiumSamplerBatched() {
//
//	if (!CesiumGeoreference)
//	{
//		UE_LOG(LogTemp, Error, TEXT("CesiumGeoreference is null."));
//		return;
//	}
//
//	if (FailedSamplePoints.Num() == 0)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("No PCG point data available to spawn."));
//		return;
//	}
//
//	// --- GROUP BY TYPE (CleanedName) ---
//	TMap<FString, TArray<const FVegetationPointData*>> Buckets;
//	Buckets.Reserve(32);
//	for (const FVegetationPointData& Data : FailedSamplePoints)
//	{
//		const FString CleanedName = Data.Model.Replace(TEXT(" "), TEXT("")).ToLower();
//		Buckets.FindOrAdd(CleanedName).Add(&Data);
//	}
//
//	// --- Prewarm: per-type mesh + HISM on the GAME THREAD (no UObject work off-thread) ---
//	TMap<FString, UHierarchicalInstancedStaticMeshComponent*> PerTypeHISM;
//	PerTypeHISM.Reserve(Buckets.Num());
//
//	for (const TPair<FString, TArray<const FVegetationPointData*>>& Pair : Buckets)
//	{
//		const FString& CleanedName = Pair.Key;
//
//		UStaticMesh* Mesh = GetOrLoadMeshForType_GameThread(CleanedName); // loads only once per type
//		if (!Mesh)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Skipping type '%s' due to missing mesh."), *CleanedName);
//			continue;
//		}
//		Pair.Value[0]->SubCategDe;
//		UHierarchicalInstancedStaticMeshComponent* HISM = GetOrCreateHISM_GameThread(CleanedName, Mesh);
//		if (!HISM)
//		{
//			UE_LOG(LogTemp, Warning, TEXT("Skipping type '%s' due to HISM create failure."), *CleanedName);
//			continue;
//		}
//
//		PerTypeHISM.Add(CleanedName, HISM);
//	}
//
//	static const int32 kBatchSize = 1000; // tune based on your data; 5–20k is usually a good range
//
//	struct FSamplerMeta {
//		int32 id = -1;
//		FString CleanedName;
//		float Scale;
//		float Rotation;
//		const FVegetationPointData* Source = nullptr;
//	};
//
//	// For each type bucket, schedule batches on the thread pool
//	for (const TPair<FString, TArray<const FVegetationPointData*>>& Pair : Buckets)
//	{
//		const FString& CleanedName = Pair.Key;
//
//		UHierarchicalInstancedStaticMeshComponent* const* HISMPtr = PerTypeHISM.Find(CleanedName);
//		if (!HISMPtr) continue;
//		UHierarchicalInstancedStaticMeshComponent* HISM = *HISMPtr;
//
//		const TArray<const FVegetationPointData*>& Items = Pair.Value;
//		const int32 Total = Items.Num();
//
//		for (int32 StartIdx = 0; StartIdx < Total; StartIdx += kBatchSize)
//		{
//			const int32 Count = FMath::Min(kBatchSize, Total - StartIdx);
//
//			TArray<FSamplerMeta> MetaPerIndex;
//			MetaPerIndex.Reserve(Count);
//
//			TArray<FVector> Positions;
//			Positions.Reserve(Count);
//
//			for (int32 i = 0; i < Count; ++i)
//			{
//				const FVegetationPointData& Data = PointDataList[StartIdx + i];
//				Positions.Add(FVector(Data.Long, Data.Lat, 0));
//
//				FSamplerMeta M;
//				M.id = Data.Id;
//				M.CleanedName = Data.Model.Replace(TEXT(" "), TEXT("")).ToLower();
//				M.Scale = Data.Scale;
//				M.Rotation = Data.Rotation;
//				M.Source = &Data;
//				MetaPerIndex.Add(M);
//			}
//
//			FCesiumSampleHeightMostDetailedCallback CesiumCallback;
//			CesiumCallback.BindLambda(
//				[this, CleanedName, PerTypeHISM, MetaPerIndex, HISM](ACesium3DTileset*, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& Warnings)
//				{
//
//					if (Warnings.Num() > 0) {
//						for (const FString& W : Warnings) {
//							UE_LOG(LogTemp, Error, TEXT("Cesium Warning: %s"), *W);
//						}
//					}
//
//					TArray<FCesiumSampleHeightResult> ResultsCopy = Results;
//
//					Async(EAsyncExecution::ThreadPool, [this, PerTypeHISM, ResultsCopy, MetaPerIndex, CleanedName, HISM]()
//						{
//							TMap<FString, TArray<FTransform>> PerTypeTransforms;
//							PerTypeTransforms.Reserve(PerTypeHISM.Num());
//
//							const int32 N = FMath::Min(ResultsCopy.Num(), MetaPerIndex.Num());
//							PerTypeTransforms.Reserve(32);
//
//							for (int32 i = 0; i < N; i++) {
//								const auto& R = ResultsCopy[i];
//								if (!R.SampleSuccess) {
//									const FSamplerMeta& M = MetaPerIndex[i];
//									FailedSamplePoints.Add(*M.Source);
//									UE_LOG(LogTemp, Error, TEXT("AGAIN: Point Data Height Sampling Fails for Point id:%d at Long/Lat: (%f, %f)"), M.id, R.LongitudeLatitudeHeight[0], R.LongitudeLatitudeHeight[1]);
//									continue;
//								}
//
//								const FVector World = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(R.LongitudeLatitudeHeight);
//								const FSamplerMeta& M = MetaPerIndex[i];
//								const FVector S(M.Scale / 100.0f);
//								const FRotator Rot(0.0f, M.Rotation, 0.0f);
//
//								PerTypeTransforms.FindOrAdd(M.CleanedName).Emplace(Rot, World, S);
//
//								// db insert :
//								FVegetationPointData DBData = *M.Source;
//								DBData.Elev = R.LongitudeLatitudeHeight.Z;
//								InsertPointDataFeaturesToDB(DBData);
//
//							}
//
//							AsyncTask(ENamedThreads::GameThread, [this, PerTypeTransforms = MoveTemp(PerTypeTransforms), PerTypeHISM]()
//								{
//									for (const TPair<FString, TArray<FTransform>>& Pair : PerTypeTransforms) {
//										const FString& CleanedName = Pair.Key;
//										const TArray<FTransform>& Transforms = Pair.Value;
//
//										if (Transforms.Num() == 0) continue;
//
//										UHierarchicalInstancedStaticMeshComponent* const* HISMPtr = PerTypeHISM.Find(CleanedName);
//										if (!HISMPtr) continue;
//
//										UHierarchicalInstancedStaticMeshComponent* HISM = *HISMPtr;
//										HISM->AddInstances(Transforms, false, true);
//									}
//								});
//						});
//				});
//
//			Tileset->SampleHeightMostDetailed(Positions, CesiumCallback);
//		}
//	}
//
//}
//void APCGPointContent::SpawnPointDataOnTerrainUsingCesiumSampler_HISM(FVegetationPointData& Data)
//{
//	if (!CesiumGeoreference || !BlueprintRegistry || !Tileset || !ParentActor)
//	{
//		UE_LOG(LogTemp, Error, TEXT("Missing required references."));
//		return;
//	}
//
//	TArray<FVector> Positions;
//	Positions.Add(FVector(Data.Long, Data.Lat, 0)); // Z ignored for sampling
//
//	FString CleanedName = Data.Model.Replace(TEXT(" "), TEXT("")).ToLower();
//	FVector FinalScale = FVector(Data.Scale / 100.f);
//	FRotator FinalRotation = FRotator(0.0f, Data.Rotation, 0.0f);
//
//
//	FCesiumSampleHeightMostDetailedCallback CesiumCallback;
//	CesiumCallback.BindLambda(
//		[this, CleanedName, FinalScale, FinalRotation, &Data](ACesium3DTileset*, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& Warnings)
//		{
//			if (Results.Num() == 0 || !Results[0].SampleSuccess)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("Failed to sample height for %s"), *CleanedName);
//				return;
//			}
//			if (!CesiumGeoreference) return;
//
//			// Step 1: Cesium world transform
//			const FVector WorldLocation = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(
//				Results[0].LongitudeLatitudeHeight);
//
//
//			// Step 2: Retrieve or extract mesh
//			UStaticMesh* MeshToUse = StaticMeshesPerType.FindRef(CleanedName);
//			if (!MeshToUse)
//			{
//				TSubclassOf<AActor> MatchedBPClass = nullptr;
//				for (const TSoftClassPtr<AActor>& SoftBP : BlueprintRegistry->BlueprintClasses)
//				{
//					FString AssetName = SoftBP.GetAssetName().ToLower();
//					AssetName.RemoveFromEnd(TEXT("_c"));
//
//					if (AssetName.Equals("pd_" + CleanedName))
//					{
//						MatchedBPClass = SoftBP.LoadSynchronous();
//						break;
//					}
//				}
//
//
//				if (!MatchedBPClass)
//				{
//					UE_LOG(LogTemp, Error, TEXT("Blueprint not found for type: %s"), *CleanedName);
//					return;
//				}
//
//				MeshToUse = ExtractMeshFromBlueprint(MatchedBPClass);
//				if (!MeshToUse)
//				{
//					UE_LOG(LogTemp, Error, TEXT("No mesh extracted from blueprint: %s"), *CleanedName);
//					return;
//				}
//
//				StaticMeshesPerType.Add(CleanedName, MeshToUse);
//			}
//
//			Data.Elev = Results[0].LongitudeLatitudeHeight[2];
//			// InsertPointDataFeaturesToDB(Data);
//
//			UHierarchicalInstancedStaticMeshComponent* HISM = nullptr;
//
//			if (!InstancedMeshMap.Contains(CleanedName))
//			{
//				HISM = NewObject<UHierarchicalInstancedStaticMeshComponent>(ParentActor);
//				HISM->SetStaticMesh(MeshToUse);
//				HISM->AttachToComponent(ParentActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
//				HISM->RegisterComponent();
//				AddInstanceComponent(HISM);
//				InstancedMeshMap.Add(CleanedName, HISM);
//			}
//			else
//			{
//				HISM = InstancedMeshMap[CleanedName];
//			}
//
//			// Step 4: Add the instance
//			FTransform InstanceTransform(FinalRotation, WorldLocation, FinalScale);
//			HISM->AddInstance(InstanceTransform, true);
//
//			//APCGPointContent::TotalPointDataPoints++;
//
//			//if (APCGPointContent::TotalPointDataPoints!=0 && ExpectedTotalPoints == APCGPointContent::TotalPointDataPoints) {
//			//    FTimespan Elapsed = FDateTime::UtcNow() - StartTime;
//
//			//    GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Green, FString::Printf(TEXT("Total Point Data Points: %d"), TotalPointDataPoints));
//			//    GEngine->AddOnScreenDebugMessage(-1, 5.0, FColor::Red, FString::Printf(TEXT("Total Time(s) Point Data: %f"), Elapsed.GetTotalSeconds()));
//
//
//			//    UE_LOG(LogTemp, Log, TEXT("Total Point Data Points are: %d"), TotalPointDataPoints);
//			//    UE_LOG(LogTemp, Log, TEXT("Total Execution Time(Point Data): %.2f"), Elapsed.GetTotalSeconds());
//
//			//    TotalPointDataPoints = 0;
//			//    ExpectedTotalPoints = 0;
//			//    StartTime = FDateTime::MinValue();
//			//    bTimerStarted = false;
//			//}
//
//
//
//			UE_LOG(LogTemp, Log, TEXT("Instanced %s at %s"), *CleanedName, *WorldLocation.ToString());
//
//			for (const FString& Warn : Warnings)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("Cesium warning: %s"), *Warn);
//			}
//		});
//
//	Tileset->SampleHeightMostDetailed(Positions, CesiumCallback);
//}
//void APCGPointContent::SpawnPointDataOnTerrainUsingCesiumSampler(const FVegetationPointData& Data)
//{
//	if (!CesiumGeoreference || !BlueprintRegistry || !Tileset)
//	{
//		UE_LOG(LogTemp, Error, TEXT("CesiumGeoreference, Tileset, or BlueprintRegistry is null."));
//		return;
//	}
//
//	TArray<FVector> Positions;
//	Positions.Add(FVector(Data.Long, Data.Lat, 0)); // Z is ignored by Cesium sampler
//
//	// Pre-bind data
//	FString CleanedName = Data.Model.Replace(TEXT(" "), TEXT("")).ToLower();
//	FVector FinalScale = FVector(Data.Scale / 100.f);
//	FRotator FinalRotation = FRotator(0.0f, Data.Rotation + 90.0f, 0.0f);
//
//	FCesiumSampleHeightMostDetailedCallback CesiumCallback;
//	CesiumCallback.BindLambda(
//		[this, CleanedName, FinalScale, FinalRotation, Data](ACesium3DTileset* /*Tileset*/, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& Warnings)
//		{
//			if (Results.Num() == 0 || !Results[0].SampleSuccess)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("Failed to sample terrain height for model: %s"), *CleanedName);
//				return;
//			}
//
//			if (!CesiumGeoreference) return;
//			const FCesiumSampleHeightResult& Result = Results[0];
//			FVector WorldLocation = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(Result.LongitudeLatitudeHeight);
//
//			// Load blueprint from registry
//			TSubclassOf<AActor> MatchedBPClass = nullptr;
//			for (const TSoftClassPtr<AActor>& SoftBP : BlueprintRegistry->BlueprintClasses)
//			{
//				FString AssetName = SoftBP.GetAssetName().ToLower();
//				AssetName.RemoveFromEnd(TEXT("_c"));
//
//				if (AssetName.Equals("pd_" + CleanedName))
//				{
//					MatchedBPClass = SoftBP.LoadSynchronous();
//					break;
//				}
//			}
//
//
//
//			if (!MatchedBPClass)
//			{
//				UE_LOG(LogTemp, Error, TEXT("No blueprint found in registry for model: %s"), *CleanedName);
//				return;
//			}
//
//			// Spawn actor
//			FActorSpawnParameters SpawnParams;
//			AActor* Spawned = GetWorld()->SpawnActor<AActor>(MatchedBPClass, WorldLocation, FinalRotation, SpawnParams);
//			if (Spawned && ParentActor && ParentActor->GetRootComponent())
//			{
//				Spawned->SetActorScale3D(FinalScale);
//				Spawned->AttachToComponent(ParentActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
//				UE_LOG(LogTemp, Log, TEXT("Spawned %s at %s with Cesium height: %.2f"), *CleanedName, *WorldLocation.ToString(), Result.LongitudeLatitudeHeight[2]);
//			}
//
//			for (const FString& Warn : Warnings)
//			{
//				UE_LOG(LogTemp, Warning, TEXT("Cesium Warning: %s"), *Warn);
//			}
//		});
//
//	Tileset->SampleHeightMostDetailed(Positions, CesiumCallback);
//}
//void APCGPointContent::SpawnPointDataOnTerrainUsingElevData(const FVegetationPointData& Data)
//{
//	if (!CesiumGeoreference || !BlueprintRegistry)
//	{
//		UE_LOG(LogTemp, Error, TEXT("CesiumGeoreference or BlueprintRegistry is null."));
//		return;
//	}
//
//	// Step 1: Convert LLH to Unreal World Location
//	FVector LLH(static_cast<double>(Data.Long), static_cast<double>(Data.Lat), static_cast<double>(Data.Elev));
//	FVector WorldLocation = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(LLH);
//
//	// Step 2: Match model name
//	FString CleanedName = Data.Model.Replace(TEXT(" "), TEXT("")).ToLower();
//	TSubclassOf<AActor> MatchedBPClass = nullptr;
//
//	for (const TSoftClassPtr<AActor>& SoftBP : BlueprintRegistry->BlueprintClasses)
//	{
//		FString AssetName = SoftBP.GetAssetName().ToLower();
//		AssetName.RemoveFromEnd(TEXT("_c")); // remove _C suffix if present
//
//		if (AssetName.Equals("pd_" + CleanedName))
//		{
//			MatchedBPClass = SoftBP.LoadSynchronous();
//			break;
//		}
//	}
//
//	if (!MatchedBPClass)
//	{
//		UE_LOG(LogTemp, Error, TEXT("No blueprint found in registry for model: %s"), *CleanedName);
//		return;
//	}
//
//	// Step 3: Spawn actor with position, scale, and rotation
//	FVector FinalScale = FVector(Data.Scale / 100.f);
//	FRotator FinalRotation = FRotator(0.0f, Data.Rotation, 0.0f);
//	FActorSpawnParameters SpawnParams;
//
//	AActor* Spawned = GetWorld()->SpawnActor<AActor>(MatchedBPClass, WorldLocation, FinalRotation, SpawnParams);
//	if (Spawned && ParentActor && ParentActor->GetRootComponent())
//	{
//		Spawned->SetActorScale3D(FinalScale);
//		Spawned->AttachToComponent(ParentActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
//		UE_LOG(LogTemp, Log, TEXT("Spawned %s at %s"), *CleanedName, *WorldLocation.ToString());
//	}
//}
//void APCGPointContent::SpawnPointDataOnTerrainUsingElevData_HISM(const FVegetationPointData& Data) {
//	if (!CesiumGeoreference || !BlueprintRegistry)
//	{
//		UE_LOG(LogTemp, Error, TEXT("CesiumGeoreference or BlueprintRegistry is null."));
//		return;
//	}
//	FVector LLH(static_cast<double>(Data.Long), static_cast<double>(Data.Lat), static_cast<double>(Data.Elev));
//	FVector WorldLocation = CesiumGeoreference->TransformLongitudeLatitudeHeightPositionToUnreal(LLH);
//	FString CleanedName = Data.Model.Replace(TEXT(" "), TEXT("")).ToLower();
//	FVector FinalScale = FVector(Data.Scale / 100.f);
//	FRotator FinalRotation = FRotator(0.0f, Data.Rotation, 0.0f);
//	TSubclassOf<AActor> MatchedBPClass = nullptr;
//	UStaticMesh* MeshToUse = StaticMeshesPerType.FindRef(CleanedName);
//
//	for (const TSoftClassPtr<AActor>& SoftBP : BlueprintRegistry->BlueprintClasses)
//	{
//		FString AssetName = SoftBP.GetAssetName().ToLower();
//		AssetName.RemoveFromEnd(TEXT("_c")); // remove _C suffix if present
//
//		if (AssetName.Equals("pd_" + CleanedName))
//		{
//			MatchedBPClass = SoftBP.LoadSynchronous();
//			break;
//		}
//	}
//	if (!MatchedBPClass)
//	{
//		UE_LOG(LogTemp, Error, TEXT("No blueprint found in registry for model: %s"), *CleanedName);
//		return;
//	}
//	MeshToUse = ExtractMeshFromBlueprint(MatchedBPClass);
//	if (!MeshToUse)
//	{
//		UE_LOG(LogTemp, Error, TEXT("No mesh extracted from blueprint: %s"), *CleanedName);
//		return;
//	}
//	StaticMeshesPerType.Add(CleanedName, MeshToUse);
//
//	UHierarchicalInstancedStaticMeshComponent* HISM = nullptr;
//
//	if (!InstancedMeshMap.Contains(CleanedName))
//	{
//		HISM = NewObject<UHierarchicalInstancedStaticMeshComponent>(ParentActor);
//		HISM->SetStaticMesh(MeshToUse);
//		HISM->AttachToComponent(ParentActor->GetRootComponent(), FAttachmentTransformRules::KeepWorldTransform);
//		HISM->RegisterComponent();
//		//HISM->SetCullDistance(200.0f);
//		AddInstanceComponent(HISM);
//		InstancedMeshMap.Add(CleanedName, HISM);
//	}
//	else
//	{
//		HISM = InstancedMeshMap[CleanedName];
//	}
//	FTransform InstanceTransform(FinalRotation, WorldLocation, FinalScale);
//	HISM->AddInstance(InstanceTransform, true);
//}
//void APCGPointContent::SetIsFileChanged(bool InisFileChanged) {
//	isFileChanged = InisFileChanged;
//}
