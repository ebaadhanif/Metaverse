#include "PCGContent.h"

APCGContent::APCGContent()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APCGContent::BeginPlay()
{
    Super::BeginPlay();
}

void APCGContent::ToggleVisibility(bool bVisible) {
}


