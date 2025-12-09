#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Blueprint.h"
#include "Cesium3DTileset.h"
#include "CesiumGeoreference.h"
#include "CesiumGlobeAnchorComponent.h"
#include "FShapeFileReader.h"
#include "PinActor.h"
#include "Components/TextRenderComponent.h"
#include <Components/HierarchicalInstancedStaticMeshComponent.h>
#include "../Public/AppConstEnumStruct.h"
#include <mutex>
#include "AirBaseManager.generated.h"



USTRUCT(BlueprintType)
struct FLandMarkPointData {
	 GENERATED_BODY();

	 UPROPERTY(BlueprintReadWrite) FString Name;
	 UPROPERTY(BlueprintReadWrite) FString Abbreviation;

	 UPROPERTY(BlueprintReadWrite) FString LayerOrder;
	 UPROPERTY(BlueprintReadWrite) double Lat;
	 UPROPERTY(BlueprintReadWrite) double Long;
	 UPROPERTY(BlueprintReadWrite) double Elev = 0;

	 UPROPERTY(BlueprintReadWrite) int32 CountryId = 0;
	 UPROPERTY(BlueprintReadWrite) FString Category;
	 UPROPERTY(BlueprintReadWrite) FString Colour;
	 UPROPERTY(BlueprintReadWrite) FString TextColour;
};

UCLASS()
class METAVERSE_API AAirBaseManager : public AActor
{
	 GENERATED_BODY()

public:
	static AAirBaseManager* instance;
	static AAirBaseManager* getInstance();
	AAirBaseManager();
	 void LoadAirBaseData();
	 void LoadData();
	 void LoadCapitalsData();
	 void LoadCityLocationData();

	 FLandMarkPointData temp;
	 ACesiumGeoreference* CesiumGeoreference;
	 ACesium3DTileset* Tileset;
	 bool bIsVisible = true;
	 APlayerController* PC;
	 UCesiumGlobeAnchorComponent* GlobeAnchor;


	 //Pakistan Bases Data Structure
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> PakistanAirbasesList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> CapitalsList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> PakistanAirbasesListLayer1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> PakistanAirbasesListLayer2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> PakistanAirbasesListLayer3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> PakistanAirbasesListLayer4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> Layer0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> Layer1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> Layer2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> Layer3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> Layer4;

	//Indian Bases Data Structure
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> IndianAirbasesListLayer1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> IndianAirbasesListLayer2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> IndianAirbasesListLayer3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> IndianAirbasesListLayer4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> IndianAirbasesList;


	//Pakistan Cities Data Structure
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> PakistanCitiesList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> PakistanCitiesListLayer1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> PakistanCitiesListLayer2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> PakistanCitiesListLayer3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> PakistanCitiesListLayer4;

	//Indian Cities Data Structure
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> IndianCitiesList;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> IndianCitiesListLayer1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> IndianCitiesListLayer2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> IndianCitiesListLayer3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<APinActor*> IndianCitiesListLayer4;

	UPROPERTY()
	UClass* PakLabelWidgetClass = nullptr;

	UPROPERTY()
	UClass* IndLabelWidgetClass = nullptr;

	 void InitializeData(const FShapeRawData& Raw);
	void UpdatePakistanCitiesPinVisibility(bool bShowPins);
	void UpdatePakistanBasePinVisibility(bool bShowPins);
	void UpdateIndianAirbasePinVisibility(bool bShowPins);
	void UpdateIndianCitiesPinVisibility(bool bShowPins);
	void HideAllBases();
	void HideAllCities();
	void HideAllCapitals();
	void ToggleMarkers(bool isVisible);
	void UpdateVisibilityBasedOnLayer(ELayer layer);
	double GetCircleRadius();
	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* LabelWidget;
	UClass* labelWidgetClass = nullptr;
	UClass* labelWidgetIndiaClass = nullptr;
	UClass* labelWidgetClassWithoutBG = nullptr;
	UPROPERTY()
	AActor* PinParentActor;

	UPROPERTY()
	APlayerCameraManager* CameraManager;
	FVector cachedCameraLocation;
	ELayer layer = ELayer::Bottom;

	double TopMostLayerDistance = 2600000;
	double TopLayerDistance = 1600000;
	double TopMidLayerDistance = 600000;
	double MidLayerDistance = 25000;
	double CullDistance = 8000000;


	float FrameTime = 0.f;
	bool isVisible = true;

protected:
	 virtual void BeginPlay() override;
	 virtual void Tick(float DeltaTime) override;
};