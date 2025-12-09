#include "HookedStatePawn.h"
#include "HtcVIVEInputHandler.h"
#include "AVajroInputHandler.h"
#include "AKeyboardInputHandler.h"
#include "Components/CapsuleComponent.h"


AHookedStatePawn::AHookedStatePawn()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AHookedStatePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHookedStatePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



