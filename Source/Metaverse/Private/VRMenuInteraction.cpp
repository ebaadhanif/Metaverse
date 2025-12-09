#include "VRMenuInteraction.h"
#include "../Team Visioneers/Menus/UIManager.h"
#include "TimerManager.h"   
#include <Metaverse/Team Visioneers/DisplayManager.h>

// Sets default values
AVRMenuInteraction::AVRMenuInteraction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WidgetInteractor = CreateDefaultSubobject<UWidgetInteractionComponent>(TEXT("WidgetInteractor"));
	WidgetInteractor->PointerIndex = 0;
	WidgetInteractor->InteractionSource = EWidgetInteractionSource::World;
	WidgetInteractor->bEnableHitTesting = true;
	WidgetInteractor->bShowDebug = false;
	WidgetInteractor->TraceChannel = ECollisionChannel::ECC_Visibility;

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMesh"));
	SphereMesh->SetRelativeScale3D(FVector(0.0175f, 0.0175f, 0.0175f));
	SphereMesh->SetCollisionResponseToAllChannels(ECR_Ignore);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> ContactSphere(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (ContactSphere.Succeeded())
	{
		SphereMesh->SetStaticMesh(ContactSphere.Object);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> NewSphereMaterial(TEXT("/Game/Materials/M_Sphere.M_Sphere"));
	if (NewSphereMaterial.Succeeded()) {
		SphereMaterial = NewSphereMaterial.Object;
	}

}

void AVRMenuInteraction::BeginPlay()
{
	Super::BeginPlay();
	if (SphereMaterial)
		SphereMesh->SetMaterial(0, SphereMaterial);
}

void AVRMenuInteraction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ADisplayManager::GetInstance()->HandTrackingActor != nullptr && ADisplayManager::GetInstance()->isVRMode)
	{
		VRMenuHandler(DeltaTime);
		VRMenuClick(DeltaTime);
	}
}

void AVRMenuInteraction::VRMenuHandler(float DeltaSeconds)
{
	if (!(GEngine && GEngine->XRSystem.IsValid()))
		return;
	if (AHanTracking::GetInstance())
	{

		bL = AHanTracking::GetInstance()->GetHandKeypoints(EControllerHand::Left, LP, LR, LRd);
		bIsGrabbing = AHanTracking::GetInstance()->IsGrabbing(LP);

		if (bIsGrabbing && !AHanTracking::GetInstance()->bPrevGrabState) {
			AHanTracking::GetInstance()->bMenuLockedByGrab = !AHanTracking::GetInstance()->bMenuLockedByGrab;
		}
		AHanTracking::GetInstance()->bPrevGrabState = bIsGrabbing;

		if (AHanTracking::GetInstance()->bMenuLockedByGrab) {
			if (AHanTracking::GetInstance()->IsPalmFacingCamera(LR, LP)) {
			UIManager::GetInstance()->ShowMenuVR(UIManager::GetInstance()->CurrentMenu);

			}
			else {
				UIManager::GetInstance()->HideMenuVR(UIManager::GetInstance()->CurrentMenu);

			}
		}
		else {
			UIManager::GetInstance()->HideMenuVR(UIManager::GetInstance()->CurrentMenu);

		}
	}

	if (!ADisplayManager::GetInstance()->isVRMode)
	{
		UIManager::GetInstance()->HideMenuVR(UIManager::GetInstance()->CurrentMenu);

	}

}

void AVRMenuInteraction::ReactivateInteractor()
{
	WidgetInteractor->Activate();
}

void AVRMenuInteraction::VRMenuClick(float DeltaSeconds)
{
	if (!(GEngine && GEngine->XRSystem.IsValid()))
		return;
	bR = AHanTracking::GetInstance()->GetHandKeypoints(EControllerHand::Right, RP, RR, RRd);
	bIsPointing = AHanTracking::GetInstance()->IsPointing(RP, RR);

	IndexTip = (int32)EHandKeypoint::IndexTip;
	if (RP.IsValidIndex(IndexTip)) {
		RawIndexLoc = RP[IndexTip];
		RawIndexQuat = RR[IndexTip];

		WidgetInteractor->SetWorldLocation(RawIndexLoc);
		WidgetInteractor->SetWorldRotation(RawIndexQuat);

		HitResult = WidgetInteractor->GetLastHitResult();

		bIsPointing = AHanTracking::GetInstance()->IsPointing(RP, RR);
		if (HitResult.bBlockingHit) {
			Distance = FVector::Dist(RawIndexLoc, HitResult.ImpactPoint);

			if (Distance <= ClickDistance) {
				SphereMesh->SetVisibility(true);
				SphereMesh->SetWorldLocation(RawIndexLoc);
				bIsClicking = true;
				WidgetInteractor->PressPointerKey(EKeys::LeftMouseButton);
				WidgetInteractor->ReleasePointerKey(EKeys::LeftMouseButton);
				WidgetInteractor->Deactivate();
				GetWorldTimerManager().SetTimer(
					ReEnableTimerHandle,
					this,
					&AVRMenuInteraction::ReactivateInteractor,
					0.4f,
					false);
			}
			else {
				SphereMesh->SetVisibility(false);
			}
		}
	}
}

