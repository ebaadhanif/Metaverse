#include "PinActor.h"
#include "CesiumGeoreference.h"
#include "CesiumGlobeAnchorComponent.h"
#include "PinLabelWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "ScalingManager.h"
#include "DisplayManager.h"
#include "Kismet/GameplayStatics.h"
#include <Kismet/KismetMathLibrary.h>
#include "CesiumSampleHeightMostDetailedAsyncAction.h"
#include "CesiumSampleHeightResult.h"
#include "Engine/TextureRenderTarget2D.h"


APinActor::APinActor()
{
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClass(TEXT("/Game/Blueprints/WBP_PakPinLabel"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Materials/LandMarks/PinPoint.PinPoint"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRingAsset(TEXT("/Game/Materials/LockLine/Ring.Ring"));
	PinMeshMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/LandMarks/PinPointMaterial.PinPointMaterial"));
	TextMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/LandMarks/TextMaterial.TextMaterial"));
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	PinMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PinMesh"));
	RingMesh = MeshRingAsset.Object;

	PinMesh->SetupAttachment(RootComponent);
	if (MeshAsset.Succeeded()) {
		PinMesh->SetStaticMesh(MeshAsset.Object);
		//PinMesh->SetWorldScale3D(FVector(100000.f));
	}

	GlobeAnchor = CreateDefaultSubobject<UCesiumGlobeAnchorComponent>(TEXT("GlobeAnchor"));
	//LabelWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PakLabelWidget"));

	//Attach To Root
	//LabelWidget->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	//Attach to Pin
	//LabelWidget->SetupAttachment(PinMesh);
	//LabelWidget->SetupAttachment(PinMesh);
	MeshSize = SetSize(MeshSize);
	PinMesh->SetWorldScale3D(MeshSize);

	//if (WidgetClass.Succeeded()) {
	//	//LabelWidget->SetWidgetClass(WidgetClass.Class);
	//	LabelWidget->SetTwoSided(true);
	//}
	CameraManager = nullptr;

	LabelTextRender = CreateDefaultSubobject<UTextRenderComponent>(TEXT("LabelTextRender"));
	LabelTextRender->SetupAttachment(PinMesh);
	LabelTextRender->SetHorizontalAlignment(EHTA_Center);
	LabelTextRender->SetVerticalAlignment(EVRTA_TextCenter);
	LabelTextRender->SetWorldSize(1.75f);
	LabelTextRender->SetTextRenderColor(FColor::White);
	LabelTextRender->SetRelativeLocation(FVector(0.f,0.f,3.5f));
	LabelTextRender->SetMaterial(0, TextMaterial);

}

FVector APinActor::SetSize(const FVector NewMeshSize)
{
	MeshSize = NewMeshSize;
	return MeshSize;
}


void APinActor::InitializePin(double Longitude, double Latitude, double elevation, const FString& LabelText, UClass* LabelWidgetClass, const FString& MColour, const FString& MCategory, const FString& MTextColour)
{
	this->Category = MCategory;
	//LabelWidget->SetWidgetClass(LabelWidgetClass);
	abbr = LabelText;
	FVector PinMeshSize = SetSize(FVector(10000.0f));
	PinMesh->SetWorldScale3D(PinMeshSize);
	PinMeshDynamicInstanceMaterial = UMaterialInstanceDynamic::Create(PinMeshMaterial, nullptr);
	Colour = FColor::FromHex(TEXT("#") + MColour);
	TextColour = FColor::FromHex(TEXT("#") + MTextColour);
	//if (MColour.Contains("Green"))
	//	Colour = FLinearColor(0.258414, 0.682292, 0.292013);
	//else if((MColour.Contains("Blue")))
	//	Colour = FLinearColor(0.045058, 0.292353, 0.786458);
	//else if((MColour.Contains("Red")))
	//	Colour = FLinearColor(0.802083, 0.263016, 0.215086);
	//else if((MColour.Contains("Others")) || (MColour.Contains("Yellow")))
	//	Colour = FLinearColor(0.744792, 0.744792, 0.290934);


	//if (MTextColour.Contains("Green"))
	//	TextColour = FLinearColor(0.258414, 0.682292, 0.292013);
	//else if((MTextColour.Contains("Blue")))
	//	TextColour = FLinearColor(0.045058, 0.292353, 0.786458);
	//else if((MTextColour.Contains("Red")))
	//	TextColour = FLinearColor(0.802083, 0.263016, 0.215086);
	//else if((MTextColour.Contains("Others")))
	//	TextColour = FLinearColor(0.744792, 0.744792, 0.290934);

	TextColour = FColor::FromHex(TEXT("#FFFFFF"));

	PinMeshDynamicInstanceMaterial->SetVectorParameterValue(FName("Color"), FLinearColor::FromSRGBColor(Colour));
	PinMesh->SetMaterial(0,PinMeshDynamicInstanceMaterial);

	if (GlobeAnchor) {
		double Height = GlobeAnchor->GetHeight();
		GlobeAnchor->MoveToLongitudeLatitudeHeight(FVector(Longitude, Latitude, elevation));
	}

	if (LabelTextRender)
	{
		LabelTextRender->SetText(FText::FromString(LabelText));
	}

	/*UserWidget = LabelWidget->GetUserWidgetObject();
	if (UserWidget) {
		if (UPinLabelWidget* MyLabelWidget = Cast<UPinLabelWidget>(UserWidget)) {
			MyLabelWidget->SetLabelText(FText::FromString(LabelText));
			MyLabelWidget->SetColorAndOpacity(FLinearColor::FromSRGBColor(TextColour));
			MyLabelWidget->InvalidateLayoutAndVolatility();
			LabelWidget->SetWidgetSpace(EWidgetSpace::World);
			FVector2D DesiredSize = MyLabelWidget->GetDesiredSize();
			LabelWidget->SetTwoSided(true);
			LabelWidget->SetRelativeLocation(FVector(0.f, 0.f, 3.5f));
			LabelWidget->SetPivot(FVector2D(0.5f, 0.5f));
			LabelWidget->SetDrawAtDesiredSize(false);
			LabelWidget->SetDrawSize(FVector2D(1024, 1024));
			FVector LabelWidgetSize = PinMeshSize / 89.9;
			LabelWidget->SetWorldScale3D(LabelWidgetSize);
			MyLabelWidget->SetPadding(FMargin(50.0f, 20.0f));
		}
	}*/
	this->SetActorHiddenInGame(false);
}


void APinActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (this->IsHidden())
		return;

	FrameTime += DeltaTime;
	if (!CameraManager) {
		CameraManager = ADisplayManager::GetInstance()->PC->PlayerCameraManager;
	}
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FVector LabelLocation = PinMesh->GetComponentLocation();
	FRotator CameraRotation = CameraManager->GetCameraRotation();

	if ((FrameTime > 0.25)&&((!CameraLocation.Equals(cachedCameraLocation, 0.01f))||(!CameraRotation.Equals(cachedCameraRotation, 0.01f))))
	{
		if (CameraManager && LabelWidget && PinMesh) {
			cachedCameraLocation = CameraLocation;
			cachedActorLocation = LabelLocation;
			cachedCameraRotation = CameraRotation;
			setPinRotation();
		}
		FVector PinMeshSize = SetSize(FVector(AScalingManager::GetInstance()->ScaleActorBasedOnDistance(this, EActorType::BaseMarker, ADisplayManager::GetInstance()->CameraLocation)));
		PinMesh->SetWorldScale3D(PinMeshSize * 75);
		FrameTime = 0.f;
	}


	double height = ADisplayManager::GetInstance()->HeightOfCamera;
	double DistanceAlongX = FMath::Abs(LabelLocation.X - CameraLocation.X);
	double DistanceAlongY = FMath::Abs(LabelLocation.Y - CameraLocation.Y);


	HeightOfCamera = FVector::Dist(FVector(0, 0, CameraLocation.Z), FVector(0, 0, LabelLocation.Z));
//	GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Green, FString::Printf(TEXT("Distance=%.3f Height=%.3f"),Distance, HeightOfCamera));
	//if ((Distance > (Height*4)))
	//{
	//	this->SetActorHiddenInGame(true);
	//}
	//else {
	//	this->SetActorHiddenInGame(false);
	//}
	
}


void APinActor::BeginPlay()
{
	Super::BeginPlay();


	if (!CameraManager) {
		CameraManager = ADisplayManager::GetInstance()->PC->PlayerCameraManager;
	}
	setPinRotation();

}

void APinActor::setPinRotation() {
	FVector CameraLocation = CameraManager->GetCameraLocation();
	float CameraYaw = CameraManager->GetCameraRotation().Yaw;
	FRotator CameraRotation = CameraManager->GetCameraRotation();
	FVector LabelLocation = PinMesh->GetComponentLocation();

	FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(LabelLocation, CameraLocation);
	FRotator LookAtRotCamera = FRotator(LookAtRot.Pitch, CameraRotation.Yaw + 180, 0);

	//LookAtRot.Pitch = 90.f;
	//LookAtRot.Yaw = 0.f;
	LabelTextRender->SetWorldRotation(LookAtRotCamera);
	PinMesh->SetWorldRotation(LookAtRotCamera);
}


double APinActor::GetHorizontolDistanceFromCamera() {
	if (!CameraManager) {
		CameraManager = ADisplayManager::GetInstance()->PC->PlayerCameraManager;
	}
	FVector CameraLocation = CameraManager->GetCameraLocation();
	FVector LabelLocation = PinMesh->GetComponentLocation();
	Distance = FVector::Dist(FVector(CameraLocation.X, CameraLocation.Y, 0), FVector(LabelLocation.X, LabelLocation.Y, 0));
	return Distance;
}
