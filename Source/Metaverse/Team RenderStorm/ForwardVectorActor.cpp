// ForwardVectorActor.cpp
#include "ForwardVectorActor.h"
#include "UObject/ConstructorHelpers.h"

AForwardVectorActor::AForwardVectorActor()
{
	// set the Niagara asset once; no need to spawn at runtime
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysAsset(
		TEXT("/Game/VFX/LockLine/ForwardVector.ForwardVector"));
	if (BeamSysAsset.Succeeded())
	{
		BeamSystem = BeamSysAsset.Object; // base will assign it to BeamComp in BeginPlay
	}

	// set the Niagara asset once; no need to spawn at runtime
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysAssetRed(
		TEXT("/Game/VFX/LockLine/ForwardVectorRed.ForwardVectorRed"));
	if (BeamSysAssetRed.Succeeded())
	{
		BeamSystemRed = BeamSysAssetRed.Object;
	}

	// set the Niagara asset once; no need to spawn at runtime
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysAssetOther(
		TEXT("/Game/VFX/LockLine/ForwardVectorOthers.ForwardVectorOthers"));
	if (BeamSysAssetOther.Succeeded())
	{
		BeamSystemOther = BeamSysAssetOther.Object;
	}


	// set the Niagara asset once; no need to spawn at runtime
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysAssetNeutral(
		TEXT("/Game/VFX/LockLine/ForwardVectorNeutral.ForwardVectorNeutral"));
	if (BeamSysAssetNeutral.Succeeded())
	{
		BeamSystemNeutral = BeamSysAssetNeutral.Object;
	}

}