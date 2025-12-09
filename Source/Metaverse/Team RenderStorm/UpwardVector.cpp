#include "UpwardVector.h"


AUpwardVector::AUpwardVector()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set Niagara beam asset
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysAsset(
		TEXT("/Game/VFX/LockLine/UpwardVector.UpwardVector"));
	if (BeamSysAsset.Succeeded())
	{
		BeamSystem = BeamSysAsset.Object; 
	}

}


