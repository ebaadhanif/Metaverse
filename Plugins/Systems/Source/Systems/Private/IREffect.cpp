// Fill out your copyright notice in the Description page of Project Settings.


#include "IREffect.h"

IREffect::IREffect()
{
}

IREffect::~IREffect()
{
}

void IREffect::Initialize(AActor* actor)
{
}

void IREffect::Initialize(AActor* actor, TArray<float> fovArr, float fPlane, float nPlane, float blurValue, FVector pos, FRotator rot)
{

}

void IREffect::SwitchIRMode(int effect)
{
	if(!IsValid(IRMaterialInstanceTest)) CreateIRMaterialInstance();
	if (effect == -1)
	{
		PostProcessSettings.AddBlendable(IRMaterialInstanceTest, 0);
	}
	else
	{
		IRMaterialInstanceTest->SetScalarParameterValue("IRSwitch", effect);
		PostProcessSettings.AddBlendable(IRMaterialInstanceTest, 1);
	}
	float val;
	IRMaterialInstanceTest->GetScalarParameterValue(FName("IRSwitch"), val);
	UE_LOG(LogTemp, Warning, TEXT("IRSwitch Value = %f "), val);
}

void IREffect::IncGain()
{
	gainLevel += gainLevel + 0.1;
	gainLevel = FMath::Clamp(gainLevel, 0, 2.0f);
	PostProcessSettings.bOverride_ColorGain = true;
	PostProcessSettings.ColorContrast = FVector4(gainLevel,gainLevel,gainLevel,1.f);
	PostProcessSettings.ColorGamma = FVector4(1.f/ gainLevel, 1.f / gainLevel, 1.f / gainLevel,1.f);
}

void IREffect::DecGain()
{
	gainLevel += gainLevel - 0.1;
	gainLevel = FMath::Clamp(gainLevel, 0, 2.0f);
	PostProcessSettings.bOverride_ColorGain = true;
	PostProcessSettings.ColorContrast = FVector4(gainLevel, gainLevel, gainLevel, 1.f);
	PostProcessSettings.ColorGamma = FVector4(1.f / gainLevel, 1.f / gainLevel, 1.f / gainLevel, 1.f);
}


