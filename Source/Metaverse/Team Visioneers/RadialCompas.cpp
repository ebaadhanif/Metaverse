#include "RadialCompas.h"
#include <Kismet/GameplayStatics.h>
#include "Math/RotationMatrix.h"

ARadialCompas::ARadialCompas()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	static const TCHAR* DirectionNames[40] = {
		TEXT("N"), TEXT("'"), TEXT("'") , TEXT("'") , TEXT("'"), 
		TEXT("NE"), TEXT("'"), TEXT("'") , TEXT("'") , TEXT("'"), 
		TEXT("E"), TEXT("'"), TEXT("'") , TEXT("'") , TEXT("'"),
		TEXT("SE"), TEXT("'"), TEXT("'") , TEXT("'") , TEXT("'"),
		TEXT("S"), TEXT("'"), TEXT("'") , TEXT("'") , TEXT("'"), 
		TEXT("SW"), TEXT("'"), TEXT("'") , TEXT("'") , TEXT("'"),
		TEXT("W"), TEXT("'"), TEXT("'") , TEXT("'") , TEXT("'"),
		TEXT("NW"), TEXT("'"), TEXT("'") , TEXT("'") , TEXT("'")
	};

	DirectionsText.Reserve(40);

	CompasTextMaterial = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/RadialCompas/CompasTextMaterial.CompasTextMaterial"));

	for (int32 i = 0; i < 40; i++) {
		FString CompName = FString::Printf(TEXT("DirText_%d"), i);
		UTextRenderComponent* TextComp = CreateDefaultSubobject<UTextRenderComponent>(*CompName);

		TextComp->SetupAttachment(Root);
		TextComp->SetText(FText::FromString(DirectionNames[i]));
		/*TextComp->SetHorizontalAlignment(EHTA_Center);
		TextComp->SetVerticalAlignment(EVRTA_TextCenter);*/
		TextComp->SetWorldSize(80.f);
		TextComp->SetWorldScale3D(FVector(0.25f));
		TextComp->SetMaterial(0, CompasTextMaterial);
		DirectionsText.Add(TextComp);
	}

}

void ARadialCompas::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(this, 0);

	if (PlayerController.IsValid()) {
		FRotator CamRot;
		FVector CamLoc;
		PlayerController->GetPlayerViewPoint(CamLoc, CamRot);

		NorthYaw = CamRot.Roll;

		float Distance = 160.0f;
		FVector Forword = CamRot.Vector();
		FVector Up = FVector::UpVector;

		FVector CompassLocation = CamLoc + Forword * Distance - Up * 50.0f;

		SetActorLocation(CompassLocation);
		SetActorRotation(FRotator(0.f, NorthYaw , 0.f));
	}

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FreeCamPawn = Cast<AFreeCameraPawn>(PlayerPawn);

	for (int32 i = 0; i < DirectionsText.Num(); ++i) {
		float BaseAngleDeg = i * 9.f;
		float AngleRad = FMath::DegreesToRadians(BaseAngleDeg);

		float X = FMath::Cos(AngleRad) * CompasRadius;
		float Y = FMath::Sin(AngleRad) * CompasRadius;
		float Z = Height;

		if (UTextRenderComponent* TextComp = DirectionsText[i]) {
			TextComp->SetRelativeLocation(FVector(X, Y, Z));

			FVector ToCenter = -FVector(X, Y, 0.f);
			FRotator LookRot = ToCenter.Rotation();
			TextComp->SetRelativeRotation(LookRot);
		}
	}
}

void ARadialCompas::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!PlayerController.IsValid())
		return;

	PlayerController->GetPlayerViewPoint(PlayerCamLoc, PlayerCamRot);
	float CurrentYaw = PlayerCamRot.Yaw;

	float RelativeYaw = CurrentYaw - NorthYaw;
	RelativeYaw = FRotator::NormalizeAxis(RelativeYaw);

	float CompassYaw = -RelativeYaw;

	JtacPawnLocation = FreeCamPawn->Camera->GetComponentLocation();
	JtacPawnRotation = FreeCamPawn->Camera->GetComponentRotation();
	
	SetActorLocation(JtacPawnLocation);
	SetActorRelativeRotation(FRotator(JtacPawnRotation.Pitch, 0.f , 0.f));
}
