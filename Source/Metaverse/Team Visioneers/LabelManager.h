// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "Components/WidgetComponent.h"
//#include "EntityBase.h"
class AEntityBase;
class LabelManager
{
public:

	float MinScaleFactor = 0.5f;
	float MaxScaleFactor = 2.0f;
	float MaxDistance = 1000.0f;
	float MinDistance = 100.0f;
	static void AttachLabelToEntity(AEntityBase* entity);
	static void UpdateLabelFacingCamera(class AEntityBase* entity, const FVector& CameraLoacation);
	static void RemoveLabelFromEntity(AEntityBase* entity);
	//static void                                                       (class AEntityBase* entity, float ScaleMultiplier);
	//static void UpdateWidgetScale(const FVector& CameraLocation);
	//static float CalculateDistanceToCamera(const FVector& CameraLocation);
	/*void ShowHideLabel();
	*/
	//static void UpadteLabelScaleBasedOnDistance(class AEntityBase* entity);

};


