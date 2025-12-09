// Class Added by Ebaad, This class is the Entry Point of game and deals with assigning default pawn hud controller etc. stuff
#include "MetaverseGameModeBase.h"
#include "FreeCameraPawn.h"
#include "MetaverseHUD.h"
#include"ISRPawn.h"
#include"ISRHUD.h"


AMetaverseGameModeBase::AMetaverseGameModeBase()
{
	DefaultPawnClass = AFreeCameraPawn::StaticClass();
	HUDClass = AMetaverseHUD::StaticClass();
	/*DefaultPawnClass = AISRPawn::StaticClass();
	HUDClass = AISRHUD::StaticClass();*/
}

//Function to make mouse curson active durng game play, by default unreal engine hides the cursor  when game is played 
void AMetaverseGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (PC)
	{
		PC->bShowMouseCursor = true; 
		PC->SetInputMode(FInputModeGameAndUI());
	}
}