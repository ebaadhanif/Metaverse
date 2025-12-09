#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../AirbaseManager.h"
#include "../EntityListUI.h"
#include "ViewDropDown.h"
#include "Components/TextBlock.h"
#include "../VR_Menus/VRShortcutToolbar.h"
#include "MainMenu.h"
#include "Math/Vector2D.h"
#include "ListDropDown.h"
#include "TerrainManager.h"
#include "../../Public/AppConstEnumStruct.h"
#include "../../Team RenderStorm/TrailController.h"
#include "StatusBar.h"

class UMetaverseMode;
class ALoadingManager;
class AVRWidgetActor;
class UDWGXDrawingManager;
class ATrailController;
class EntityManager;
class AEntityBase;

/**
 *
 */

class METAVERSE_API UIManager 
{
	
public:
	//-------------SCREEN
	ALoadingManager* loadingManager = nullptr;
	TMap<EMenus, TObjectPtr<UUserWidget>> MenuWidgetMap;
	static UIManager* GetInstance();
	TMap<EMenus, TObjectPtr<UUserWidget>> InitializeScreenMenu();
	void RegisterMenuPath(EMenus MenuType, const TCHAR* ClassPath);
	void CreateMenu(EMenus MenuType);
	void HideMenu(EMenus MenuType);
	void ShowMenu(EMenus MenuType);
	void SetWorld(UWorld* world) { World = world; }
	void HidAllMenus();
	void UpdateFPS(int fps);
	UEntityListUI* GetEntityListPtr() { return EntityListUIWidget; }
	UListDropDown* GetListPtr() { return ListDropDownWidget;  }
	EMenus OpenedMenu = EMenus::None;
	UMetaverseMode* GetActiveMode() const { return ActiveMode; }
	TArray<TObjectPtr<UUserWidget>> OpenMenu;
	AFreeCameraPawn* FreeCamPawn = nullptr;
	void SetStateofScreen(EButtonsName button, bool Value);
	static void Toggle(UObject* WorldContextObject, UWidget* AnchorButton, UUserWidget* MenuInstance, float GapX = 0.4f, float GapY = 4.f);
	static FVector2D CalculateForwardMenuPosition(UObject* WorldContext, UWidget* Anchor, UUserWidget* Menu);
	void CloseAllOpenMenu();
	void InitScreenMenu();

	//-------------------VR
	TMap<EMenusVR, TWeakObjectPtr<AVRWidgetActor>> MenuWidgetMapVR;
	TMap<EMenusVR, TWeakObjectPtr<AVRWidgetActor>> InitializeVRMenu();	
	void RegisterMenuPathVR(EMenusVR MenuType, const TCHAR* ClassPath);
	void CreateMenuVR(EMenusVR MenuTypeVR);
	//void MenuLocation(EMenusVR MenuType);
	void ShowMenuVR(EMenusVR MenuTypeVR);
	void HideMenuVR(EMenusVR MenuTypeVR);
	void UpdateFPSVR(int fps);
	UPROPERTY()
	FButtonState ButtonSates;
	void SetState(EButtonsName button);
	EVisualsButtonStateVR EntityVisualStateVR = EVisualsButtonStateVR::Off;
	EMenusVR CurrentMenu = EMenusVR::MainMenu;
	UPROPERTY()
	TArray<EMenusVR> MenuHistory;
	FVector CameraLocation = FVector::ZeroVector;
	void SetSelectedEntity(AEntityBase* entity) { SelectedEntity = entity; }
	void ToolbarLocation(EMenusVR MenuType);
	void ShutDown();
	static void close();

private:
	UIManager();
	static UIManager* UIManagerInstance;
	bool isShadedVisible = false;
	bool isBorderVisibile = false;
	bool bUpdatingLocklineUI = false;
	float entityScaleValue = 1;
	UPROPERTY()
	ATrailController* trailController = nullptr;
	AVRWidgetActor* VRActor;
	AVRWidgetActor* ToolbarVRActor;
	APawn* PlayerPawn;
	UPROPERTY()
	AEntityBase* SelectedEntity;
	UFUNCTION()
	bool LoadModesFromConfig(const FString& ConfigFilePath, UObject* Outer);
	static bool Tick(float DeltaTime);
	static void StartTicker();
	static void StopTicker();
	static void Reposition();
	static FVector2D BottomLeftViewportPos(UWidget* Anchor);
	static FVector2D GetWidgetLocalSize(UWidget* w, UObject* WorldContext);
	static FVector2D GetButtonSize(UWidget* w);

	static TWeakObjectPtr<UObject> ActiveWorldContext;
	static TWeakObjectPtr<UUserWidget> ActiveMenu;
	static TWeakObjectPtr<UWidget> ActiveAnchor;
	static FVector2D ActiveGap;
	static FTSTicker::FDelegateHandle TickerHandle;
	static bool bTickerRunning;
	
protected:
	UWorld* World;
	int ZOrder = 0;

	UMainMenu* MainMenu=nullptr;
	UStatusBar* StatusBar = nullptr;
	UEntityListUI* EntityListUIWidget = nullptr;
	UListDropDown* ListDropDownWidget = nullptr;
	UViewDropDown* ViewDropDownWidget = nullptr;
	TSubclassOf<AVRWidgetActor> VRWidgetActorClass;
	UVRShortcutToolbar* Toolbar = nullptr;
	TMap<EMenus, TSoftClassPtr<UUserWidget>> WidgetClassMap;
	TMap<EMenusVR, TSubclassOf<UUserWidget>> WidgetClassMapVR;
	UMetaverseMode* ActiveMode = nullptr;


	~UIManager();
};
