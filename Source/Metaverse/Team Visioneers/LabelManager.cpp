// Fill out your copyright notice in the Description page of Project Settings.

#include "LabelManager.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HorizontalBox.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "Math/Color.h"
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "../Team SimBridge/EntityBase.h"
#include "GameFramework/PlayerController.h"
#include <Components/RichTextBlock.h>
#include "FreeCameraPawn.h"

void LabelManager::AttachLabelToEntity(AEntityBase* entity)
{
	if (!entity) return;

	UWidgetComponent* WidgetComp = NewObject<UWidgetComponent>(entity);
	if (!WidgetComp) return;
	WidgetComp->RegisterComponent();
	WidgetComp->AttachToComponent(entity->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
	WidgetComp->SetWidgetSpace(EWidgetSpace::World);
	//WidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	WidgetComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	WidgetComp->SetMobility(EComponentMobility::Movable);

	FVector2D BaseSize(200.f, 50.f);
	WidgetComp->SetDrawSize(BaseSize);
	UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/Blueprints/WBP_LabelBackground.WBP_LabelBackground_C"));
	if (WidgetClass)
	{
		WidgetComp->SetWidgetClass(WidgetClass);
		if (UUserWidget* UserWidget = WidgetComp->GetUserWidgetObject())
		{
			UBorder* BackgroundBorder = Cast<UBorder>(UserWidget->GetWidgetFromName(TEXT("BackgroundBorder")));
			UTextBlock* TextBlock = Cast<UTextBlock>(UserWidget->GetWidgetFromName(TEXT("CallSignText")));
			if (TextBlock)
			{
				entity->TextBlock = TextBlock;
				FString CallSign = entity->GetCallSign();
				TextBlock->SetText(FText::FromString(CallSign));
				TextBlock->SetColorAndOpacity(FSlateColor(FLinearColor::White));
			}
			if (BackgroundBorder)
			{
				EForceType ForceType = entity->GetForceType();
				FLinearColor BackgroundColor;
				switch (ForceType)
				{
				case EForceType::FRIENDLY:
					BackgroundColor = FLinearColor(0.f, 0.f, 1.f);
					break;
				case EForceType::OPPOSING:
					BackgroundColor = FLinearColor(1.f, 0.f, 0.f);
					break;
				case EForceType::NEUTRAL:					
					BackgroundColor = FLinearColor(0.f, 1.f, 0.f);
					break;
				case EForceType::OTHERS:
					BackgroundColor = FLinearColor(1.f, 1.f, 0.f);
					break;
				default:
					BackgroundColor = FLinearColor::White;
				}
				BackgroundBorder->SetBrushColor(BackgroundColor);
			}
		}
	}
	FVector2D BackgroundSize = WidgetComp->GetDrawSize();
	WidgetComp->SetDrawSize(FVector2D(BackgroundSize.X, BackgroundSize.Y));
	//FVector Origin, Extent;
	//entity->GetActorBounds(true, Origin, Extent);
	//FVector LabelOffSet = FVector(0.f, 0.f, Extent.Z + 50.f);
	//WidgetComp->SetRelativeLocation(LabelOffSet);

	//WidgetComp->SetDrawAtDesiredSize(true);
	WidgetComp->SetCullDistance(0.f);
	WidgetComp->bAllowCullDistanceVolume = false;
	WidgetComp->SetVisibility(true);
	WidgetComp->SetHiddenInGame(false);

	entity->WidgetComponent = WidgetComp;
	//UpadteLabelScaleBasedOnDistance(entity, WidgetComp);
}

void LabelManager::RemoveLabelFromEntity(AEntityBase* entity)
{
	if (!entity) return;
	entity->WidgetComponent->DestroyComponent();
	entity->WidgetComponent->ReleaseResources();
	entity->WidgetComponent = nullptr;
}

void LabelManager::UpdateLabelFacingCamera(AEntityBase* entity, const FVector& CameraLocation)
{
	if (!entity || !entity->WidgetComponent) return;
	FVector LabelLoc = entity->WidgetComponent->GetComponentLocation();
	FVector CameraDirection = CameraLocation - LabelLoc;
	CameraDirection.Z = 0;
	if (!CameraDirection.IsNearlyZero())
	{
		FRotator FaceRotation = CameraDirection.Rotation();
		entity->WidgetComponent->SetWorldRotation(FaceRotation);
	}

}

/*
void LabelManager::ScaleLabel(AEntityBase* entity, float ScaleMultiplier)
{
	if (!entity || !entity->WidgetComponent) return;
	FVector2D BackgroundSize = entity->WidgetComponent->GetDrawSize();
	entity->WidgetComponent->SetDrawSize(FVector2D(BackgroundSize.X * ScaleMultiplier, BackgroundSize.Y * ScaleMultiplier));
}

void LabelManager::UpadteLabelScaleBasedOnDistance(AEntityBase* entity)
{
	UWidgetComponent* WidgetComp = entity->WidgetComponent;

	if (!entity || !WidgetComp) return;

	APlayerController* PC = UGameplayStatics::GetPlayerController(entity->GetWorld(), 0);

	if (!PC || !PC->PlayerCameraManager) return;

	FVector CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
	FVector EntityLocation = entity->GetWorldLocation();
	float Distance = FVector::Dist(CameraLocation, EntityLocation);
	float ScaleFactor = FMath::Clamp(100 , 1.0f, 100.0f);
	FVector2D BaseSize(200.0f, 50.0f);
	FVector2D NewSize = BaseSize * ScaleFactor;
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Black, FString::FromInt(ScaleFactor));
	WidgetComp->SetDrawSize(NewSize);
	for (USceneComponent* children : WidgetComp->GetAttachChildren()) {
		children->SetRelativeScale3D(children->GetRelativeScale3D() * ScaleFactor);
	}
}
*/
//void LabelManager::UpdateWidgetScale(const FVector& CameraLocation)
//{
//	if (!WidgetComp)
//	{
//		return;
//	}
//	float Distance = CalculateDistanceToCamera(CameraLocation);
//	Distance = FMath::Clamp(Distance, MinDistance, MaxDistance);
//	float ScaleFactor = FMath::Lerp(MaxScaleFactor, MinScaleFactor, (Distance - MinDistance) / (MaxDistance - MinDistance));
//	WidgetComp->SetWorldScale3D(FVector(ScaleFactor));
//}
//float LabelManager::CalculateDistanceToCamera(const FVector& CameraLocation)
//{
//	if (!WidgetComp)
//	{
//		return 0.0f;
//	}
//	FVector WidgetLocation = WidgetComp->GetComponentLocation();
//	return FVector::Dist(WidgetLocation, CameraLocation);
//}
//void LabelManager::ShowHideLabel()
//{
//	bool setVisible =false;
//	if (setVisible)
//	{	
//	}
//}
