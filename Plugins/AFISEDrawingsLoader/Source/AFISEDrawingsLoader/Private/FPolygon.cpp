#include "FPolygon.h"
#include "LineDrawerActor.h"




FPolygon::FPolygon(const TArray<FVector>& InLatLongHeight)
	: LatLongHeightPoints(InLatLongHeight), LineWidth(1)
{

	//for (const FVector& LatLong : LatLongHeightPoints)
	//{
	//	WorldPoints.Add(Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(FVector(LatLong.X, LatLong.Y, 10000)));
	//}
	MaterialPath = "/Game/Materials/Drawings/M_Polygon";
	Material = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *MaterialPath));
	if (Material)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(Material, nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Material at path: %s"), *MaterialPath);
	}

	ProjectionMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *ProjectionMaterialPath));
	if (ProjectionMaterial)
	{
		DynamicProjectionMaterial = UMaterialInstanceDynamic::Create(ProjectionMaterial, nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to load Projection Material at path: %s"), *ProjectionMaterialPath);
	}
}
FString FPolygon::GetShapeType() const { return TEXT("Polygon"); }
FVector FPolygon::GetWorldPosition() const { 
	if (!CenterAvgPoint.IsZero()) return CenterAvgPoint;
	const int32 N = WorldPoints.Num();
	if (N == 0) return FVector::ZeroVector;
	const bool bClosed = (N > 1 && WorldPoints[0].Equals(WorldPoints[N - 1], KINDA_SMALL_NUMBER));
	const int32 Count = bClosed ? (N - 1) : N;

	FVector Sum = FVector::ZeroVector;
	for (int32 i = 0; i < Count; ++i)
	{
		Sum += WorldPoints[i];
	}
	CenterAvgPoint = Sum / Count;
	return CenterAvgPoint;

	//return WorldPoints.Num() > 0 ? WorldPoints[0] : FVector::ZeroVector; 
}

FVector FPolygon::GetLatLongHeightPosition() const { return LatLongHeightPoints.Num() > 0 ? LatLongHeightPoints[0] : FVector::ZeroVector; }
TArray<FVector> FPolygon::GetLatLongHeightPositions() {
	return LatLongHeightPoints;
}
void FPolygon::CreateMeshes(UWorld* World) {

	if (!World || !Material || WorldPoints.Num() < 2) return;

	const float HalfWidth = LineWidth;
	const float HalfHeight = LineHeight;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;
	TArray<FProcMeshTangent> Tangents;
	int32 VertexIndex = 0;

	if (LineMeshComponent && WallMeshComponent)
	{
		LineMeshComponent->DestroyComponent();
		WallMeshComponent->DestroyComponent();
		LineMeshComponent = nullptr;
		WallMeshComponent = nullptr;
	}

	if (DynamicMaterial) {
		DynamicMaterial->SetVectorParameterValue(FName("BaseColor"), LineColor);
	}
	if (DynamicProjectionMaterial) {
		DynamicProjectionMaterial->SetVectorParameterValue(FName("ProjectionColor"), LineColor);
	}
	// --- Compute Corner Offsets ---
	struct FLineCorner { FVector Left; FVector Right; };
	TArray<FLineCorner> Corners;
	Corners.SetNum(WorldPoints.Num());

	for (int32 i = 0; i < WorldPoints.Num(); ++i)
	{
		FVector PrevDir, NextDir;

		if (i == 0)
		{
			NextDir = (WorldPoints[i + 1] - WorldPoints[i]).GetSafeNormal();
			FVector Right = FVector::CrossProduct(NextDir, FVector::UpVector).GetSafeNormal();
			Corners[i].Right = Right * HalfWidth;
			Corners[i].Left = -Right * HalfWidth;
		}
		else if (i == WorldPoints.Num() - 1)
		{
			PrevDir = (WorldPoints[i] - WorldPoints[i - 1]).GetSafeNormal();
			FVector Right = FVector::CrossProduct(PrevDir, FVector::UpVector).GetSafeNormal();
			Corners[i].Right = Right * HalfWidth;
			Corners[i].Left = -Right * HalfWidth;
		}
		else
		{
			PrevDir = (WorldPoints[i] - WorldPoints[i - 1]).GetSafeNormal();
			NextDir = (WorldPoints[i + 1] - WorldPoints[i]).GetSafeNormal();

			FVector PrevRight = FVector::CrossProduct(PrevDir, FVector::UpVector).GetSafeNormal();
			FVector NextRight = FVector::CrossProduct(NextDir, FVector::UpVector).GetSafeNormal();

			FVector AvgRight = (PrevRight + NextRight).GetSafeNormal();
			float Dot = FVector::DotProduct(AvgRight, FVector::CrossProduct(NextDir, FVector::UpVector));
			float MiterLength = FMath::Abs(Dot) > KINDA_SMALL_NUMBER ? HalfWidth / Dot : HalfWidth;

			// Clamp miter to avoid spikes
			const float MaxMiter = HalfWidth * 2.0f;
			MiterLength = FMath::Clamp(MiterLength, 0.0f, MaxMiter);

			Corners[i].Right = AvgRight * MiterLength;
			Corners[i].Left = -AvgRight * MiterLength;
		}
	}

	// --- Build Mesh Between Segments ---
	for (int32 i = 0; i < WorldPoints.Num() - 1; ++i)
	{
		FVector A = WorldPoints[i];
		FVector B = WorldPoints[i + 1];

		FVector RT0 = A + Corners[i].Right;
		FVector LT0 = A + Corners[i].Left;
		FVector RT1 = B + Corners[i + 1].Right;
		FVector LT1 = B + Corners[i + 1].Left;

		FVector RB0 = RT0 - FVector(0, 0, HalfHeight);
		FVector LB0 = LT0 - FVector(0, 0, HalfHeight);
		FVector RB1 = RT1 - FVector(0, 0, HalfHeight);
		FVector LB1 = LT1 - FVector(0, 0, HalfHeight);

		// Top face
		Vertices.Append({ RT0, LT0, RT1, LT1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex + 2, VertexIndex + 3, VertexIndex + 1
			});
		VertexIndex += 4;

		// Bottom face
		Vertices.Append({ RB0, RB1, LB0, LB1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex + 2, VertexIndex + 3, VertexIndex + 1
			});
		VertexIndex += 4;

		// Side 1 (outer)
		Vertices.Append({ RT0, RB0, RB1, RT1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;

		// Side 2 (inner)
		Vertices.Append({ LT1, LB1, LB0, LT0 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;

		// Forward face
		Vertices.Append({ RT1, RB1, LB1, LT1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;

		// Back face
		Vertices.Append({ LT0, LB0, RB0, RT0 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;
	}

	// --- Apply Vertex Attributes ---
	for (int32 i = 0; i < Vertices.Num(); ++i)
	{
		Normals.Add(FVector::UpVector);
		UVs.Add(FVector2D(0, 0));
		Colors.Add(LineColor);
		Tangents.Add(FProcMeshTangent(1, 0, 0));
	}

	// --- Mesh Component ---
	if (!LineMeshComponent)
	{
		LineMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
		if (!LineMeshComponent) return;

		LineMeshComponent->RegisterComponent();
		LineMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		LineMeshComponent->ClearAllMeshSections();
	}

	LineMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
	LineMeshComponent->SetMaterial(0, DynamicMaterial);
	LineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LineMeshComponent->SetCastShadow(false);
	LineMeshComponent->SetCastInsetShadow(false);
	LineMeshComponent->SetCastHiddenShadow(false);


	// --- Wall Projection ---
	TArray<FVector> LatLongPoints3d;
	for (const FVector& LatLong : LatLongHeightPoints)
	{
		LatLongPoints3d.Add(FVector(LatLong.X, LatLong.Y, 0));
	}


	if (!WallMeshComponent)
	{
		WallMeshComponent = NewObject<UProceduralMeshComponent>(World->GetWorldSettings());
		if (!WallMeshComponent) return;

		WallMeshComponent->RegisterComponent();
		WallMeshComponent->AttachToComponent(World->GetWorldSettings()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	}
	else
	{
		WallMeshComponent->ClearAllMeshSections();
	}

	WallMeshComponent->SetMaterial(0, DynamicProjectionMaterial);
	WallMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);


	FCesiumSampleHeightMostDetailedCallback CesiumCallback;
	CesiumCallback.BindLambda(
		[this, World](ACesium3DTileset*, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>&)
		{
			if (Results.Num() != WorldPoints.Num()) return;

			TArray<FVector> Vertices;
			TArray<int32> Triangles;
			TArray<FVector> Normals;
			TArray<FVector2D> UVs;
			TArray<FLinearColor> Colors;
			TArray<FProcMeshTangent> Tangents;
			int32 VertexIndex = 0;

			for (int32 i = 0; i < Results.Num() - 1; ++i)
			{
				if (!Results[i].SampleSuccess || !Results[i + 1].SampleSuccess) continue;

				FVector TopA = WorldPoints[i];
				FVector TopB = WorldPoints[i + 1];
				FVector BottomA = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i].LongitudeLatitudeHeight);
				FVector BottomB = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(Results[i + 1].LongitudeLatitudeHeight);

				Vertices.Append({ TopA, BottomA, BottomB, TopB });
				Triangles.Append({
					VertexIndex, VertexIndex + 2, VertexIndex + 1,
					VertexIndex, VertexIndex + 3, VertexIndex + 2
					});

				for (int j = 0; j < 4; ++j)
				{
					Normals.Add(FVector::UpVector);
					UVs.Add(FVector2D(0, 0));
					Colors.Add(LineColor);
					Tangents.Add(FProcMeshTangent(1, 0, 0));
				}

				VertexIndex += 4;
			}
			WallMeshComponent->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colors, Tangents, true);
		});

	Tileset->SampleHeightMostDetailed(LatLongPoints3d, CesiumCallback);
}
void FPolygon::Draw(UWorld* World)
{

	if (WorldPoints.Num() > 0)
	{
		CreateMeshes(World);
	}
	else {
		SampleHeightAboveTerrain(LatLongHeightPoints,
			[this, World]( TArray<FVector>& SampledWorldPoints,  TArray<FVector> SampleWorldProjectionPoints)
			{
				WorldPoints = SampledWorldPoints;
				CreateMeshes(World);
			});
	}

}
void FPolygon::SetLineColor(const FLinearColor& InColor) { LineColor = InColor; }
void FPolygon::SetLineWidth(int32 InWidth) { LineWidth = InWidth* BaseLineWidth; }
void FPolygon::SetLineHeight(int32 InHeight)
{
	LineHeight = InHeight * BaseLineHeight;
}
void FPolygon::SetFillColor(const FLinearColor&) {}
void FPolygon::LogInfo() const
{
}
void FPolygon::Clear()
{
	if (LineMeshComponent && WallMeshComponent)
	{
		LineMeshComponent->DestroyComponent();
		WallMeshComponent->DestroyComponent();
		LineMeshComponent = nullptr;
		WallMeshComponent = nullptr;
	}
}
void FPolygon::SetProjectionVisibility(bool bVisible)
{

	if (WallMeshComponent)
	{
		WallMeshComponent->SetVisibility(bVisible, true);
		WallMeshComponent->SetHiddenInGame(!bVisible);
	}
}
void FPolygon::SetVisibility(bool bVisible)
{
	if (WallMeshComponent && LineMeshComponent)
	{
		WallMeshComponent->SetVisibility(bVisible, true);
		WallMeshComponent->SetHiddenInGame(!bVisible);
		LineMeshComponent->SetVisibility(bVisible, true);
		LineMeshComponent->SetHiddenInGame(!bVisible);
	}

}
void FPolygon::UpdateScale(UWorld* World)
{

	const float HalfWidth = LineWidth;
	const float HalfHeight = LineHeight;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector> Normals;
	TArray<FVector2D> UVs;
	TArray<FLinearColor> Colors;
	TArray<FProcMeshTangent> Tangents;
	int32 VertexIndex = 0;

	// --- Compute Corner Offsets ---
	struct FLineCorner { FVector Left; FVector Right; };
	TArray<FLineCorner> Corners;
	Corners.SetNum(WorldPoints.Num());

	for (int32 i = 0; i < WorldPoints.Num(); ++i)
	{
		FVector PrevDir, NextDir;

		if (i == 0)
		{
			NextDir = (WorldPoints[i + 1] - WorldPoints[i]).GetSafeNormal();
			FVector Right = FVector::CrossProduct(NextDir, FVector::UpVector).GetSafeNormal();
			Corners[i].Right = Right * HalfWidth;
			Corners[i].Left = -Right * HalfWidth;
		}
		else if (i == WorldPoints.Num() - 1)
		{
			PrevDir = (WorldPoints[i] - WorldPoints[i - 1]).GetSafeNormal();
			FVector Right = FVector::CrossProduct(PrevDir, FVector::UpVector).GetSafeNormal();
			Corners[i].Right = Right * HalfWidth;
			Corners[i].Left = -Right * HalfWidth;
		}
		else
		{
			PrevDir = (WorldPoints[i] - WorldPoints[i - 1]).GetSafeNormal();
			NextDir = (WorldPoints[i + 1] - WorldPoints[i]).GetSafeNormal();

			FVector PrevRight = FVector::CrossProduct(PrevDir, FVector::UpVector).GetSafeNormal();
			FVector NextRight = FVector::CrossProduct(NextDir, FVector::UpVector).GetSafeNormal();

			FVector AvgRight = (PrevRight + NextRight).GetSafeNormal();
			float Dot = FVector::DotProduct(AvgRight, FVector::CrossProduct(NextDir, FVector::UpVector));
			float MiterLength = FMath::Abs(Dot) > KINDA_SMALL_NUMBER ? HalfWidth / Dot : HalfWidth;

			// Clamp miter to avoid spikes
			const float MaxMiter = HalfWidth * 2.0f;
			MiterLength = FMath::Clamp(MiterLength, 0.0f, MaxMiter);

			Corners[i].Right = AvgRight * MiterLength;
			Corners[i].Left = -AvgRight * MiterLength;
		}
	}

	// --- Build Mesh Between Segments ---
	for (int32 i = 0; i < WorldPoints.Num() - 1; ++i)
	{
		FVector A = WorldPoints[i];
		FVector B = WorldPoints[i + 1];

		FVector RT0 = A + Corners[i].Right;
		FVector LT0 = A + Corners[i].Left;
		FVector RT1 = B + Corners[i + 1].Right;
		FVector LT1 = B + Corners[i + 1].Left;

		FVector RB0 = RT0 - FVector(0, 0, HalfHeight);
		FVector LB0 = LT0 - FVector(0, 0, HalfHeight);
		FVector RB1 = RT1 - FVector(0, 0, HalfHeight);
		FVector LB1 = LT1 - FVector(0, 0, HalfHeight);

		// Top face
		Vertices.Append({ RT0, LT0, RT1, LT1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex + 2, VertexIndex + 3, VertexIndex + 1
			});
		VertexIndex += 4;

		// Bottom face
		Vertices.Append({ RB0, RB1, LB0, LB1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex + 2, VertexIndex + 3, VertexIndex + 1
			});
		VertexIndex += 4;

		// Side 1 (outer)
		Vertices.Append({ RT0, RB0, RB1, RT1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;

		// Side 2 (inner)
		Vertices.Append({ LT1, LB1, LB0, LT0 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;

		// Forward face
		Vertices.Append({ RT1, RB1, LB1, LT1 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;

		// Back face
		Vertices.Append({ LT0, LB0, RB0, RT0 });
		Triangles.Append({
			VertexIndex, VertexIndex + 2, VertexIndex + 1,
			VertexIndex, VertexIndex + 3, VertexIndex + 2
			});
		VertexIndex += 4;
	}

	// --- Apply Vertex Attributes ---
	for (int32 i = 0; i < Vertices.Num(); ++i)
	{
		Normals.Add(FVector::UpVector);
		UVs.Add(FVector2D(0, 0));
		Colors.Add(LineColor);
		Tangents.Add(FProcMeshTangent(1, 0, 0));
	}

	LineMeshComponent->UpdateMeshSection_LinearColor(0, Vertices, Normals, UVs, Colors, Tangents, true);
}



// Some helper functions

//void FPolygon::Draw(UWorld* World, UMaterialInterface* Material)
//{
//	if (!World || !Material) return;
//
//	TArray<FVector> Points;
//	for (int32 i = 0; i < WorldPoints.Num(); ++i)
//	{
//		Points.Add(WorldPoints[i]);
//	}
//
//	TArray<FVector> LatLongPoints3d;
//	for (const FVector2D& LatLong : LatLongPoints)
//	{
//		LatLongPoints3d.Add(FVector(LatLong.X, LatLong.Y, 0));
//	}
//
//	// Spawn the Line Drawer actor
//	ALineDrawerActor* LineDrawer = World->SpawnActor<ALineDrawerActor>(FVector::ZeroVector, FRotator::ZeroRotator);
//	if (LineDrawer)
//	{
//		// Update the line with the points and material
//		LineDrawer->UpdateLine(Points, Material);
//	}
//
//	FString MaterialPath = "/Game/Materials/Drawings/M_Plane";
//	UMaterialInterface* PlaneMaterial = Cast<UMaterialInterface>(StaticLoadObject(UMaterialInterface::StaticClass(), nullptr, *MaterialPath));
//	if (!PlaneMaterial) return;
//
//	FCesiumSampleHeightMostDetailedCallback CesiumCallback;
//
//	// Bind lambda safely
//	CesiumCallback.BindLambda(
//		[this, World, PlaneMaterial](ACesium3DTileset* /*Tileset*/, const TArray<FCesiumSampleHeightResult>& Results, const TArray<FString>& /*Warnings*/)
//		{
//			if (Results.Num() != WorldPoints.Num())
//			{
//				UE_LOG(LogTemp, Error, TEXT("Mismatch between WorldPoints (%d) and Results (%d)"), WorldPoints.Num(), Results.Num());
//				return;
//			}
//
//			for (int32 i = 0; i < Results.Num() - 1; ++i)
//			{
//				const auto& ResultA = Results[i];
//				const auto& ResultB = Results[i + 1];
//
//				if (ResultA.SampleSuccess && ResultB.SampleSuccess)
//				{
//					FVector GroundA = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(ResultA.LongitudeLatitudeHeight);
//					FVector GroundB = Georeference->TransformLongitudeLatitudeHeightPositionToUnreal(ResultB.LongitudeLatitudeHeight);
//
//					// Use the original WorldPoints for top, sampled heights for bottom
//					SpawnWallQuad(World, WorldPoints[i], GroundA, WorldPoints[i + 1], GroundB, PlaneMaterial);
//				}
//				else
//				{
//					UE_LOG(LogTemp, Warning, TEXT("Skipping wall at segment %d due to failed height sampling"), i);
//				}
//			}
//		});
//
//	Tileset->SampleHeightMostDetailed(LatLongPoints3d, CesiumCallback);
//
//}

//void FPolygon::SpawnSphereAtLocation(UWorld* World, const FVector& Location)
//{
//	AStaticMeshActor* SphereActor = World->SpawnActor<AStaticMeshActor>(Location, FRotator::ZeroRotator);
//	if (!SphereActor) return;
//
//	UStaticMesh* SphereMesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Engine/BasicShapes/Sphere.Sphere"));
//	if (!SphereMesh) return;
//
//	UMaterialInterface* SphereMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/Drawings/M_SphereMaterial"));
//
//	UStaticMeshComponent* MeshComp = SphereActor->GetStaticMeshComponent();
//	MeshComp->SetStaticMesh(SphereMesh);
//	MeshComp->SetMaterial(0, SphereMaterial);
//
//	MeshComp->SetWorldScale3D(FVector(12000.00f, 12000.00f, 12000.00f));
//
//	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
//	SphereActor->SetMobility(EComponentMobility::Movable);
//
//
//}

