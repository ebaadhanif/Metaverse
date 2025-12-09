#pragma once
#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "Components/WidgetInteractionComponent.h"
#include "MotionControllerComponent.h"
#include "../Team SimBridge/EntityManager.h"
#include "MetaverseHUD.h"
#include "../Team SimBridge/EntityBase.h"
#include "../Team Visioneers/AirBaseManager.h"
#include "../Team Visioneers/CmpassWidget.h"
#include "../Team Visioneers/ContextMenuWidget.h"
#include "../Team Visioneers/ExerciseStatsManager.h"
#include "../Team Visioneers/ExerciseStatsWidget.h"
#include "../Team Visioneers/StatsTable.h"
#include "HanTracking.h"
#include "GameFramework/SpringArmComponent.h"
#include "CesiumGlobeAnchorComponent.h"
//#include "RuntimeGen/GenSources/PCGGenSourceComponent.h"
#include "LoadingManager.h"
#include "FreeCameraPawn.generated.h"
class DisplayManager;
class UCapsuleComponent;
UCLASS()
class METAVERSE_API AFreeCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	AFreeCameraPawn();



	UInstancedStaticMeshComponent* TipSpheresL = nullptr;
	UInstancedStaticMeshComponent* TipSpheresR = nullptr;

	//UCesiumGlobeAnchorComponent* globeAnchor;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	UCameraComponent* Camera; 

	UCapsuleComponent* CapsuleBody;

	USceneComponent* SmoothedActor;

	//This section holds VR Related Declarations:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector HandOffset;

	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* LeftController;

	UPROPERTY(VisibleAnywhere)
	UMotionControllerComponent* RightController;

	// Hand Meshes for visual feedback
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LeftHandMesh;
	// Haptic FeedBack for Controller Trigger
	UPROPERTY(EditAnywhere, Category = "Haptic")
	TObjectPtr<UHapticFeedbackEffect_Base> TriggerHaptic;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RightHandMesh;

	// Compass Widget Class.
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> CompassWidgetClass;

	// Compass Widget Instance.
	UPROPERTY(EditAnywhere)
	UCmpassWidget* CompassWidgetInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VR UI")
	class UWidgetComponent* CompassWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> RemoteEntityPreviewClass;

	UPROPERTY()
	TSubclassOf<AActor> CaptureClass;

	AActor* SpawnedActor;

	UPROPERTY(VisibleAnywhere, Category = "UI")
	UWidgetComponent* RemoteEntityWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ExerciseStatsWidgetClass;

	UPROPERTY(EditAnywhere)
	UExerciseStatsWidget* ExerciseStatsWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VR UI")
	class UWidgetComponent* ExerciseStatsWidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> StatsTableClass;

	UPROPERTY(EditAnywhere)
	UStatsTable* StatsTableInstance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "VR UI")
	class UWidgetComponent* StatsTableComponent;

	// Context Menu Widget Class.
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> ContextMenuClass;

	// Context Menu Widget Instance.
	UPROPERTY(EditAnywhere)
	UContextMenuWidget* ContextMenuInstance;

	UPROPERTY(VisibleAnywhere)
	UCesiumGlobeAnchorComponent* GlobeAnchor;
	UPROPERTY()
	USpringArmComponent* SpringArm;
	UPROPERTY()
	UCapsuleComponent* OrbitPivot;


	EntityManager* EntityManager;
	AEntityBase* RemoteEntity;
	bool IsHooked = false;
	int StatsTableImageIndex = -1;

	bool bIsStatsVisible = true;
	bool bIsCompassVisible = false;
	FVector LeftControllerStart, LeftControllerEnd;

  static UCameraComponent* GetCamera();
  AVRWidgetActor* VRActor;

protected:
	virtual void BeginPlay() override;
	UPROPERTY()
	ALoadingManager* loadingManager;
public:
	virtual void Tick(float DeltaTime) override;

	void OnLeftGripPressed(const FInputActionValue& Value);

	void OnLeftGripReleased(const FInputActionValue& Value);

	void OnTriggerClick(const FInputActionValue& Value);

	void ToggleBattlespaceMode(const FInputActionValue& Value);


	void MoveUp();

	void MoveDown();

	void MoveForward();

	void MoveBackward();

	void MoveLeft();

	void MoveRight();

	void MoveFreeCamPawnForward(const FInputActionValue& Value);

	void MoveFreeCamPawnBackward(const FInputActionValue& Value);

	void MoveFreeCamPawnLeft(const FInputActionValue& Value);

	void MoveFreeCamPawnRight(const FInputActionValue& Value);

	void MoveFreeCamPawnUp(const FInputActionValue& Value);

	void MoveFreeCamPawnDown(const FInputActionValue& Value);

	void RotateFreeCamPawnLeft(const FInputActionValue& Value);

	void RotateFreeCamPawnRight(const FInputActionValue& Value);

	void RotateFreeCamPawnUp(const FInputActionValue& Value);

	void RotateFreeCamPawnDown(const FInputActionValue& Value);

	void ToggleMouseCursor(const FInputActionValue& Value);

	void LookMouseX(const FInputActionValue& Value);

	void LookMouseY(const FInputActionValue& Value);

	void RightMouseButtonClicked(const FInputActionValue& Value);
	void LeftMouseButtonClicked(const FInputActionValue& Value);

	void BindSpecificDeviceInputActionsToFunctions();

	UFUNCTION()
	void AdjustMouseAndMovementSensitivity(const FInputActionValue& Value);

	UFUNCTION()
	void ToggleVRMode(const FInputActionValue& Value);

	void OnShiftPressed(const FInputActionValue& Value);

	void OnShiftReleased(const FInputActionValue& Value);

	void ToggleHook(AEntityBase* Entity, bool hook);

	void SetCompassPosition();

	void SpawnSceneCaptureComponent2D(AEntityBase* Entity);
	void ShowEntityPreview(AEntityBase* Entity);
	void HideEntityPreview(const FInputActionValue& Value);
	void OnGripPressed();
	AEntityBase* GetComponentInParent(AActor* From);


	void ToggleStats(const FInputActionValue& Value);
	void SetStatsPosition();
	void SetStatsTablePosition();
	void ToggleStatsTable(const FInputActionValue& Value);
	void ChangeToJTACMode(const FInputActionValue& Value);
	void ChangeToISRMode(const FInputActionValue& Value);

	void ChangeToBSVMode(const FInputActionValue& Value);
	void ToggleMainMenu(const FInputActionValue& Value);

	void devFun();

	bool IsStatsTableVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement and Rotation Speed");
	float MovementSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement and Rotation Speed");
	float RotationSpeed = 500.0f;

	bool bIsMouseFree = false;
	bool bIsActorVisible = false;
	bool bIsVR = false;
	AHanTracking* HandTrackingActor= nullptr;
	APlayerController* PlayerControllerRef = nullptr;
	AMetaverseHUD* HUD = nullptr;
	// Optional sensitivity control
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mouse Camera Control")
	float MouseSensitivity = 10.0f;

	bool bLeftGriptHeld = false;
	bool bIsShiftHeld = false;

	float Yaw = 0;
	float Pitch = 0;
	float GroundTraceDistance = 999999999;
	float GroundClearance = 20;
	FCollisionQueryParams params;
	bool isGrounded = false;

	UPROPERTY(EditAnywhere)
	float TestDistanceForward = 45;

	float MouseXPosition, MouseYPosition;
	bool DisplayingCompass = false;
	void ToggleCompass(const FInputActionValue& Value);

	double heightFromGround = 0;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	//UPCGGenSourceComponent* PCGGenSource;


	float MinArmLength;
	FTransform FreeCameraTransform;

};
