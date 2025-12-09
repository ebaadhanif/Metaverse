#include "FPSDisplay.h"
#include "Slate/SceneViewport.h"
#include "Framework/Application/SlateApplication.h"
#include "Widgets/SWindow.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/GameMode.h"
#include "LoadingManager.h"
#include "Engine/Engine.h"


AFPSDisplay::AFPSDisplay()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSDisplay::BeginPlay()
{
	Super::BeginPlay();

}

void AFPSDisplay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ElapsedTime += DeltaTime;

	if (ElapsedTime > 1) {
		value = FMath::RoundToInt(1.0f / DeltaTime);
		FPS = FString::Printf(TEXT("FPS : %d"), value);
		ElapsedTime = 0;
	}

	//GEngine->AddOnScreenDebugMessage(1, 0.0, FColor::Green, FPS);

	UIManager::GetInstance()->UpdateFPSVR(value);
	UIManager::GetInstance()->UpdateFPS(value);
	//UUIManagerVR::GetInstance()->UpdateFPS(value);
}

FString AFPSDisplay::GetFPS() const
{
	return FPS;
}

