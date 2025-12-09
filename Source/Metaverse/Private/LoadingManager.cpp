#include "LoadingManager.h"
#include "AKeyboardInputHandler.h"
#include "AVajroInputHandler.h"
#include "HtcVIVEInputHandler.h"
#include "../Team Visioneers/FPSDisplay.h"
#include "TerrainManager.h"
#include "../Team RenderStorm/WeatherController.h"
//#include "PCGManager.h"
#include "Engine/World.h"
#include "../Team RenderStorm/SplatMapping.h"
#include "../Team RenderStorm/DetonationController.h"
#include "../Team RenderStorm/ModeManager.h"
#include "../Team SimBridge/NetworkManager.h"
#include "../Team Visioneers/ScalingManager.h"
#include "../Team SimBridge/RemoteEntityFactory.h"
#include "../Team Visioneers/AirBaseManager.h"
#include "../Team Visioneers/VR_Menus/UIManagerVR.h"
#include "../Team Visioneers/ExerciseStatsManager.h"

#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "GameFramework/Actor.h"
#include "IShape.h"
#include "HanTracking.h"
#include "DWGXDrawingManager.h"
#include "../Team Visioneers/DisplayManager.h"
#define NOMINMAX
#include "CesiumGeoreference.h"
#undef OPAQUE
#include "Cesium3DTileset.h"
#include "MetaverseLogger.h"
#include "VRMenuInteraction.h"
#include "CesiumGlobeMovementHandler.h"
#include <HeadMountedDisplayFunctionLibrary.h>
#include "../Team RenderStorm/VisualEffectsController.h"
ALoadingManager::ALoadingManager()
{
    PrimaryActorTick.bCanEverTick = true;
    ActorClassesToSpawn.Add(AModeManager::StaticClass());
    ActorClassesToSpawn.Add(ADisplayManager::StaticClass());
    //ActorClassesToSpawn.Add(AScalingManager::StaticClass());
    ActorClassesToSpawn.Add(AVRMenuInteraction::StaticClass());    
    ActorClassesToSpawn.Add(ASplatMapping::StaticClass());
    ActorClassesToSpawn.Add(AFPSDisplay::StaticClass());
    ActorClassesToSpawn.Add(AWeatherController::StaticClass());
   // ActorClassesToSpawn.Add(APCGManager::StaticClass());
    ActorClassesToSpawn.Add(AAirBaseManager::StaticClass());
    ActorClassesToSpawn.Add(AExerciseStatsManager::StaticClass());
    ActorClassesToSpawn.Add(AVisualEffectsController::StaticClass());
   // ActorClassesToSpawn.Add(ANetworkManager::StaticClass());  
}

void ALoadingManager::BeginPlay()
{
    Super::BeginPlay();




    if (LoadingScreenWidgetClass && !UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
    {
        LoadingScreenWidget = CreateWidget<ULoadingScreenWidget>(GetWorld(), LoadingScreenWidgetClass);
        if (LoadingScreenWidget)
        {
            LoadingScreenWidget->AddToViewport();
        }
    }
    
    GEngine->Exec(GetWorld(), TEXT("r.Streaming.PoolSize 8000"));
    GEngine->Exec(GetWorld(), TEXT("r.TextureStreaming 1"));
    GEngine->Exec(GetWorld(), TEXT("r.Shadow.Virtual.SMRT.RayCountLocal 8"));
    GEngine->Exec(GetWorld(), TEXT("t.MaxFPS 1000"));

    SpawnAllActors();
    ACesiumGeoreference* Goereference = ACesiumGeoreference::GetDefaultGeoreference(GetWorld());
    ACesium3DTileset* Tileset = Cast< ACesium3DTileset>(UGameplayStatics::GetActorOfClass(GetWorld(), ACesium3DTileset::StaticClass()));
    CesiumGlobeMovementHandler::GetInstance()->CustomGlobeMovementBeginPlay(GetWorld());

    //Coverages Setup
    UCoveragesManager::GetInstance()->SetWorld(GetWorld());
    MPC = LoadObject<UMaterialParameterCollection>(nullptr, TEXT("/Game/Materials/MPC_CesiumMask.MPC_CesiumMask"));
    if (MPC)
    {
        MPC_Inst = GetWorld()->GetParameterCollectionInstance(MPC);

    }
    //Detonation Setup
    UDetonationController::Get()->SetWorldVariable(GetWorld());
    UDetonationController::Get()->SetTileset(Tileset);
    UDetonationController::Get()->SetGeoreference(Goereference);


    UCoveragesManager::GetInstance()->SetWorld(GetWorld());
    InitializeModel3DAssetManager();
    InitializeUIManager();
    GetWorld()->GetTimerManager().SetTimer(TimerHandle3DAssets, this, &ALoadingManager::AttachModelsToParent, 1.0f, false);
    RemoteEntityFactory::GetRemoteEntityFactoryInstance(); //call to load objectTypeEnum file
    for (TActorIterator<AActor> It(GetWorld()); It; ++It)
    {
        if (It->ActorHasTag("Ultra_Dynamic_Sky"))
        {
            UltraDynamicSkyActor = *It;
            VrOnlyObjects.Add(UltraDynamicSkyActor);
            UE_LOG(LogTemp, Warning, TEXT("Found Ultra Dynamic Sky Actor: %s"), *UltraDynamicSkyActor->GetName());
            break;
        }
    }
    if (AHanTracking::GetInstance())
    {
        
        AHanTracking::GetInstance()->SetUpMRControl(VrOnlyObjects);

    }



}


void ALoadingManager::SpawnAllActors()
{
    for (int i = 0; i < ActorClassesToSpawn.Num(); i++)
    {
       //if (ActorClassesToSpawn[i] == APCGManager::StaticClass())
       // {
       //     if ((!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::Vegetation).FeatureActive) && (!AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::Vegetation).buttonVisibility))
       //     {
       //         continue;
       //     }

       // }
        if (i < ActorClassesToSpawn.Num())
        {

            AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
                ActorClassesToSpawn[i],
                FVector(0, 0, 0),
                FRotator(0, 0, 0)
            );

            if (SpawnedActor)
            {
                UE_LOG(LogTemp, Log, TEXT("Spawned Actor: %s"), *SpawnedActor->GetName());

                if (LoadingScreenWidget)
                {
                    if (SpawnedActor->GetName().Contains(TEXT("NetworkManager")))
                    {
                        NetworkManagerInstance = Cast<ANetworkManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ANetworkManager::StaticClass()));
                    }
                    LoadingScreenWidget->SetLoadingMessage(FText::FromString(SpawnedActor->GetName()));
                    LoadingScreenWidget->SetProgressBar((i + 1) / static_cast<float>(ActorClassesToSpawn.Num()));
                }
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to spawn actor of class %s"), *ActorClassesToSpawn[CurrentActorIndex]->GetName());
            }
            //CurrentActorIndex++;
            //SpawnNextActor();
            //GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALoadingManager::SpawnNextActor, 5.0f, false);

            if (CurrentActorIndex == ActorClassesToSpawn.Num() && !NetworkManagerInstance)
            {
                HideSplash();
            }
        }
    }
    //SpawnNextActor();
}

void ALoadingManager::SpawnNextActor() {





    if (CurrentActorIndex < ActorClassesToSpawn.Num())
    {

        AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
            ActorClassesToSpawn[CurrentActorIndex],
            FVector(0, 0, 0),                     
            FRotator(0, 0, 0)                    
        );
        
        if (SpawnedActor)
        {
            UE_LOG(LogTemp, Log, TEXT("Spawned Actor: %s"), *SpawnedActor->GetName());

   	if (LoadingScreenWidget)
      	{
          if (SpawnedActor->GetName().Contains(TEXT("NetworkManager")))
          {
              NetworkManagerInstance = Cast<ANetworkManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ANetworkManager::StaticClass()));
          }
          LoadingScreenWidget->SetLoadingMessage(FText::FromString(SpawnedActor->GetName()));
          LoadingScreenWidget->SetProgressBar((CurrentActorIndex + 1) / static_cast<float>(ActorClassesToSpawn.Num()));
     	}
        }
        else
        {
           UE_LOG(LogTemp, Warning, TEXT("Failed to spawn actor of class %s"), *ActorClassesToSpawn[CurrentActorIndex]->GetName());
        }
        CurrentActorIndex++;
        SpawnNextActor();
        //GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ALoadingManager::SpawnNextActor, 5.0f, false);

        if (CurrentActorIndex == ActorClassesToSpawn.Num()  && !NetworkManagerInstance)
        {
            HideSplash();
        }
    }
}


void ALoadingManager::InitializeModel3DAssetManager()
{
    obj = NewObject<UModel3DAssetManager>();
    obj->ModelsFolderpath = Get3DModelsPath();
    obj->Import3DAsset();
}

FString ALoadingManager::Get3DModelsPath()
{
    FString XmlContent;
    FString Path = FPaths::ProjectContentDir() / TEXT("Archive/AppConfig.xml");
    if (FFileHelper::LoadFileToString(XmlContent, *Path))
    {
        XmlContent.TrimStartAndEndInline(); // Remove BOM or stray spaces
        FXmlFile XmlFile(XmlContent, EConstructMethod::ConstructFromBuffer);

        if (XmlFile.IsValid())
        {
            FXmlNode* RootNode = XmlFile.GetRootNode();
            if (RootNode && RootNode->GetTag() == TEXT("AppConfig")) // Case-sensitive!
            {
                FXmlNode* ModelsPathNode = RootNode->FindChildNode(TEXT("3DModelsPath"));
                if (ModelsPathNode)
                {
                    FString ModelsPathValueStr = ModelsPathNode->GetContent().TrimStartAndEnd();
                    return ModelsPathValueStr;
                }
            }
        }
    }

    return FString("Invalid");
}

void ALoadingManager::InitializeUIManager()
{
    if (UIManager::GetInstance()) {
        UIManager::GetInstance()->SetWorld(GetWorld());
        UIManager::GetInstance()->loadingManager = this;
        MenuWidgetMap = UIManager::GetInstance()->InitializeScreenMenu();
        if (!ADisplayManager::GetInstance()->isVRMode)
            return;
        MenuWidgetMapVR = UIManager::GetInstance()->InitializeVRMenu();

    }
}

UModel3DAssetManager* ALoadingManager::GetUModel3DAssetManager()
{
    return obj;
}

void ALoadingManager::InitializeVRManager()
{
    /* if (!ADisplayManager::GetInstance()->vr)
         return;
     if (UUIManagerVR::GetInstance()) {
         UUIManagerVR::GetInstance()->SetWorld(GetWorld());
         UUIManagerVR::GetInstance()->Initialize();
         UUIManagerVR::GetInstance()->CreateMenu(EMenusVR::MainMenu);
     }*/
}

void ALoadingManager::HideSplash()
{
    if (LoadingScreenWidget)
    {
        LoadingScreenWidget->RemoveFromParent();
      //  UIManager::GetInstance()->ShowMenu(EMenus::MainMenu);
        LoadingScreenWidget = nullptr;
    }
}


void ALoadingManager::AttachModelsToParent()
{
    obj->AttachSpawnedActorsToParent();
}

void ALoadingManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    UIManager::GetInstance()->ShutDown();
    UDetonationController::Get()->Shutdown();
    UCoveragesManager::GetInstance()->Shutdown();
    UDWGXDrawingManager::Get(this)->Shutdown();

}

void ALoadingManager::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    CesiumGlobeMovementHandler::GetInstance()->CesiumGlobeMovementHandlerCustomTick(DeltaSeconds);

   if (NetworkManagerInstance && NetworkManagerInstance->GetProtocolAdapterPtr()->bIsJoined)
    {
        HideSplash();
    }

    if (ADisplayManager::GetInstance()->FreeCamPawn) {
   TargetDiameter = minDiameter + ADisplayManager::GetInstance()->FreeCamPawn->heightFromGround * maxMultiplied;
    NormalizedHeight = FMath::Clamp(TargetDiameter, minDiameter, 8e10f);
    multiplier = FMath::Clamp(ADisplayManager::GetInstance()->FreeCamPawn->heightFromGround * 180, 0.0f, 500000000);


    //if (MPC_Inst)
    //{
    //    //FVector PawnLLH = CesiumGlobeMovementHandler::GetInstance()->m_DefaultGeoreferenceActor->TransformUnrealPositionToEarthCenteredEarthFixed(ADisplayManager::GetInstance()->FreeCamPawn->GetActorLocation());
    //    //FVector UnrealPivot = CesiumGlobeMovementHandler::GetInstance()->m_DefaultGeoreferenceActor->TransformLongitudeLatitudeHeightPositionToUnreal(PawnLLH);
    //    MPC_Inst->SetScalarParameterValue(FName("Diameter"), NormalizedHeight);
    //    // CesiumMaterialBaseDynamicInstanceMaterial->SetScalarParameterValue(FName("Diameter"), NormalizedHeight);
    //}

    //if (ADisplayManager::GetInstance()->FreeCamPawn->heightFromGround > CesiumGlobeMovementHandler::GetInstance()->OriginHeightM + 100000)
    //{
    //    MPC_Inst->SetVectorParameterValue(FName("Pivot"), FVector(0.0f, 0.325f, 34020.0f));

    //}
    //else
    //{
    //    MPC_Inst->SetVectorParameterValue(FName("Pivot"), FVector(ADisplayManager::GetInstance()->FreeCamPawn->GetActorLocation().X + multiplier, ADisplayManager::GetInstance()->FreeCamPawn->GetActorLocation().Y, 34020.0));
    //}

    }
}




