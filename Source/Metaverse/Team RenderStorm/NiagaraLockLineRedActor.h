#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <AppConstEnumStruct.h>
#include "NiagaraLockLineRedActor.generated.h"


class UNiagaraSystem;
class UNiagaraComponent;
class AActor;

UCLASS()
class METAVERSE_API ANiagaraLockLineRedActor : public AActor
{
    GENERATED_BODY()

public:
    ANiagaraLockLineRedActor();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void EndPlay(const EEndPlayReason::Type EEndPlayReason) override;

    UFUNCTION(BlueprintCallable, Category = "LockLine")
    void SetJetEndpoints(AActor* InSource, AActor* InDestination);
    void setForceType(EForceType force);

    UPROPERTY()
    UNiagaraComponent* BeamComp = nullptr;

protected:
    UPROPERTY(EditAnywhere, Category = "Niagara")
    UNiagaraSystem* BeamSystem = nullptr;

    UPROPERTY()
    float beamWidth = 1000;

    UPROPERTY()
    float FrameTime = 0.f;

    UPROPERTY()
    AActor* Source;

    UPROPERTY()
    AActor* Destination;

    EForceType ForceType = EForceType::FRIENDLY;
};
