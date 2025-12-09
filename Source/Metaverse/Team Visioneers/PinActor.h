// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AKeyboardInputHandler.h"
#include <Components/TextRenderComponent.h>
#include "PinActor.generated.h"

class UCesiumGlobeAnchorComponent;
class UStaticMeshComponent;
class UWidgetComponent;
class UUserWidget;

UCLASS()
class METAVERSE_API APinActor : public AActor
{
	GENERATED_BODY()

public:
	double DesiredOffSet = 2000.0;
	bool IsInRadius = false;

	void InitializePin(double Latitude, double Longitude, double elevation, const FString& LabelText, UClass* LabelWidgetClass, const FString& MColour, const FString& MCategory, const FString& MTextColour);

	FVector MeshSize = FVector(10000.f);
	APinActor();
	FVector SetSize(FVector NewMeshSize);
	void setPinRotation();
	double GetHorizontolDistanceFromCamera();
	double GetCircleRadius();

	UPROPERTY(BlueprintReadWrite) FString Category;
	UPROPERTY(BlueprintReadWrite) double Distance = 0.f;
	UPROPERTY(BlueprintReadWrite) double HeightOfCamera = 0.f;
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere)
	UUserWidget* UserWidget = nullptr;

	UStaticMeshComponent* PinMesh;
	UStaticMesh* RingMesh;

	UPROPERTY(VisibleAnywhere)
	UCesiumGlobeAnchorComponent* GlobeAnchor;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* LabelWidget;

	UPROPERTY(VisibleAnywhere)
	UTextRenderComponent* LabelTextRender;

	UPROPERTY(VisibleAnywhere)
	UWidgetComponent* LabelIndiaWidget;

	UPROPERTY()
	APlayerCameraManager* CameraManager = nullptr;


	//UPROPERTY()
	//FLinearColor Colour = FLinearColor(1,1,1);


	UPROPERTY()
	FColor Colour = FColor::FromHex(TEXT("#FFFFFF"));



	//UPROPERTY()
	//FLinearColor TextColour = FLinearColor(1,1,1);
	UPROPERTY()
	FColor TextColour = FColor::FromHex(TEXT("#FFFFFF"));

	UPROPERTY()
	UMaterialInterface* PinMeshMaterial = nullptr;
	UPROPERTY()
	UMaterialInterface* TextMaterial = nullptr;
	UPROPERTY()
	UMaterialInstanceDynamic* PinMeshDynamicInstanceMaterial = nullptr;


	FString abbr;

	float FrameTime = 0;
	FVector cachedCameraLocation;
	FVector cachedActorLocation;
	FRotator cachedCameraRotation;

};
