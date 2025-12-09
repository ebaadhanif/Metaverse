#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Team SimBridge/Model3DAssetManager.h"
#include "../Team SimBridge/NetworkManager.h"
#include "TimerManager.h"  
#include "Blueprint/UserWidget.h"
#include "../Team Visioneers/Menus/UIManager.h"
#include "../Team Visioneers/LoadingScreenWidget.h"
#include "LoadingManager.generated.h"

UCLASS()
class METAVERSE_API ALoadingManager : public AActor
{
	GENERATED_BODY()

public:
	ALoadingManager();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void AttachModelsToParent();
	FTimerHandle TimerHandle3DAssets;
	UPROPERTY() AActor* UltraDynamicSkyActor = nullptr;
	TArray<AActor*> VrOnlyObjects;
	ANetworkManager* NetworkManagerInstance;
	UMaterialParameterCollection* MPC = nullptr;
	UMaterialParameterCollectionInstance* MPC_Inst = nullptr;
	float NormalizedHeight;
	double multiplier;
	float TargetDiameter;
	float minDiameter = 1e6f;
	float maxMultiplied = 250.0f;
public:
	// Called every frame

	void SpawnAllActors();
	void SpawnNextActor();

	void InitializeModel3DAssetManager();
	FString Get3DModelsPath();
	void InitializeUIManager();
	UModel3DAssetManager* GetUModel3DAssetManager();
	void InitializeVRManager();
	void HideSplash();

	int32 CurrentActorIndex = 0;
	FTimerHandle TimerHandle;

	UPROPERTY()
	UModel3DAssetManager* obj;
	UPROPERTY()
	TMap<EMenus, TObjectPtr<UUserWidget>> MenuWidgetMap;
	UPROPERTY(Transient)
	TMap<EMenus, TSoftClassPtr<UUserWidget>> WidgetClassMap;
	UPROPERTY()
	TMap<EMenusVR, TWeakObjectPtr<AVRWidgetActor>> MenuWidgetMapVR;
	UPROPERTY()
	TMap<EMenusVR, TSubclassOf<UUserWidget>> WidgetClassMapVR;
	UPROPERTY()
	UWorld* world;


	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<class UUserWidget> LoadingScreenWidgetClass;

	UPROPERTY()
	ULoadingScreenWidget* LoadingScreenWidget;

private:
	TArray<TSubclassOf<AActor>> ActorClassesToSpawn;
};
