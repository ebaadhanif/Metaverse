#include "FreeCameraPawn.h"
#include "HtcVIVEInputHandler.h"
#include "AVajroInputHandler.h"
#include "AKeyboardInputHandler.h"
#include "MouseInputHandler.h"
#include "IXRTrackingSystem.h"
#include "../Team Visioneers/CmpassWidget.h"
#include "../Team Visioneers/ContextMenuWidget.h"
#include "../Team Visioneers/DisplayManager.h"
#include "../Team Visioneers/VR_Menus/VRWidgetActor.h"
#include "../Team RenderStorm/ModeManager.h"
#include "Engine/Engine.h"
#include "CesiumGeoreference.h"
#include <CesiumGeospatial/Ellipsoid.h>
#include <glm/vec3.hpp>
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"
#include "DWGXDrawingManager.h"
#include <Metaverse/Team Visioneers/VR_Menus/UIManagerVR.h>
#include <Metaverse/Team Visioneers/Menus/GraphicsDropDown.h>


AFreeCameraPawn::AFreeCameraPawn()
{
    // setting PCG Generation Source:
    PCGGenSource = CreateDefaultSubobject<UPCGGenSourceComponent>(TEXT("PCGGenSource"));
    PCGGenSource->SetAutoActivate(true);


    GlobeAnchor = CreateDefaultSubobject<UCesiumGlobeAnchorComponent>(TEXT("GlobeAnchor"));
    CapsuleBody = CreateDefaultSubobject<UCapsuleComponent>(TEXT("RootCapsule")); // capsule has built in collider so we dont need to attach a collider to camera
    CapsuleBody->SetupAttachment(RootComponent);
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    Camera->SetupAttachment(CapsuleBody);
    Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    CapsuleBody->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    CapsuleBody->SetCollisionResponseToAllChannels(ECR_Block);
    CapsuleBody->SetCollisionObjectType(ECC_Pawn);
    //  Ignoring RayTracing collision for mouseclickevent to CapsuleBody ...
    CapsuleBody->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
    // Left and Right Motion Controllers
    LeftController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftController"));
    LeftController->SetupAttachment(CapsuleBody);
    LeftController->SetTrackingSource(EControllerHand::Left);
    LeftController->bDisableLowLatencyUpdate = false;
    //globeAnchor = CreateDefaultSubobject<UCesiumGlobeAnchorComponent>(TEXT("globeAnchor"));
    RightController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightController"));
    RightController->SetupAttachment(CapsuleBody);
    RightController->SetTrackingSource(EControllerHand::Right);

    CompassWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("CompassWidgetComponent"));
    //CompassWidgetComponent->SetupAttachment(Camera);
    CompassWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    CompassWidgetComponent->SetWorldScale3D(FVector(0.1f));
    CompassWidgetComponent->SetHiddenInGame(false);
    //CompassWidgetComponent->SetDrawSize(FVector2D(500.0f, 500.0f));
    CompassWidgetComponent->SetDrawSize(FIntPoint(1024, 1024));
    CompassWidgetComponent->SetVisibility(false);
    CompassWidgetComponent->SetTwoSided(true);

    // Hand Meshes for visual feedback
    LeftHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftHandMesh"));
    //  LeftHandMesh->SetupAttachment(LeftController);
    LeftHandMesh->SetRelativeLocation(FVector::ZeroVector);
    LeftHandMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));  // Rotate to face the correct direction
    LeftHandMesh->SetRelativeScale3D(FVector(0.5f));

    RightHandMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightHandMesh"));
    // RightHandMesh->SetupAttachment(RightController);
    RightHandMesh->SetRelativeLocation(FVector::ZeroVector);
    RightHandMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f)); // Mirror the left hand
    RightHandMesh->SetRelativeScale3D(FVector(0.5f));

    ExerciseStatsWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("ExerciseStatsWidgetComponent"));
    ExerciseStatsWidgetComponent->SetWidgetSpace(EWidgetSpace::World);
    ExerciseStatsWidgetComponent->SetWorldScale3D(FVector(0.1f));
    ExerciseStatsWidgetComponent->SetHiddenInGame(false);
    ExerciseStatsWidgetComponent->SetDrawSize(FIntPoint(1800, 1024));
    ExerciseStatsWidgetComponent->SetVisibility(false);
    ExerciseStatsWidgetComponent->SetTwoSided(true);

    StatsTableComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatsTableComponent"));
    StatsTableComponent->SetWidgetSpace(EWidgetSpace::World);
    StatsTableComponent->SetWorldScale3D(FVector(0.03f));
    StatsTableComponent->SetHiddenInGame(false);
    StatsTableComponent->SetDrawSize(FIntPoint(1800, 1024));
    StatsTableComponent->SetTwoSided(true);
    StatsTableComponent->SetVisibility(false);

    TipSpheresL = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TipSpheres_Left"));
    TipSpheresR = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TipSpheres_Right"));
    static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
    if (SphereMesh.Succeeded())
    {
        TipSpheresL->SetStaticMesh(SphereMesh.Object);
        TipSpheresR->SetStaticMesh(SphereMesh.Object);
    }
    TipSpheresL->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    TipSpheresR->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    TipSpheresL->SetupAttachment(CapsuleBody);
    TipSpheresR->SetupAttachment(CapsuleBody);

    static ConstructorHelpers::FClassFinder<UUserWidget> CompassWidgetBP(TEXT("/Game/Blueprints/WBP_Compass"));
    if (CompassWidgetBP.Succeeded())
    {
        CompassWidgetClass = CompassWidgetBP.Class;
        CompassWidgetComponent->SetWidgetClass(CompassWidgetClass);
    }

    static ConstructorHelpers::FClassFinder<AActor> CaptureBPClass(TEXT("/Game/Blueprints/BP_RemoteEntityPreview"));
    if (CaptureBPClass.Succeeded())
    {
        CaptureClass = CaptureBPClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> ExerciseStatsWidgetBP(TEXT("/Game/Blueprints/WBP_Exercise_Stats"));
    if (ExerciseStatsWidgetBP.Succeeded())
    {
        ExerciseStatsWidgetClass = ExerciseStatsWidgetBP.Class;
        ExerciseStatsWidgetComponent->SetWidgetClass(ExerciseStatsWidgetClass);
    }


    static ConstructorHelpers::FClassFinder<UUserWidget> StatsTabletBP(TEXT("/Game/Blueprints/WBP_Stats_Table"));
    if (StatsTabletBP.Succeeded())
    {
        StatsTableClass = StatsTabletBP.Class;
        StatsTableComponent->SetWidgetClass(StatsTableClass);
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> ContextWidgetBP(TEXT("/Game/Blueprints/WBP_ContextMenu"));
    if (ContextWidgetBP.Succeeded())
    {
        ContextMenuClass = ContextWidgetBP.Class;
    }

    HandOffset = FVector(1, -3, -8);


    // Camera ->SetupAttachment(CapsuleBody);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    OrbitPivot = CreateDefaultSubobject<UCapsuleComponent>(TEXT("OrbitPivot"));

}


void AFreeCameraPawn::BeginPlay()
{
    Super::BeginPlay();
    PlayerControllerRef = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    //Setting PCG:
    PCGGenSource = NewObject<UPCGGenSourceComponent>(this, TEXT("PCGGenSourceDyn"));
    AddInstanceComponent(PCGGenSource);
    PCGGenSource->RegisterComponent();
    PCGGenSource->SetAutoActivate(true);
    PCGGenSource->Activate(true);

   SetActorLocationAndRotation(FVector(-104710.000000, 691270.000000, -12899.000000), FRotator(0.0f, 0.0f, 0.0f));
    //SetActorRotation(FRotator(0.0f,0.0f,0.0f));

    GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AFreeCameraPawn::BindSpecificDeviceInputActionsToFunctions);
    params.AddIgnoredActor(this);
    params.AddIgnoredComponent(RightController);

    params.AddIgnoredComponent(LeftController);
    UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
    UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();

    if (CompassWidgetClass)
    {
        CompassWidgetInstance = Cast<UCmpassWidget>(CompassWidgetComponent->GetUserWidgetObject());
    }

    if (CaptureClass)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        FVector SpawnLocation(0.f, 0.f, 200.f);
        FRotator SpawnRotation = FRotator::ZeroRotator;
        SpawnedActor = GetWorld()->SpawnActor<AActor>(CaptureClass, SpawnLocation + FVector(0.f, 200.f, 0.f), SpawnRotation, SpawnParams);

    }

    if (ExerciseStatsWidgetClass)
    {
        ExerciseStatsWidgetInstance = Cast<UExerciseStatsWidget>(ExerciseStatsWidgetComponent->GetUserWidgetObject());
    }

    if (StatsTableClass)
    {
        StatsTableInstance = Cast<UStatsTable>(StatsTableComponent->GetUserWidgetObject());
    }

    if (ContextMenuClass)
    {
        ContextMenuInstance = CreateWidget<UContextMenuWidget>(GetWorld(), ContextMenuClass);
        if (ContextMenuInstance)
        {
            ContextMenuInstance->AddToViewport();
            ContextMenuInstance->SetVisibility(ESlateVisibility::Hidden);
        }

    }

    SetActorRotation(FRotator::ZeroRotator);
    FVector SpawnLocation(0, 0, 0);
    FRotator SpawnRotatiaon(0, 0, 0);
    FActorSpawnParameters Fparams;

    FreeCameraTransform = GetTransform();

}

void AFreeCameraPawn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UDWGXDrawingManager::Get(GetWorld())->CustomTick(DeltaTime);


    MovementSpeed = FMath::Clamp((GlobeAnchor->GetHeight() * 10), 1000, 99999999);
    if (bIsShiftHeld) {
        MovementSpeed = MovementSpeed * 5;
    }
    FString height = FString::Printf(TEXT("MovementSpeed : %.0f"), MovementSpeed);

    if (CompassWidgetInstance)
    {
        CompassWidgetInstance->UpdateCompassNeedle(Camera->GetComponentRotation().Yaw);
        SetCompassPosition();

    }

    if (ExerciseStatsWidgetInstance)
    {
        SetStatsPosition();
    }

    if (StatsTableInstance)
    {
        SetStatsTablePosition();
    }

    if (AExerciseStatsManager::GetInstance())
    {
        StatsTableInstance->UpdateStatsTableData(StatsTableImageIndex, AExerciseStatsManager::GetInstance()->GetEntityStats());
    }


    if (GlobeAnchor->GetHeight() > 200000) {
        ExerciseStatsWidgetComponent->SetVisibility(false);
        StatsTableComponent->SetVisibility(false);
    }
    else {
        ExerciseStatsWidgetComponent->SetVisibility(!bIsStatsVisible);
        StatsTableComponent->SetVisibility(false);
    }

    if (!bIsStatsVisible && AExerciseStatsManager::GetInstance())
    {
        ExerciseStatsWidgetInstance->UpdateStatsData(AExerciseStatsManager::GetInstance()->GetEntityStats());

    }

    if (GlobeAnchor->GetHeight() > 200000) {
        ExerciseStatsWidgetComponent->SetVisibility(false);
    }
    else {
        ExerciseStatsWidgetComponent->SetVisibility(!bIsStatsVisible);
    }

    if (RightController)
    {
        LeftControllerStart = RightController->GetComponentLocation();
        FVector ForwardVector = RightController->GetForwardVector();
        LeftControllerEnd = LeftControllerStart + (ForwardVector * 100000);
    }

    heightFromGround = GlobeAnchor->GetHeight();


}

void AFreeCameraPawn::BindSpecificDeviceInputActionsToFunctions()
{

    AHtcVIVEInputHandler* CurrentHtcViveDeviceHandlerObject = NULL;
    CurrentHtcViveDeviceHandlerObject = Cast<AHtcVIVEInputHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AHtcVIVEInputHandler::StaticClass()));

    AAVajroInputHandler* CurrentVajroDeviceHandlerObject = NULL;
    CurrentVajroDeviceHandlerObject = Cast<AAVajroInputHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAVajroInputHandler::StaticClass()));

    AAKeyboardInputHandler* CurrentKeyboardDeviceHandlerObject = NULL;
    CurrentKeyboardDeviceHandlerObject = Cast<AAKeyboardInputHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAKeyboardInputHandler::StaticClass()));

    AMouseInputHandler* MouseHandler = Cast<AMouseInputHandler>(
        UGameplayStatics::GetActorOfClass(GetWorld(), AMouseInputHandler::StaticClass()));

    if (CurrentVajroDeviceHandlerObject)
    {
        CurrentVajroDeviceHandlerObject->BindActions(CurrentVajroDeviceHandlerObject->IA_VarjoController_Right_Thumbstick_Y, ETriggerEvent::Triggered, this, &AFreeCameraPawn::MoveFreeCamPawnForward);
        CurrentVajroDeviceHandlerObject->BindActions(CurrentVajroDeviceHandlerObject->IA_VarjoController_Right_Thumbstick_X, ETriggerEvent::Triggered, this, &AFreeCameraPawn::MoveFreeCamPawnLeft);

        CurrentVajroDeviceHandlerObject->BindActions(CurrentVajroDeviceHandlerObject->IA_VarjoController_Right_Trigger_Axis, ETriggerEvent::Started, this, &AFreeCameraPawn::OnLeftGripPressed);
        CurrentVajroDeviceHandlerObject->BindActions(CurrentVajroDeviceHandlerObject->IA_VarjoController_Right_Trigger_Axis, ETriggerEvent::Completed, this, &AFreeCameraPawn::OnLeftGripReleased);
    }

    if (CurrentHtcViveDeviceHandlerObject)
    {
        CurrentHtcViveDeviceHandlerObject->BindActions(CurrentHtcViveDeviceHandlerObject->IA_Vive_Right_Trackpad_Y, ETriggerEvent::Triggered, this, &AFreeCameraPawn::MoveFreeCamPawnForward);
        CurrentHtcViveDeviceHandlerObject->BindActions(CurrentHtcViveDeviceHandlerObject->IA_Vive_Right_Trackpad_X, ETriggerEvent::Triggered, this, &AFreeCameraPawn::MoveFreeCamPawnLeft);

        CurrentHtcViveDeviceHandlerObject->BindActions(CurrentHtcViveDeviceHandlerObject->IA_Vive_Right_Grip_Click, ETriggerEvent::Started, this, &AFreeCameraPawn::OnLeftGripPressed);
        CurrentHtcViveDeviceHandlerObject->BindActions(CurrentHtcViveDeviceHandlerObject->IA_Vive_Right_Grip_Click, ETriggerEvent::Completed, this, &AFreeCameraPawn::OnLeftGripReleased);
        CurrentHtcViveDeviceHandlerObject->BindActions(CurrentHtcViveDeviceHandlerObject->IA_Vive_Right_Trigger_Axis, ETriggerEvent::Started, this, &AFreeCameraPawn::OnTriggerClick);
    }

    if (CurrentKeyboardDeviceHandlerObject)
    {
        // Pawn Movement Mapping 
        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_W_Press,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::MoveFreeCamPawnForward);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_S_Press,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::MoveFreeCamPawnBackward);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_A_Press,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::MoveFreeCamPawnLeft);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_D_Press,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::MoveFreeCamPawnRight);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_Q_Press,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::MoveFreeCamPawnUp);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_E_Press,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::MoveFreeCamPawnDown);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_L_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::ToggleVRMode);

        // Pawn Rotation Mapping 
        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_ArrowKeyLeft_Press,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::RotateFreeCamPawnLeft);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_ArrowKeyRight_Press,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::RotateFreeCamPawnRight);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_ArrowKeyUp_Press,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::RotateFreeCamPawnUp);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_ArrowKeyDown_Press,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::RotateFreeCamPawnDown);

        // Toggle mouse cursor using Right Ctrl
        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_RightCtrl_Press,
            ETriggerEvent::Started,
            this,
            &AFreeCameraPawn::ToggleMouseCursor);

        // Track shift press/release
        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_LeftShift_Press,
            ETriggerEvent::Started,
            this,
            &AFreeCameraPawn::OnShiftPressed);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_LeftShift_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::OnShiftReleased);

        CurrentKeyboardDeviceHandlerObject->BindActions(

            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_B_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::ToggleBattlespaceMode);

        CurrentKeyboardDeviceHandlerObject->BindActions(

            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_C_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::ToggleCompass);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_V_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::HideEntityPreview);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_M_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::ToggleStats);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_T_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::ToggleStatsTable);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_O_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::ChangeToJTACMode);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_I_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::ChangeToISRMode);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_P_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::ChangeToBSVMode);

        CurrentKeyboardDeviceHandlerObject->BindActions(
            CurrentKeyboardDeviceHandlerObject->IA_Keyboard_LeftCtrl_Press,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::ToggleMainMenu);

    }

    if (MouseHandler)
    {
        MouseHandler->BindActions(
            MouseHandler->IA_MouseX,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::LookMouseX);

        MouseHandler->BindActions(
            MouseHandler->IA_MouseY,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::LookMouseY);

        MouseHandler->BindActions(
            MouseHandler->IA_MouseScroll,
            ETriggerEvent::Triggered,
            this,
            &AFreeCameraPawn::AdjustMouseAndMovementSensitivity);

        MouseHandler->BindActions(
            MouseHandler->IA_RightMouseButton,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::RightMouseButtonClicked);

        MouseHandler->BindActions(
            MouseHandler->IA_LeftMouseButton,
            ETriggerEvent::Completed,
            this,
            &AFreeCameraPawn::LeftMouseButtonClicked);
    }

}
void AFreeCameraPawn::ToggleVRMode(const FInputActionValue& Value)
{
    if (PlayerControllerRef)
    {
        HUD = Cast<AMetaverseHUD>(PlayerControllerRef->GetHUD());
    }
    // track state locally

    bIsVR = !bIsVR;

    if (bIsVR)
    {
        UHeadMountedDisplayFunctionLibrary::EnableHMD(true);
        if (Camera)
        {
            Camera->bLockToHmd = true;
        }

        UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
        //UE_LOG(LogTemp, Log, TEXT("VR Mode Enabled"));
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Switched to VR Mode"));
    }
    else
    {
        if (Camera)
        {
            Camera->bLockToHmd = false;
        }

        UHeadMountedDisplayFunctionLibrary::EnableHMD(false);

        APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        if (PC)
        {
            PC->ConsoleCommand(TEXT("stereo off"));
        }

        UE_LOG(LogTemp, Log, TEXT("VR Mode Disabled"));
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, TEXT("Switched to Monitor Mode"));
    }
}


void AFreeCameraPawn::ToggleBattlespaceMode(const FInputActionValue& Value)
{
    EntityManager::GetEntityManagerInstance()->ToggleBattleSpaceMode();
}



void AFreeCameraPawn::OnTriggerClick(const FInputActionValue& Value)
{

    FVector Start = RightController->GetComponentLocation();
    FVector End = Start + RightController->GetForwardVector() * 1000.0f;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params);
    if (bHit && Hit.GetActor())
    {
        UE_LOG(LogTemp, Log, TEXT("🎯 Clicked Actor: %s"), *Hit.GetActor()->GetName());


    }
}
void AFreeCameraPawn::OnLeftGripPressed(const FInputActionValue& Value)
{
    bLeftGriptHeld = true;
}

void AFreeCameraPawn::OnLeftGripReleased(const FInputActionValue& Value)
{
    bLeftGriptHeld = false;
    OnGripPressed();
}

void AFreeCameraPawn::MoveUp()
{
    FVector UpDirection = FVector::UpVector;  //GetActorUpVector();
    AddActorLocalOffset(UpDirection * MovementSpeed * GetWorld()->GetDeltaSeconds(), true);
}

void AFreeCameraPawn::MoveDown()
{

    FVector UpDirection = FVector::UpVector; // GetActorUpVector();
    AddActorLocalOffset(-UpDirection * MovementSpeed * GetWorld()->GetDeltaSeconds(), true);

}

void AFreeCameraPawn::MoveForward()
{
    FVector ForwardDirection = Camera->GetForwardVector(); //FVector::ForwardVector; // GetActorForwardVector();
    AddActorLocalOffset(ForwardDirection * MovementSpeed * GetWorld()->GetDeltaSeconds(), true);

}

void AFreeCameraPawn::MoveBackward()
{
    FVector ForwardDirection = Camera->GetForwardVector(); //FVector::ForwardVector; //GetActorForwardVector();
    AddActorLocalOffset(-ForwardDirection * MovementSpeed * GetWorld()->GetDeltaSeconds(), true);
}

void AFreeCameraPawn::MoveLeft()
{
    FVector RightDirection = Camera->GetRightVector();; //FVector::RightVector; // GetActorRightVector();
    AddActorLocalOffset(-RightDirection * MovementSpeed * GetWorld()->GetDeltaSeconds(), true);
}

void AFreeCameraPawn::MoveRight()
{
    FVector RightDirection = Camera->GetRightVector();; //FVector::RightVector;  //GetActorRightVector();
    AddActorLocalOffset(RightDirection * MovementSpeed * GetWorld()->GetDeltaSeconds(), true);
}

// Pawn Movement 
void AFreeCameraPawn::MoveFreeCamPawnForward(const FInputActionValue& Value)
{
    //GEngine->AddOnScreenDebugMessage(-1, 0.0, FColor::Green, Value.ToString());
    // using FVector::XYZ to ensure that pawn moves relative to its own orientation 

    if (bLeftGriptHeld && Value.GetMagnitude() > 0.5)
    {
        MoveUp();                                   // VR controller MoveUp
        return;
    }
    else if (bLeftGriptHeld && Value.GetMagnitude() < 0.5)
    {
        MoveDown();                                 // VR controller MoveDown
        return;
    }
    if (Value.ToString() == "true") {               // Keyboard
        MoveForward();
    }
    else if (Value.GetMagnitude() > 0.5) {            // VR controller MoveForward
        MoveForward();
    }
    else if (Value.GetMagnitude() < -0.5) {            // VR controller MoveBackward
        MoveBackward();
    }
}

void AFreeCameraPawn::MoveFreeCamPawnBackward(const FInputActionValue& Value)
{
    MoveBackward();                                 // Keyboard
}

void AFreeCameraPawn::MoveFreeCamPawnLeft(const FInputActionValue& Value)
{

    if (Value.ToString() == "true") {               // Keyboard
        MoveLeft();
    }
    else if (Value.GetMagnitude() > 0.5) {            // VR controller MoveRight
        MoveRight();
    }
    else if (Value.GetMagnitude() < -0.5) {            // VR controller MoveLeft
        MoveLeft();
    }

}

void AFreeCameraPawn::MoveFreeCamPawnRight(const FInputActionValue& Value)
{
    MoveRight();                                    // Keyboard
}

void AFreeCameraPawn::MoveFreeCamPawnUp(const FInputActionValue& Value)
{
    MoveUp();                                       // Keyboard
}

void AFreeCameraPawn::MoveFreeCamPawnDown(const FInputActionValue& Value)
{
    MoveDown();                                     // Keyboard
}

// Pawn Rotation 
void AFreeCameraPawn::RotateFreeCamPawnLeft(const FInputActionValue& Value)
{
    Yaw = Yaw - Value.GetMagnitude();
    FRotator newRotation = FRotator(Pitch, Yaw, 0.0);
    Camera->SetRelativeRotation(newRotation);

}
void AFreeCameraPawn::RotateFreeCamPawnRight(const FInputActionValue& Value)
{
    Yaw = Yaw + Value.GetMagnitude();
    FRotator newRotation = FRotator(Pitch, Yaw, 0.0);
    Camera->SetRelativeRotation(newRotation);
}
void AFreeCameraPawn::RotateFreeCamPawnUp(const FInputActionValue& Value)
{
    if (Pitch < 85.0f) {
        Pitch = Pitch + Value.GetMagnitude();
        FRotator newRotation = FRotator(Pitch, Yaw, 0.0);
        Camera->SetRelativeRotation(newRotation);
    }
}
void AFreeCameraPawn::RotateFreeCamPawnDown(const FInputActionValue& Value)
{
    if (Pitch > -85.0f) {
        Pitch = Pitch - Value.GetMagnitude();
        FRotator newRotation = FRotator(Pitch, Yaw, 0.0);
        Camera->SetRelativeRotation(newRotation);
    }

}

//Mouse Locking And Unlocking
void AFreeCameraPawn::ToggleMouseCursor(const FInputActionValue& Value)
{

    if (PlayerControllerRef)
    {
        if (!bIsMouseFree)
        {
            bIsMouseFree = true;
            PlayerControllerRef->bShowMouseCursor = true;
            PlayerControllerRef->SetInputMode(FInputModeGameAndUI());
            return;


        }

        else if (bIsMouseFree)
        {
            bIsMouseFree = false;
            PlayerControllerRef->bShowMouseCursor = false;
            PlayerControllerRef->SetInputMode(FInputModeGameOnly());
            return;
        }
    }
}

void AFreeCameraPawn::LookMouseX(const FInputActionValue& Value)
{
    if (!bIsMouseFree) // only rotate camera if not in UI cursor mode
    {
        if (IsHooked) {


            FVector2D LookAxis = Value.Get<FVector2D>();
            FRotator NewRot = SpringArm->GetRelativeRotation();
            NewRot.Yaw += LookAxis.X * 3.0f;

            SpringArm->SetRelativeRotation(FRotator(NewRot.Pitch, NewRot.Yaw, 0.0f));

        }
        else {
            Yaw = Yaw + Value.GetMagnitude();
            FRotator newRotation = FRotator(Pitch, Yaw, 0.0);
            Camera->SetRelativeRotation(newRotation);
        }
    }

}

void AFreeCameraPawn::LookMouseY(const FInputActionValue& Value)
{
    if (!bIsMouseFree)
    {
        if (IsHooked) {
            if (Pitch < 85.0f && Pitch > -85.0f) {
                FRotator NewRot = SpringArm->GetRelativeRotation();
                Pitch = Pitch + Value.GetMagnitude();
                FRotator newRotation = FRotator(Pitch, NewRot.Yaw, 0.0f);
                SpringArm->SetRelativeRotation(newRotation);

                if (Pitch >= 85.0f) Pitch = 84.99f;
                if (Pitch <= -85.0f) Pitch = -84.99f;


            }
        }
        else
        {
            if (Pitch < 85.0f && Pitch > -85.0f) {
                Pitch = Pitch + Value.GetMagnitude();
                FRotator newRotation = FRotator(Pitch, Yaw, 0.0);
                Camera->SetRelativeRotation(newRotation);

                if (Pitch >= 85.0f) Pitch = 84.99f;
                if (Pitch <= -85.0f) Pitch = -84.99f;

            }
        }
    }

}

void AFreeCameraPawn::RightMouseButtonClicked(const FInputActionValue& Value)
{
    FHitResult Hit;
    PlayerControllerRef->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, Hit);
    RemoteEntity = Cast<AEntityBase>(Hit.GetActor());
    UE_LOG(LogTemp, Log, TEXT("Movement Speed adjusted to"));

    if (RemoteEntity)
    {
        FVector WorldLocation = Hit.Location;
        FVector2d ScreenPosition;

        if (PlayerControllerRef->ProjectWorldLocationToScreen(WorldLocation, ScreenPosition))
        {
            if (ContextMenuInstance)
            {

                if (PlayerControllerRef->GetMousePosition(MouseXPosition, MouseYPosition))
                {

                    ContextMenuInstance->SetPositionInViewport(FVector2D(MouseXPosition, MouseYPosition), true);
                    ContextMenuInstance->SetAlignmentInViewport(FVector2D(0.0f, 0.0f));
                    ContextMenuInstance->SetVisibility(ESlateVisibility::Visible);
                    ContextMenuInstance->Init(RemoteEntity);
                }
            }


        }

    }
}

void AFreeCameraPawn::LeftMouseButtonClicked(const FInputActionValue& Value)
{
    UIManager::GetInstance()->CloseAllOpenMenu();
    UIManager::GetInstance()->HidAllMenus();
    UIManager::close();
}

void AFreeCameraPawn::AdjustMouseAndMovementSensitivity(const FInputActionValue& Value)
{
    float ScrollValue = Value.Get<float>();

    if (bIsShiftHeld)
    {
        MovementSpeed += ScrollValue * 3000.0f;  // Tune this multiplier
        MovementSpeed = FMath::Clamp(MovementSpeed, 100.0f, 1000000000.0f);
        UE_LOG(LogTemp, Log, TEXT("Movement Speed adjusted to: %f"), MovementSpeed);

    }
    else
    {
        MouseSensitivity += ScrollValue * 1.0f;  // Tune as needed
        MouseSensitivity = FMath::Clamp(MouseSensitivity, 0.1f, 20.0f);
        UE_LOG(LogTemp, Log, TEXT("Mouse Sensitivity adjusted to: %f"), MouseSensitivity);

    }
    if (IsHooked) {
        if (ScrollValue > 0.5f)
        {
            SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength - 100.0f, MinArmLength * 100, 5000.0f);
        }
        if (ScrollValue < 0.5f)
        {
            SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength + 100.0f, MinArmLength * 100, 5000.0f);
        }
    }
    else {

    }


}

void AFreeCameraPawn::OnShiftPressed(const FInputActionValue& Value)
{
    bIsShiftHeld = true;
}

void AFreeCameraPawn::OnShiftReleased(const FInputActionValue& Value)
{
    bIsShiftHeld = false;
}

void AFreeCameraPawn::ToggleHook(AEntityBase* Entity, bool Hooked)
{

    IsHooked = Hooked;
    if (Entity == nullptr)
        Entity = EntityManager::GetEntityManagerInstance()->GetEntity();

    MinArmLength = Entity->entityLength;

    if (Entity)
    {
        if (IsHooked)
        {

            AttachToActor(Entity, FAttachmentTransformRules::KeepWorldTransform);
            FVector LocalOffset = FVector(-4500.f, 0.f, 1000.f);
            FVector WorldOffset = Entity->GetActorRotation().RotateVector(LocalOffset);
            FVector TargetLocation = Entity->GetActorLocation();
            SetActorLocation(TargetLocation);

            FRotator LookAtRotation = (TargetLocation - GetActorLocation()).Rotation();
            LookAtRotation.Roll = 0;
            SetActorRotation(LookAtRotation);


            OrbitPivot->AttachToComponent(CapsuleBody, FAttachmentTransformRules::KeepWorldTransform);
            Camera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
            SpringArm->AttachToComponent(CapsuleBody, FAttachmentTransformRules::KeepWorldTransform);
            // Camera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
            OrbitPivot->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepWorldTransform);
            Camera->AttachToComponent(OrbitPivot, FAttachmentTransformRules::KeepWorldTransform);
            /*Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);*/
            OrbitPivot->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
            Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
            Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
            Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));

            SpringArm->TargetArmLength = 1300.0f;


            USceneComponent* TargetRoot = Entity->GetRootComponent();
            FTransform ComponentTransform = TargetRoot->GetComponentTransform();
            GetRootComponent()->SetWorldTransform(ComponentTransform);

            SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
            SpringArm->SetRelativeRotation(FRotator(-90.0f, 0.0f, 0.0f));
            OrbitPivot->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            OrbitPivot->SetCollisionResponseToAllChannels(ECR_Block);
            OrbitPivot->SetCollisionObjectType(ECC_Pawn);
            //  Ignoring RayTracing collision for mouseclickevent to CapsuleBody ...
            OrbitPivot->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

            SpringArm->SocketOffset = FVector(0, 0, 50);
            SpringArm->bUsePawnControlRotation = false;
            SpringArm->bInheritPitch = false;
            SpringArm->bInheritYaw = false;
            SpringArm->bInheritRoll = false;
            SpringArm->bDoCollisionTest = false;

        }
        else
        {
            DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            SetActorTransform(FreeCameraTransform);
            Camera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
            SpringArm->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
            Camera->AttachToComponent(CapsuleBody, FAttachmentTransformRules::KeepWorldTransform);
            Camera->bUsePawnControlRotation = false;
            Camera->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
            Camera->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
            CapsuleBody->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            CapsuleBody->SetCollisionResponseToAllChannels(ECR_Block);
            CapsuleBody->SetCollisionObjectType(ECC_Pawn);
            //  Ignoring RayTracing collision for mouseclickevent to CapsuleBody ...
            CapsuleBody->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);

        }
    }
}

void AFreeCameraPawn::ToggleCompass(const FInputActionValue& Value)
{

    if (CompassWidgetComponent)
    {
        bIsCompassVisible = CompassWidgetComponent->IsVisible();
        CompassWidgetComponent->SetVisibility(!bIsCompassVisible);
    }


}

void AFreeCameraPawn::SpawnSceneCaptureComponent2D(AEntityBase* Entity)
{
    //USceneCaptureComponent2D* SceneCapture = Cast<USceneCaptureComponent2D>(SpawnedActor->FindComponentByClass(USceneCaptureComponent2D));
    if (SpawnedActor)
    {
        /*   SpawnedActor->AttachToActor(Entity, FAttachmentTransformRules::KeepWorldTransform);

           FVector TargetLocation = Entity->GetActorLocation();
           FVector CameraOffset(-1500.f, 0.f, 500.f);
           FVector NewCameraLocation = TargetLocation + CameraOffset;
           SpawnedActor->SetActorLocation(NewCameraLocation);*/

        SpawnedActor->AttachToActor(Entity, FAttachmentTransformRules::KeepWorldTransform);
        FVector LocalOffset = FVector(-1500.f, 0.f, 500.f);
        FVector WorldOffset = Entity->GetActorRotation().RotateVector(LocalOffset);
        FVector TargetLocation = Entity->GetActorLocation();
        SpawnedActor->SetActorLocation(TargetLocation + WorldOffset);

        FRotator LookAtRotation = (TargetLocation - SpawnedActor->GetActorLocation()).Rotation();
        LookAtRotation.Roll = 0;
        SpawnedActor->SetActorRotation(LookAtRotation);
        //HidePreview(false);

    }

}

void AFreeCameraPawn::ShowEntityPreview(AEntityBase* Entity)
{
    SpawnSceneCaptureComponent2D(RemoteEntity);

    //bool bIsVisible = RemoteEntityWidgetComponent->IsVisible();
    //RemoteEntityWidgetComponent->SetVisibility(true);
}

void AFreeCameraPawn::HideEntityPreview(const FInputActionValue& Value)
{

    //RemoteEntityWidgetComponent->SetVisibility(false);
}

void AFreeCameraPawn::OnGripPressed()
{

    FHitResult Hit;
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(this);
    bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, LeftControllerStart, LeftControllerEnd, ECC_Visibility, TraceParams);

    if (bHit)
    {
        RemoteEntity = GetComponentInParent(Hit.GetActor());
        if (RemoteEntity)
        {
            ShowEntityPreview(RemoteEntity);
        }

    }

}

AEntityBase* AFreeCameraPawn::GetComponentInParent(AActor* Actor)
{
    while (Actor)
    {
        AEntityBase* EntityBase = Cast<AEntityBase>(Actor);
        if (EntityBase)
        {
            return EntityBase;
        }
        Actor = Actor->GetAttachParentActor();
    }
    return nullptr;
}

void AFreeCameraPawn::devFun()
{

}

void AFreeCameraPawn::SetCompassPosition()
{

    FVector CamLocation = Camera->GetComponentLocation();
    FRotator CamRotation = Camera->GetComponentRotation();
    FVector Forward = CamRotation.Vector();
    FVector Up = FVector::UpVector;

    float DistanceForward = 150.f;
    float OffsetDown = -25.0f;

    FVector WidgetLocation = CamLocation + (Forward * DistanceForward) + (Up * OffsetDown);
    CompassWidgetComponent->SetWorldLocation(WidgetLocation);
    FVector ToCamera = CamLocation - WidgetLocation;
    ToCamera.Normalize();
    FVector UpVector = FVector::UpVector;
    FRotator LookAtRotation = FRotationMatrix::MakeFromXZ(ToCamera, UpVector).Rotator();
    LookAtRotation.Pitch += 45;

    CompassWidgetComponent->SetWorldRotation(LookAtRotation);

}

void AFreeCameraPawn::ToggleStats(const FInputActionValue& Value)
{
    if (ExerciseStatsWidgetComponent && AExerciseStatsManager::GetInstance())
    {
        bIsStatsVisible = ExerciseStatsWidgetComponent->IsVisible();
        ExerciseStatsWidgetInstance->UpdateStatsData(AExerciseStatsManager::GetInstance()->GetEntityStats());
        ExerciseStatsWidgetComponent->SetVisibility(!bIsStatsVisible);
    }
}

void AFreeCameraPawn::SetStatsPosition()
{

    FVector CamLocation = Camera->GetComponentLocation();
    FRotator CamRotation = Camera->GetComponentRotation();
    FVector Forward = CamRotation.Vector();
    //FVector Up = FVector::UpVector;
    FVector Up = CamRotation.RotateVector(FVector::UpVector);

    float DistanceForward = 150.f;
    float OffsetDown = -25.0f;

    FVector WidgetLocation = CamLocation + (Forward * DistanceForward) + (Up * OffsetDown);
    ExerciseStatsWidgetComponent->SetWorldLocation(WidgetLocation);
    FVector ToCamera = CamLocation - WidgetLocation;
    ToCamera.Normalize();
    //FVector UpVector = FVector::UpVector;
    FVector UpVector = Up;

    FRotator LookAtRotation = FRotationMatrix::MakeFromXZ(ToCamera, UpVector).Rotator();

    ExerciseStatsWidgetComponent->SetWorldRotation(LookAtRotation);

}



void AFreeCameraPawn::SetStatsTablePosition()
{

    FVector CamLocation = Camera->GetComponentLocation();
    FRotator CamRotation = Camera->GetComponentRotation();
    FVector Forward = CamRotation.Vector();
    //FVector Up = FVector::UpVector;
    FVector Up = CamRotation.RotateVector(FVector::UpVector);

    float OffsetDown = -35.0f;

    FVector WidgetLocation = CamLocation + (Forward * TestDistanceForward) + (Up * OffsetDown);
    StatsTableComponent->SetWorldLocation(WidgetLocation);
    FVector ToCamera = CamLocation - WidgetLocation;
    ToCamera.Normalize();
    //FVector UpVector = FVector::UpVector;
    FVector UpVector = Up;

    FRotator LookAtRotation = FRotationMatrix::MakeFromXZ(ToCamera, UpVector).Rotator();
    LookAtRotation.Pitch -= 30;
    StatsTableComponent->SetWorldRotation(LookAtRotation);

}


void AFreeCameraPawn::ToggleStatsTable(const FInputActionValue& Value)
{
    if (StatsTableComponent && AExerciseStatsManager::GetInstance())
    {
        if (StatsTableImageIndex == 4) StatsTableImageIndex = -1;
        StatsTableImageIndex++;
        StatsTableInstance->UpdateStatsTableData(StatsTableImageIndex, AExerciseStatsManager::GetInstance()->GetEntityStats());

    }
}

void AFreeCameraPawn::ChangeToJTACMode(const FInputActionValue& Value)
{
    UIManager::GetInstance()->HidAllMenus();
    UIManager::GetInstance()->close();
    AModeManager::getInstance()->setActiveMode(*AModeManager::getInstance()->MetaverseModes.Find(FName(TEXT("JTAC"))));
    AScalingManager::GetInstance()->scale = false;
    AScalingManager::GetInstance()->isShowLabel = false;
    if (!AModeManager::getInstance()->getActiveMode()->bMenuVisible)
    {
        UIManager::GetInstance()->HideMenu(EMenus::MainMenu);
    }
    else {
        UIManager::GetInstance()->ShowMenu(EMenus::MainMenu);
    }
    if (!AModeManager::getInstance()->getActiveMode()->bStatusBarVisible)
    {
        UIManager::GetInstance()->HideMenu(EMenus::StatusBar);
    }
    else {
        UIManager::GetInstance()->ShowMenu(EMenus::StatusBar);
    }

    for (EMenus Menu : TEnumRange<EMenus>())
    {
        if (auto* w = Cast<UMenuParent>(UIManager::GetInstance()->MenuWidgetMap.FindRef(Menu)))
            w->ApplyMode(AModeManager::getInstance()->getActiveMode());
    }
    for (TActorIterator<AEntityBase> It(GetWorld()); It; ++It) {
        AEntityBase* Entity = *It;
        if (Entity)
        {
            Entity->ApplyMode();
        }
    }
    UCoveragesManager::GetInstance()->ToggleVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::GroundCoverages).FeatureActive);
    UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::AircraftCoverage).FeatureActive, ERemoteEntityType::FIXEDWING_AIRCRAFT);

}

void AFreeCameraPawn::ChangeToISRMode(const FInputActionValue& Value)
{
    UIManager::GetInstance()->HidAllMenus();
    UIManager::GetInstance()->close();
    AModeManager::getInstance()->setActiveMode(*AModeManager::getInstance()->MetaverseModes.Find(FName(TEXT("ISR"))));
    AScalingManager::GetInstance()->scale = false;
    AScalingManager::GetInstance()->isShowLabel = false;
    if (!AModeManager::getInstance()->getActiveMode()->bMenuVisible)
    {
        UIManager::GetInstance()->HideMenu(EMenus::MainMenu);
    }
    else {
        UIManager::GetInstance()->ShowMenu(EMenus::MainMenu);
    }
    if (!AModeManager::getInstance()->getActiveMode()->bStatusBarVisible)
    {
        UIManager::GetInstance()->HideMenu(EMenus::StatusBar);
    }
    else {
        UIManager::GetInstance()->ShowMenu(EMenus::StatusBar);
    }
    for (EMenus Menu : TEnumRange<EMenus>())
    {
        if (auto* w = Cast<UMenuParent>(UIManager::GetInstance()->MenuWidgetMap.FindRef(Menu)))
            w->ApplyMode(AModeManager::getInstance()->getActiveMode());
    }
    for (TActorIterator<AEntityBase> It(GetWorld()); It; ++It) {
        AEntityBase* Entity = *It;
        if (Entity)
        {
            Entity->ApplyMode();
        }
    }

    for (TObjectIterator<UNiagaraComponent> It; It; ++It) {
        UNiagaraComponent* Effect = *It;
        if (Effect)
        {
            Effect->DeactivateImmediate();
        }
    }
    UCoveragesManager::GetInstance()->ToggleVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::GroundCoverages).FeatureActive);
    UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::AircraftCoverage).FeatureActive, ERemoteEntityType::FIXEDWING_AIRCRAFT);
}

void AFreeCameraPawn::ChangeToBSVMode(const FInputActionValue& Value)
{
    UIManager::GetInstance()->HidAllMenus();
    UIManager::GetInstance()->close();
    AModeManager::getInstance()->setActiveMode(*AModeManager::getInstance()->MetaverseModes.Find(FName(TEXT("BSV"))));
    AScalingManager::GetInstance()->scale = true;
    AScalingManager::GetInstance()->isShowLabel = true;
    if (!AModeManager::getInstance()->getActiveMode()->bMenuVisible)
    {
        UIManager::GetInstance()->HideMenu(EMenus::MainMenu);
    }
    else {
        UIManager::GetInstance()->ShowMenu(EMenus::MainMenu);

    }
    if (!AModeManager::getInstance()->getActiveMode()->bStatusBarVisible)
    {
        UIManager::GetInstance()->HideMenu(EMenus::StatusBar);
    }
    else {
        UIManager::GetInstance()->ShowMenu(EMenus::StatusBar);
    }

    for (EMenus Menu : TEnumRange<EMenus>())
    {
        if (auto* w = Cast<UMenuParent>(UIManager::GetInstance()->MenuWidgetMap.FindRef(Menu)))
            w->ApplyMode(AModeManager::getInstance()->getActiveMode());
    }
    for (TActorIterator<AEntityBase> It(GetWorld()); It; ++It) {
        AEntityBase* Entity = *It;
        if (Entity)
        {
            Entity->ApplyMode();
            //Entity->ResetTrails();
        }
    }

    for (TObjectIterator<UNiagaraComponent> It; It; ++It) {
        UNiagaraComponent* Effect = *It;
        if (Effect)
        {
            Effect->DeactivateImmediate();
        }
    }
    UCoveragesManager::GetInstance()->ToggleVisibility(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::GroundCoverages).FeatureActive);
    UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::AircraftCoverage).FeatureActive, ERemoteEntityType::FIXEDWING_AIRCRAFT);
}

void AFreeCameraPawn::ToggleMainMenu(const FInputActionValue& Value)
{
    TObjectPtr<UUserWidget>* Found1 = UIManager::GetInstance()->MenuWidgetMap.Find(EMenus::MainMenu);
    UUserWidget* FoundPtr1 = Found1->Get();
    for (EMenus Menu : TEnumRange<EMenus>())
    {
        if (auto* w = Cast<UMenuParent>(UIManager::GetInstance()->MenuWidgetMap.FindRef(Menu)))
            w->ApplyMode(AModeManager::getInstance()->getActiveMode());
    }
    if (FoundPtr1->IsInViewport())
    {
        UIManager::GetInstance()->HideMenu(EMenus::MainMenu);
    }
    else {
        UIManager::GetInstance()->ShowMenu(EMenus::MainMenu);
    }



}


