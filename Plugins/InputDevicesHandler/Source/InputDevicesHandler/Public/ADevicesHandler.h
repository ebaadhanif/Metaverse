//Class Written by Ebaad, This class Registers the input mapping context with UEnhancedInputLocalPlayerSubsystem,
// ensuring that the correct input configuration is used during gameplay.
// Also This class has two virtual function MapKeys and Create Input Action that any input device will impliment using input mapping context registered in this class

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "TimerManager.h"
#include "InputActionValue.h"
#include "ADevicesHandler.generated.h"
UCLASS()
class INPUTDEVICESHANDLER_API AADevicesHandler : public AActor
{
    GENERATED_BODY()
public:
    AADevicesHandler();
    virtual ~AADevicesHandler() = default;
    virtual void BeginPlay() override;
    void RegisterMappingContext();
    virtual void CreateInputActions() {};
    virtual void MapKeys() {};
    template <typename T>
    void BindActions(
        const UInputAction* ActionName,
        ETriggerEvent TriggerEventType,
        T* Object,
        void (T::* ClassFunction)(const FInputActionValue&))
    {
        if (UInputComponent* LocalInputComponent = PlayerController->InputComponent)
        {
            UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(LocalInputComponent);
            if (!EnhancedInputComponent)
            {
                UE_LOG(LogTemp, Error, TEXT("Unable to bind, Input Component not initialized"));
                return;
            }

            EnhancedInputComponent->BindAction(ActionName, TriggerEventType, Object, ClassFunction);
        }
    }

    APlayerController* PlayerController;
protected:
    UPROPERTY()
    UInputMappingContext* MappingContext;
};
