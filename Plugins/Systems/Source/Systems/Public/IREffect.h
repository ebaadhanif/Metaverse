// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CameraChannel.h"
/**
 *
 */

enum  IREffectEnum
{
	None = -1,
	WH = 0,
	BH = 1
};

class SYSTEMS_API IREffect :public UCameraChannel
{

private:

	
	IREffectEnum currentIREffect;
	float gainLevel;

public:
	IREffect();
	~IREffect();


	virtual void Initialize(AActor* actor) override;
	virtual void Initialize(AActor* actor, TArray<float> fovArr, float fPlane, float nPlane, float blurValue, FVector pos, FRotator rot) override;
	void SwitchIRMode(int effect);
	void IncGain();
	void DecGain();
private:

};
