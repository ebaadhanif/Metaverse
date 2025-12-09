#include "VRWidgetActor.h"
#include "../Menus/UIManager.h"
#include "FreeCameraPawn.h"

AVRWidgetActor::AVRWidgetActor()
{
	PrimaryActorTick.bCanEverTick = true;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetWidgetSpace(EWidgetSpace::World);
	WidgetComponent->SetDrawAtDesiredSize(true); 
	WidgetComponent->SetPivot(FVector2D(0.5f, 0.5f));
	WidgetComponent->SetTwoSided(true);
	WidgetComponent->SetRelativeScale3D(FVector(0.03f));
	WidgetComponent->SetRelativeRotation(FRotator(0.f, 0.f, 180.f));
	WidgetComponent->SetWindowFocusable(false);
	RootComponent = WidgetComponent;
}

void AVRWidgetActor::BeginPlay()
{
	Super::BeginPlay();
	if (!WidgetComponent->GetWidget())
	{
		WidgetComponent->InitWidget();
	}
	if (UUserWidget* UW = Cast<UUserWidget>(WidgetComponent->GetWidget()))
	{
		UW->SetVisibility(ESlateVisibility::Visible);
		UW->SetRenderOpacity(1.f);
	}
	WidgetComponent->RequestRedraw();
	if (WidgetComponent->WasRecentlyRendered(0.2f)) {
		WidgetComponent->RequestRedraw();
	}
}

void AVRWidgetActor::SetVRWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	WidgetComponent->SetWidgetClass(WidgetClass);
}

void AVRWidgetActor::ShowWidget()
{
	if (UUserWidget* widget = Cast<UUserWidget>(WidgetComponent->GetWidget()))
	{
		widget->SetVisibility(ESlateVisibility::Visible);
	}
	WidgetComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	SetActorEnableCollision(true);
}

void AVRWidgetActor::HideWidget()
{
	if (WidgetComponent) {
		if (UUserWidget* widget = Cast<UUserWidget>(WidgetComponent->GetWidget())) { widget->SetVisibility(ESlateVisibility::Collapsed); }
		WidgetComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
		SetActorEnableCollision(false);
	}
}

void AVRWidgetActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC && PC->PlayerCameraManager)
	{
		CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
		WidgetLocation = WidgetComponent->GetComponentLocation();
		LookAtRotation = (CameraLocation - WidgetLocation).Rotation();
		LookAtRotation.Roll = 0.f;
		//LookAtRotation.Yaw = 0.0f;
		//GEngine->AddOnScreenDebugMessage(8,5, FColor::Red,TEXT("MEnu Location:") + WidgetLocation.ToString());


		WidgetComponent->SetWorldRotation(LookAtRotation);

	}

	if (UIManager::GetInstance()->ButtonSates.bIsShortcutToolBar == true)
		UIManager::GetInstance()->ToolbarLocation(EMenusVR::ShortcutToolbar);
}
