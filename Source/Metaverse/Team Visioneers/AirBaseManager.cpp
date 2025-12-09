#include "AirBaseManager.h"
#include "FShapeFileReader.h"
#include "../Team Visioneers/DisplayManager.h"
#include <Metaverse/Team RenderStorm/ModeManager.h>

AAirBaseManager* AAirBaseManager::instance = nullptr;
// Sets default values
AAirBaseManager::AAirBaseManager()
{

	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/Blueprints/WBP_PakPinLabel"));
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetIndiaClass(TEXT("/Game/Blueprints/WBP_IndPinLabel"));
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassWithoutBG(TEXT("/Game/Blueprints/WBP_PakPinLabelWithoutBG"));

	labelWidgetClass = WidgetClass.Class;
	labelWidgetIndiaClass = WidgetIndiaClass.Class;
	labelWidgetClassWithoutBG = WidgetClassWithoutBG.Class;
}

AAirBaseManager* AAirBaseManager::getInstance()
{
	return instance;
}

//void AAirBaseManager::LoadAirBaseData()
//{
//	 FShapeFileReader::LoadDllForGDAL();
//
//	 FString ShapefileFolder = FPaths::ProjectContentDir() + TEXT("Shapefiles/bases/");
//	 FPaths::NormalizeDirectoryName(ShapefileFolder);
//
//	 if (!FPaths::DirectoryExists(ShapefileFolder))
//	 {
//	 	 UE_LOG(LogTemp, Error, TEXT("Shapefile folder does not exist: %s"), *ShapefileFolder);
//	 	 return;
//	 }
//
//	 TArray<FString> ShapefilePaths;
//	 IFileManager::Get().FindFilesRecursive(ShapefilePaths, *ShapefileFolder, TEXT("*.shp"), true, false);
//
//	 if (ShapefilePaths.Num() == 0)
//	 {
//	 	 UE_LOG(LogTemp, Warning, TEXT(" No shapefiles found in directory: %s"), *ShapefileFolder);
//	 	 return;
//	 }
//
//	 for (const FString& ShapefilePath : ShapefilePaths)
//	 {
//	 	 UE_LOG(LogTemp, Log, TEXT(" Loading shapefile: %s"), *ShapefilePath);
//
//	 	 FPakAirBaseLocationData PakAirBaseRawData = FShapeFileReader::ReadPakAirbaseShapeFile(ShapefilePath);
//
//	 	 InitializeAirbaseData(PakAirBaseRawData);
//	 }
//}


void AAirBaseManager::LoadData()
{
	 FShapeFileReader::LoadDllForGDAL();

	 FString ShapefileFolder = FPaths::ProjectContentDir() + TEXT("Shapefiles/UpdatedData/");
	 FPaths::NormalizeDirectoryName(ShapefileFolder);

	 if (!FPaths::DirectoryExists(ShapefileFolder))
	 {
	 	 UE_LOG(LogTemp, Error, TEXT("Shapefile folder does not exist: %s"), *ShapefileFolder);
	 	 return;
	 }

	 TArray<FString> ShapefilePaths;
	 IFileManager::Get().FindFilesRecursive(ShapefilePaths, *ShapefileFolder, TEXT("*.shp"), true, false);

	 if (ShapefilePaths.Num() == 0)
	 {
	 	 UE_LOG(LogTemp, Warning, TEXT(" No shapefiles found in directory: %s"), *ShapefileFolder);
	 	 return;
	 }

	 for (const FString& ShapefilePath : ShapefilePaths)
	 {
	 	 UE_LOG(LogTemp, Log, TEXT(" Loading shapefile: %s"), *ShapefilePath);

		 FShapeRawData RawData = FShapeFileReader::ReadShapefileRawData(ShapefilePath);

	 	 InitializeData(RawData);
	 }
}


void AAirBaseManager::InitializeData(const FShapeRawData& Raw)
{
	 PinParentActor = GetWorld()->SpawnActor<AActor>(AActor::StaticClass());
	 if (PinParentActor && !PinParentActor->GetRootComponent()) {
#if WITH_EDITOR
	 	 PinParentActor->SetActorLabel(TEXT("LandMarks"));
#endif
	 	 USceneComponent* Root = NewObject<USceneComponent>(PinParentActor);
	 	 Root->RegisterComponent();
	 	 PinParentActor->SetRootComponent(Root);
	 }
	 
	 for (int32 i = 0; i < Raw.Attributes.Num(); ++i)
	 {
	 	 const auto& A = Raw.Attributes[i];

	 	 auto GetSafeString = [&](const FString& key) ->FString {
	 	 	 return A.Contains(key) ? A[key] : TEXT("");
	 	 	 };

	 	 auto GetSafeInt = [&](const FString& key) -> int32 {
	 	 	 return A.Contains(key) ? FCString::Atoi(*A[key]) : 0;

	 	 	 };

	 	 auto GetSafeFloat = [&](const FString& key) -> double {
	 	 	 return A.Contains(key) ? FCString::Atod(*A[key]) : 0.0;

	 	 	 };

	 	 temp.Name = A["Name"];
	 	 temp.Lat = GetSafeFloat("lat");
	 	 temp.Long = GetSafeFloat("long");
	 	 temp.Abbreviation = GetSafeString("Abbr_3");
		 temp.CountryId = GetSafeInt("CountryID");
		 temp.LayerOrder = GetSafeString("LayerOrder");
		 temp.Elev = GetSafeFloat("elev");
		 temp.Colour = GetSafeString("Colour");
		 temp.Category = GetSafeString("Category");
		 temp.TextColour = GetSafeString("TextColour");

	 	 APinActor* Pin = GetWorld()->SpawnActor<APinActor>(APinActor::StaticClass());
#if WITH_EDITOR
	 	 Pin->SetActorLabel(temp.Name);
#endif

		if (Pin && PinParentActor) {
			Pin->AttachToActor(PinParentActor, FAttachmentTransformRules::KeepRelativeTransform);
			Pin->SetOwner(PinParentActor);
			if (temp.CountryId == 165)
			{
				Pin->InitializePin(temp.Long, temp.Lat, temp.Elev, temp.Abbreviation, labelWidgetClassWithoutBG, temp.Colour, temp.Category, temp.TextColour);
				if (temp.Category.Contains("Base"))
					PakistanAirbasesList.Add(Pin);
				else
					PakistanCitiesList.Add(Pin);
				if (temp.LayerOrder.Contains("0"))
					Layer0.Add(Pin);
				if (temp.LayerOrder.Contains("1"))
					Layer1.Add(Pin);
				if (temp.LayerOrder.Contains("2"))
					Layer2.Add(Pin);
				if (temp.LayerOrder.Contains("3"))
					Layer3.Add(Pin);
				if (temp.LayerOrder.Contains("4"))
					Layer4.Add(Pin);
			}
			else {
				Pin->InitializePin(temp.Long, temp.Lat, temp.Elev, temp.Abbreviation, labelWidgetClassWithoutBG, temp.Colour, temp.Category, temp.TextColour);
				if (temp.Category.Contains("Base"))
					IndianAirbasesList.Add(Pin);
				else
					IndianCitiesList.Add(Pin);
				if (temp.LayerOrder.Contains("0"))
					Layer0.Add(Pin);
				if (temp.LayerOrder.Contains("1"))
					Layer1.Add(Pin);
				if (temp.LayerOrder.Contains("2"))
					Layer2.Add(Pin);
				if (temp.LayerOrder.Contains("3"))
					Layer3.Add(Pin);
				if (temp.LayerOrder.Contains("4"))
					Layer4.Add(Pin);
			}
			
			Pin->AttachToActor(PinParentActor, FAttachmentTransformRules::KeepRelativeTransform);
			Pin->SetOwner(PinParentActor);
		}

	 }
	 PinParentActor = nullptr;
}


void AAirBaseManager::UpdatePakistanBasePinVisibility(bool bShowPins)
{
		for (APinActor* NewPin : PakistanAirbasesList) {
			NewPin->SetActorHiddenInGame(!bShowPins);
			NewPin->SetActorTickEnabled(bShowPins);
			NewPin->setPinRotation();
		}

		for (APinActor* NewPin : IndianAirbasesList) {
			NewPin->SetActorHiddenInGame(!bShowPins);
			NewPin->SetActorTickEnabled(bShowPins);
			NewPin->setPinRotation();
		}

		UpdateVisibilityBasedOnLayer(layer);
}

void AAirBaseManager::UpdateIndianAirbasePinVisibility(bool bShowPins)
{
		for (APinActor* NewPin : IndianAirbasesList) {
			NewPin->SetActorHiddenInGame(!bShowPins);
			NewPin->SetActorTickEnabled(bShowPins);
			NewPin->setPinRotation();
		}
}

void AAirBaseManager::UpdatePakistanCitiesPinVisibility(bool bShowPins)
{
		for (APinActor* NewPin : PakistanCitiesList) {
			NewPin->SetActorHiddenInGame(!bShowPins);
			NewPin->SetActorTickEnabled(bShowPins);
			NewPin->setPinRotation();
		}

		for (APinActor* NewPin : IndianCitiesList) {
			NewPin->SetActorHiddenInGame(!bShowPins);
			NewPin->SetActorTickEnabled(bShowPins);
			NewPin->setPinRotation();
		}

		UpdateVisibilityBasedOnLayer(layer);

}

void AAirBaseManager::UpdateIndianCitiesPinVisibility(bool bShowPins)
{
		for (APinActor* NewPin : IndianCitiesList) {
			NewPin->SetActorHiddenInGame(!bShowPins);
			NewPin->SetActorTickEnabled(bShowPins);
			NewPin->setPinRotation();
		}
}

void AAirBaseManager::HideAllBases() {
	for (APinActor* NewPin : IndianAirbasesList) {
		NewPin->SetActorHiddenInGame(true);
		NewPin->SetActorTickEnabled(false);
		NewPin->setPinRotation();
	}
	for (APinActor* NewPin : PakistanAirbasesList) {
		NewPin->SetActorHiddenInGame(true);
		NewPin->SetActorTickEnabled(false);
		NewPin->setPinRotation();
	}
}


void AAirBaseManager::HideAllCapitals() {
	for (APinActor* NewPin : CapitalsList) {
		NewPin->SetActorHiddenInGame(true);
		NewPin->SetActorTickEnabled(false);
		NewPin->setPinRotation();
	}
	for (APinActor* NewPin : PakistanAirbasesList) {
		NewPin->SetActorHiddenInGame(true);
		NewPin->SetActorTickEnabled(false);
		NewPin->setPinRotation();
	}
}



void AAirBaseManager::HideAllCities() {
	for (APinActor* NewPin : IndianCitiesList) {
		NewPin->SetActorHiddenInGame(true);
		NewPin->SetActorTickEnabled(false);
		NewPin->setPinRotation();
	}
	for (APinActor* NewPin : PakistanCitiesList) {
		NewPin->SetActorHiddenInGame(true);
		NewPin->SetActorTickEnabled(false);
		NewPin->setPinRotation();
	}
}

void AAirBaseManager::ToggleMarkers(bool isVisiblee) {
	if (!isVisiblee)
	{
		for (APinActor* NewPin : IndianCitiesList) {
			NewPin->SetActorHiddenInGame(true);
			NewPin->SetActorTickEnabled(false);
			NewPin->setPinRotation();
		}
		for (APinActor* NewPin : PakistanCitiesList) {
			NewPin->SetActorHiddenInGame(true);
			NewPin->SetActorTickEnabled(false);
			NewPin->setPinRotation();
		}
		for (APinActor* NewPin : PakistanAirbasesList) {
			NewPin->SetActorHiddenInGame(true);
			NewPin->SetActorTickEnabled(false);
			NewPin->setPinRotation();
		}
		for (APinActor* NewPin : IndianAirbasesList) {
			NewPin->SetActorHiddenInGame(true);
			NewPin->SetActorTickEnabled(false);
			NewPin->setPinRotation();
		}
	}

	this->isVisible = isVisiblee;
}


void AAirBaseManager::UpdateVisibilityBasedOnLayer(ELayer Mlayer) {
	layer = Mlayer;
	HideAllBases();
	HideAllCities();
	HideAllCapitals();

	switch (Mlayer)
	{
	case ELayer::TopMost:
		HideAllBases();
		HideAllCapitals();
		HideAllCities();
		break;
	case ELayer::Top:

	for (APinActor* NewPin : Layer0) {
		if (((NewPin->Category.Contains("Capital")) && (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakCities).FeatureActive)) || ((NewPin->Category.Contains("Base")) && (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakBases).FeatureActive)))
		{
			if (NewPin->GetHorizontolDistanceFromCamera() < (this->GetCircleRadius()))
			{
				NewPin->SetActorHiddenInGame(false);
				NewPin->SetActorTickEnabled(true);
				NewPin->setPinRotation();
			}
		}

	}
		break;
	case ELayer::TopMid:
		for (APinActor* NewPin : Layer1) {
			if (((NewPin->Category.Contains("Capital")) && (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakCities).FeatureActive)) || ((NewPin->Category.Contains("Base")) && (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakBases).FeatureActive)))
			{
				if (NewPin->GetHorizontolDistanceFromCamera() < (this->GetCircleRadius()))
				{
					NewPin->SetActorHiddenInGame(false);
					NewPin->SetActorTickEnabled(true);
					NewPin->setPinRotation();
				}

			}
		}
		break;
	case ELayer::Mid:
		for (APinActor* NewPin : Layer2) {
			if (((NewPin->Category.Contains("Major City")) && (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakCities).FeatureActive)) || ((NewPin->Category.Contains("Base")) && (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakBases).FeatureActive)))
			{
				if (NewPin->GetHorizontolDistanceFromCamera() < (this->GetCircleRadius()))
				{
					NewPin->SetActorHiddenInGame(false);
					NewPin->SetActorTickEnabled(true);
					NewPin->setPinRotation();
				}
			}
		}
		break;
	case ELayer::BottomMid:
		for (APinActor* NewPin : Layer3) {
			if (((NewPin->Category.Contains("Major City")) && (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakCities).FeatureActive)) || ((NewPin->Category.Contains("Base")) && (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakBases).FeatureActive)))
			{
				if (NewPin->GetHorizontolDistanceFromCamera() < (this->GetCircleRadius()))
				{
					NewPin->SetActorHiddenInGame(false);
					NewPin->SetActorTickEnabled(true);
					NewPin->setPinRotation();
				}
			}
		}

		break;
	case ELayer::Bottom:
		for (APinActor* NewPin : Layer4) {
			if (((NewPin->Category.Contains("Village")) && (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakCities).FeatureActive)) || ((NewPin->Category.Contains("Base")) && (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakBases).FeatureActive)))
			{
				if (NewPin->GetHorizontolDistanceFromCamera() < (this->GetCircleRadius()))
				{
					NewPin->SetActorHiddenInGame(false);
					NewPin->SetActorTickEnabled(true);
					NewPin->setPinRotation();
				}
			}
		}

		break;
	default:
		break;
	}
}

// Called when the game starts or when spawned
void AAirBaseManager::BeginPlay()
{
	Super::BeginPlay();

	instance = this;
	
	LoadData();
	//LoadCapitalsData();
	//LoadIndAirBaseData();
	//LoadCityLocationData();
	//LoadIndCityLocationData();
	UpdatePakistanBasePinVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakBases).FeatureActive);
	UpdateIndianAirbasePinVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::IndBases).FeatureActive);
	UpdatePakistanCitiesPinVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::PakCities).FeatureActive);
	UpdateIndianCitiesPinVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::IndCities).FeatureActive);

	UpdateVisibilityBasedOnLayer(layer);
}


void AAirBaseManager::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	FrameTime += DeltaTime;
	if (!CameraManager) {
		CameraManager = ADisplayManager::GetInstance()->PC->PlayerCameraManager;
	}
	FVector CameraLocation = CameraManager->GetCameraLocation();
	ELayer currentLayer = layer;
	cachedCameraLocation = CameraLocation;


	if ((ADisplayManager::GetInstance()->HeightOfCamera > MidLayerDistance) &&(ADisplayManager::GetInstance()->HeightOfCamera < TopMidLayerDistance)) {
	currentLayer = ELayer::BottomMid;
	}
	else if ((ADisplayManager::GetInstance()->HeightOfCamera > TopMidLayerDistance) && (ADisplayManager::GetInstance()->HeightOfCamera < TopLayerDistance)) {
		currentLayer = ELayer::Mid;
	}
	else if ((ADisplayManager::GetInstance()->HeightOfCamera > TopLayerDistance) && (ADisplayManager::GetInstance()->HeightOfCamera < TopMostLayerDistance)) {
		currentLayer = ELayer::TopMid;
	}
	else if ((ADisplayManager::GetInstance()->HeightOfCamera > TopMostLayerDistance) && (ADisplayManager::GetInstance()->HeightOfCamera < CullDistance)) {
		currentLayer = ELayer::Top;
	}
	else if((ADisplayManager::GetInstance()->HeightOfCamera > CullDistance)){
		currentLayer = ELayer::TopMost;

	}
	else if((ADisplayManager::GetInstance()->HeightOfCamera > 0) && (ADisplayManager::GetInstance()->HeightOfCamera < MidLayerDistance)){
		currentLayer = ELayer::Bottom;
	}


	//if ((currentLayer != layer) && (this->isVisible))
	//	{
	if (FrameTime > 1.f)
	{
		UpdateVisibilityBasedOnLayer(currentLayer);
			FrameTime = 0.f;
			cachedCameraLocation = CameraLocation;
	}

		//}
		
}

double AAirBaseManager::GetCircleRadius() {
	double heightOfCameraKM = ADisplayManager::GetInstance()->HeightOfCamera / 1000;

	double MinHeight = 10.0;
	double MaxHeight = 2000.0;
	double minRadius = 20.0;
	double maxRadius = 3000.0;

	if (heightOfCameraKM <= MinHeight)
	{
		return minRadius * 100000;
	}
	if (heightOfCameraKM >= MaxHeight)
	{
		return maxRadius * 100000;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf((TEXT("Height: %.3f")),heightOfCameraKM));
	double t = (heightOfCameraKM - MinHeight) / (MaxHeight - MinHeight);
	t = FMath::Clamp(t, 0.0, 1.0);

	double curvedT = FMath::Pow(t, 8);

	//double radius = minRadius * FMath::Pow((maxRadius / minRadius), curvedT);
	double radius = FMath::Lerp(minRadius, maxRadius, (heightOfCameraKM));

	radius = FMath::Clamp(heightOfCameraKM*1.5, minRadius, maxRadius);

	return radius * 100000;

}

