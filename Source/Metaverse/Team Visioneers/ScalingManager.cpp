// Fill out your copyright notice in the Description page of Project Settings.


#include "ScalingManager.h"
#include <Metaverse/Team RenderStorm/ModeManager.h>

AScalingManager* AScalingManager::Instance = nullptr;

float AScalingManager::GetEntityScalingFactor()
{
    if (AModeManager::getInstance()->getActiveMode()->ButtonStates.Find(EButtonsName::Scaling)->FeatureActive)
    {
        scale = true;
        if (this == nullptr)
            return entityScaleMultiplier;
        return 1;
    }
    else {
        scale = false;
        return 1;
    }

}

float AScalingManager::GetEntityLabelScalingFactor()
{
    if (AModeManager::getInstance()->getActiveMode()->ButtonStates.Find(EButtonsName::Scaling)->FeatureActive)
    {
        if (this == nullptr)
            return entityLabelScaleMultiplier;
        return 1;
    }
    else {
        return 1;
    }
}

float AScalingManager::GetEntityLabelOffsetFactor()
{
    if (AModeManager::getInstance()->getActiveMode()->ButtonStates.Find(EButtonsName::Scaling)->FeatureActive)
    {
    if (this == nullptr)
        return entityLabelOffsetMultiplier;
    return 1;
    }
    else {
        return 1;
    }
}

void AScalingManager::SetEntityScalingFactor(Multiplier value)
{
    switch (value)
    {
    case Multiplier::Small:
        entityScaleMultiplier = 0.3;
        break;
    case Multiplier::Medium:
        entityScaleMultiplier = 0.45;
        break;
    case Multiplier::Large:
        entityScaleMultiplier = 0.6;
        break;
    default:
        break;
    }
}

void AScalingManager::SetEntityLabelScalingFactor(Multiplier value)
{
    switch (value)
    {
    case Multiplier::Small:
        entityLabelScaleMultiplier = 0.5;
        break;
    case Multiplier::Medium:
        entityLabelScaleMultiplier = 1;
        break;
    case Multiplier::Large:
        entityLabelScaleMultiplier = 1.5;
        break;
    default:
        break;
    }
}

void AScalingManager::SetEntityLabelOffsetFactor(Multiplier value)
{
    switch (value)
    {
    case Multiplier::Small:
        entityLabelOffsetMultiplier = 0;
        break;
    case Multiplier::Medium:
        entityLabelOffsetMultiplier = 1;
        break;
    case Multiplier::Large:
        entityLabelOffsetMultiplier = 2;
        break;
    default:
        break;
    }
}

void AScalingManager::SetEntityScalingType(ScalingType value)
{
    scalingType = value;
}

// Sets default values
AScalingManager::AScalingManager()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;



}


// Called when the game starts or when spawned
void AScalingManager::BeginPlay()
{
    Super::BeginPlay();

	if (Instance == nullptr)
	{
		Instance = this;
	}
	GEngine->AddOnScreenDebugMessage(-1, 0.1, FColor::Green, "AScalingManager::BeginPlay");

    SetEntityScalingFactor(Multiplier::Small);
    SetEntityLabelScalingFactor(Multiplier::Medium);
    SetEntityLabelOffsetFactor(Multiplier::Medium);
    SetEntityScalingType(ScalingType::ExegeratedScale);

    if (AModeManager::getInstance()->getActiveMode()->ButtonStates.FindRef(EButtonsName::EntityLabels).FeatureActive)
    {
        isShowLabel = true;
    }
    else {
        isShowLabel = false;
    }

    if (AModeManager::getInstance()->getActiveMode()->ButtonStates.Find(EButtonsName::Scaling)->FeatureActive)
    {
        scale = true;
    }
    else {
        scale = false;
    }
}

// Called every frame
void AScalingManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //PC = GetWorld()->GetFirstPlayerController();

}

AScalingManager* AScalingManager::GetInstance()
{
    return Instance;
}


float AScalingManager::ScaleActorBasedOnDistance(AActor* Actor, EActorType ActorType, FVector& CameraPosition1)
{

    if ((this == nullptr) || !scale)
        return 1;

    FVector ActorPosition = Actor->GetActorLocation();
    float Distance = FVector::Dist(ActorPosition, CameraPosition1);
    float ScaleFactor = 1.0f;

    switch (ActorType)
    {
    case EActorType::EntityModel:
        switch (scalingType)
        {
        case ScalingType::ActualScale:
            ScaleFactor = 1;
            break;
        case ScalingType::ExegeratedScale:
            ScaleFactor = FMath::Clamp(((Distance / 10000.0f) * entityScaleMultiplier), 1.0f, 999999999);
            break;
        default:
            break;
        }       
        break;
    case EActorType::BaseMarker:
        ScaleFactor = FMath::Clamp((Distance / 10000.0f), Markers_Min_Scale, Markers_Max_Scale);
        break;
    case EActorType::EntityLabel:
        ScaleFactor = FMath::Clamp(((Distance / 10000.0f) * entityLabelScaleMultiplier), 1.0f, 999999999) * 3;
        break;
    default:
        break;
    }

    return ScaleFactor;
}

