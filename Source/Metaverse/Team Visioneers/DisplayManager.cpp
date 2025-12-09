// Fill out your copyright notice in the Description page of Project Settings.


#include "DisplayManager.h"
#include <Kismet/GameplayStatics.h>
#include "GameFramework/GameModeBase.h"
#include "IHeadMountedDisplayModule.h"
#include "GameFramework/GameUserSettings.h"
#include "HanTracking.h"
#include "HeadMountedDisplayFunctionLibrary.h"

ADisplayManager* ADisplayManager::Instance = nullptr;
// Sets default values
ADisplayManager::ADisplayManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ADisplayManager::LoadDisplayConfigurations(const FString& ConfigFilePath)
{
    FXmlFile ConfigFile(ConfigFilePath);
    if (!ConfigFile.IsValid()) {
        UE_LOG(LogTemp, Error, TEXT("Failed to load configuration file: %s"), *ConfigFilePath);
        return;
    }

    const FXmlNode* RootNode = ConfigFile.GetRootNode();
    if (!RootNode) {
        UE_LOG(LogTemp, Error, TEXT("Invalid XML structure: Root node missing."));
        return;
    }

    for (const FXmlNode* Node : RootNode->GetChildrenNodes()) {

        if (Node->GetTag() == "Displays") {
            for (const FXmlNode* child : Node->GetChildrenNodes()) {
                DisplayStruct display;
                display.fov = FCString::Atoi(*child->GetAttribute("fov"));
                display.camAngle = FCString::Atoi(*child->GetAttribute("camAngle"));
                display.height = FCString::Atoi(*child->GetAttribute("height"));
                display.width = FCString::Atoi(*child->GetAttribute("width"));
                display.targetDisplay = FCString::Atoi(*child->GetAttribute("targetDisplay"));
                display.fullScreenType = FCString::Atoi(*child->GetAttribute("fullScreenType"));
                display.active = child->GetAttribute("active").ToBool();
                Displays.Add(display);
            }
        }

        

        if (Node->GetTag() == "DisplayMode") {
            DisplayMode = Node->GetContent();

            isVRMode = false;
            if (DisplayMode == "VR")
                isVRMode = true;

            APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
           /*
            MetaverseXRInputManager = GetWorld()->SpawnActor<AMetaverseXRInputManager>(
                AMetaverseXRInputManager::StaticClass(),
                FVector(0, 0, 0),
                FRotator(0, 0, 0));*/

            HandTrackingActor = GetWorld()->SpawnActor<AHanTracking>(
                AHanTracking::StaticClass(),
                FVector(0, 0, 0),
                FRotator::ZeroRotator);

          //  HandTrackingActor = MetaverseXRInputManager->GetHandTrackingActor();
            
            if (PlayerPawn)
            {

                FreeCamPawn = Cast<AFreeCameraPawn>(PlayerPawn);
                if (FreeCamPawn && FreeCamPawn->Camera)
                {
                    UHeadMountedDisplayFunctionLibrary::EnableHMD(isVRMode);
                    FreeCamPawn->Camera->bLockToHmd = isVRMode;
                    FreeCamPawn->Camera->FieldOfView = Displays[0].fov;
                    UE_LOG(LogTemp, Warning, TEXT("bLockToHmd has been updated."));
                }
            }
        }

        if (Node->GetTag() == "AllowDisplayModeChange") {
            AllowDisplayModeChange = Node->GetContent();
        }
        
    }

    
    FString StringwinType;
    EWindowMode::Type winType;
    if (Displays[0].fullScreenType == 1) {
        winType = EWindowMode::Fullscreen;
        StringwinType = "EWindowMode::Fullscreen";
    }
    else if (Displays[0].fullScreenType == 2) {
        winType = EWindowMode::Windowed;
        StringwinType = "EWindowMode::Windowed";
    } 
    else if (Displays[0].fullScreenType == 3) {
        winType = EWindowMode::WindowedFullscreen;
        StringwinType = "EWindowMode::WindowedFullscreen";
    }
    else{
        winType = EWindowMode::Fullscreen;
        StringwinType = "EWindowMode::Fullscreen";
    }

    UGameUserSettings* Settings = GEngine->GetGameUserSettings();
    if (Settings)
    {
        Settings->SetOverallScalabilityLevel(0);
        Settings->SetScreenResolution(FIntPoint(Displays[0].width, Displays[0].height));
        Settings->SetFullscreenMode(winType);
        Settings->ApplySettings(false); // false disables command line overrides
    }

    GEngine->AddOnScreenDebugMessage(-1, 10.0, FColor::Green, DisplayMode + " | " + StringwinType);
}

// Called when the game starts or when spawned
void ADisplayManager::BeginPlay()
{
	Super::BeginPlay();
    if (Instance == nullptr)
    {
        Instance = this;
    }
	LoadDisplayConfigurations(XmlFilePath);

    PC = GetWorld()->GetFirstPlayerController();

}

// Called every frame
void ADisplayManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
    if(FreeCamPawn)
    HeightOfCamera = FreeCamPawn->heightFromGround;

}

void ADisplayManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (Instance == this) {
        Instance = nullptr;
    }
    Super::EndPlay(EndPlayReason);
}

ADisplayManager* ADisplayManager::GetInstance()
{
    return Instance;
}


