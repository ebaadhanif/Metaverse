#include "NiagaraLockLineActor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include <Metaverse/Team Visioneers/DisplayManager.h>

ANiagaraLockLineActor::ANiagaraLockLineActor()
{
    PrimaryActorTick.bCanEverTick = true;

    if (ForceType == EForceType::FRIENDLY)
    {
        static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysAsset(TEXT("/Game/VFX/LockLine/NS_LockBeam.NS_LockBeam"));
        if (BeamSysAsset.Succeeded())
        {
            BeamSystem = BeamSysAsset.Object;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load Beam Niagara System"));
        }
    }
    else {
        static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BeamSysRedAsset(TEXT("/Game/VFX/LockLine/NS_LockBeam_Red.NS_LockBeam_Red"));
        if (BeamSysRedAsset.Succeeded())
        {
            BeamSystem = BeamSysRedAsset.Object;
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("Failed to load Beam Niagara System"));
        }

    }


}

void ANiagaraLockLineActor::BeginPlay()
{
    Super::BeginPlay();

    if (!BeamSystem)
    {
        UE_LOG(LogTemp, Error, TEXT("BeamSystem not assigned!"));
        return;
    }

    BeamComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        BeamSystem,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        FVector(1.0f),
        true,
        true,
        ENCPoolMethod::None,
        true
    );
    BeamComp->SetCullDistance(5000000);

}

void ANiagaraLockLineActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

        if (!Source || !Destination || !BeamComp) return;

        FVector Start = Source->GetActorLocation();
        FVector End = Destination->GetActorLocation();


        const FVector ActorPosition = GetActorLocation();
        const FVector CameraPosition = ADisplayManager::GetInstance()->CameraLocation;


        float DistanceFromSource = FVector::Dist(Start, CameraPosition);
        float DistanceFromDestination = FVector::Dist(End, CameraPosition);

        float ActualDistance = FMath::Min(DistanceFromSource, DistanceFromDestination);

        const float camZ = CameraPosition.Z;
        const float zMid = 0.5f * (Start.Z + End.Z);
        const float zDist = FMath::Abs(camZ - zMid);
        const FVector midpoint = (ActorPosition + CameraPosition) * 0.5f;
        const float height = ADisplayManager::GetInstance()->HeightOfCamera;
        const float Distance = FVector::Dist(midpoint, CameraPosition);
        float ScaleFactor = 0.f;
        ScaleFactor = FMath::Clamp((ActualDistance / 400.f), 100.f, 5000000.0f);

        float stripeGap = FMath::Lerp(100, 5, FMath::Clamp((ActualDistance) / (10000000), 0.f, 1.f));
        float stripeWidth = FMath::Lerp(3000, 1000000, FMath::Clamp((ActualDistance) / (10000000), 0.f, 1.f));
        float speed = FMath::Lerp(15000, 1000000, FMath::Clamp((ActualDistance) / (15000000), 0.f, 1.f));
        // const float speed = FMath::GetMappedRangeValueClamped(FVector2D(10000, 10000000), FVector2D(-0.01, -0.1), Distance);

        BeamComp->SetVectorParameter(FName("BeamStart"), Start);
        BeamComp->SetVectorParameter(FName("BeamEnd"), End);
        BeamComp->SetFloatParameter(FName("BeamWidth"), ScaleFactor);
        BeamComp->SetFloatParameter(FName("StripeGaps"), stripeGap);
        BeamComp->SetFloatParameter(FName("Speed"), speed);
        BeamComp->SetFloatParameter(FName("BeamLength"), (End - Start).Size());
        BeamComp->SetFloatParameter(FName("StripeWidth"), stripeWidth);
    
}

void ANiagaraLockLineActor::EndPlay(const EEndPlayReason::Type EEndPlayReason)
{
    if (BeamComp)
    {
        BeamComp->DeactivateImmediate();
    }
}



void ANiagaraLockLineActor::SetJetEndpoints(AActor* InSource, AActor* InDestination)
{
    if (!InSource || !InDestination || !BeamComp) return;

    if (InSource && InDestination) {
        Source = InSource;
        Destination = InDestination;
    }
}


void ANiagaraLockLineActor::setForceType(EForceType force)
{
    this->ForceType = force;
}

