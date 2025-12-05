#include "ADevicesHandler.h"
#include "Engine/World.h"
#include "Engine/LocalPlayer.h" // For GetLocalPlayer()
AADevicesHandler::AADevicesHandler()
{
    MappingContext = CreateDefaultSubobject<UInputMappingContext>(TEXT("MappingContext"));
}

void AADevicesHandler::BeginPlay()
{
    Super::BeginPlay();  
    RegisterMappingContext();
}

void AADevicesHandler::RegisterMappingContext()
{
    PlayerController = GetWorld()->GetFirstPlayerController();
    
        if (PlayerController && PlayerController->GetLocalPlayer())
        {
            if (UEnhancedInputLocalPlayerSubsystem* Subsystem = PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
            {
                Subsystem->AddMappingContext(MappingContext, 1);
            }
        }  
}


