// Fill out your copyright notice in the Description page of Project Settings.


#include "FileDropDown.h"
#include "UIManager.h"
#include "../VR_Menus/VRDrawings.h"
#include "DWGXDrawingManager.h"
#include "../Team RenderStorm/SplatMapping.h"
#include "TerrainManager.h"
#include <Metaverse/Team RenderStorm/ModeManager.h>

void UFileDropDown::NativeConstruct()
{
	if (LoadDrawingButton)
	{
		LoadDrawingButton->OnClicked.Clear();
		LoadDrawingButton->OnClicked.AddUniqueDynamic(this, &UFileDropDown::OnLoadDrawingButtonClick);
	}
	/*if (TerrainBorder) {
		TerrainBorder->OnCheckStateChanged.Clear();
		TerrainBorder->OnCheckStateChanged.AddUniqueDynamic(this, &UFileDropDown::OnTerrainBorderClicked);
	}*/
	if (RestartIGButton)
	{
		RestartIGButton->OnClicked.Clear();
		RestartIGButton->OnClicked.AddUniqueDynamic(this, &UFileDropDown::OnRestartButtonClick);
	}
	if (ExitButton)
	{
		ExitButton->OnClicked.Clear();
		ExitButton->OnClicked.AddUniqueDynamic(this, &UFileDropDown::OnExitButtonClick);
	}
	if (AModeManager::getInstance()->getActiveMode())
	{
		ApplyMode(AModeManager::getInstance()->getActiveMode());
	}
}

void UFileDropDown::ApplyMode(UMetaverseMode* Mode)
{
	if (LoadDrawingButton)
	{
		if (FButtonStateStruct* State = Mode->ButtonStates.Find(EButtonsName::LoadDrawing))
		{
			LoadDrawingButton->SetVisibility(State->Visibility);
		}
		else
		{
			LoadDrawingButton->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UFileDropDown::OnLoadDrawingButtonClick()
{
	ACesiumGeoreference* Goereference = ACesiumGeoreference::GetDefaultGeoreference(GetWorld());
	ACesium3DTileset* Tileset = Cast< ACesium3DTileset>(UGameplayStatics::GetActorOfClass(GetWorld(), ACesium3DTileset::StaticClass()));
	IShape::SetTileset(Tileset);
	IShape::SetGeoreference(Goereference);

	UDWGXDrawingManager::Get(GetWorld())->LoadDrawingConfig();
	UDWGXDrawingManager::Get(GetWorld())->LoadDrawingFromFileExplorer();
}

//void UFileDropDown::OnTerrainBorderClicked(bool isVisible) {
//	UIManager::GetInstance()->SetState(EButtonsName::ToggleBorderButtonEnum);
//}

void UFileDropDown::OnRestartButtonClick()
{
	APlayerController* playerController = GetOwningPlayer();
	FString CurrentLevel = GetWorld()->GetMapName();
	CurrentLevel.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*CurrentLevel));
}

void UFileDropDown::OnExitButtonClick()
{
	APlayerController* playerController = GetOwningPlayer();
	UKismetSystemLibrary::QuitGame(GetWorld(), playerController, EQuitPreference::Quit, true);
}

