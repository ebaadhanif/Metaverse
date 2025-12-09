// Fill out your copyright notice in the Description page of Project Settings.


#include "UIManager.h"
#include "MetaverseMode.h"
#include "../DisplayManager.h"
#include "Kismet/GameplayStatics.h"
#include "DWGXDrawingManager.h"
#include "Misc/Paths.h"
#include "XmlFile.h"   
#include "Misc/FileHelper.h"
#include "TerrainManager.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Containers/Ticker.h"
#include <Kismet/KismetMathLibrary.h>
#include "HeadMountedDisplayFunctionLibrary.h"
#include "../Public/LoadingManager.h"
#include "../VR_Menus/VRWidgetActor.h"
#include "HanTracking.h"
#include "../../Team RenderStorm/STerrainSettingsDialog.h"
#include "../../Team RenderStorm/RibbonMeshActor.h"
#include "../../Team RenderStorm/VerticalRibbonMeshActor.h"
#include "../../Team RenderStorm/GroundVectorActor.h"
#include "../../Team RenderStorm/ForwardVectorActor.h"
#include "../../Team RenderStorm/CoveragesManager.h"
#include "../../Team RenderStorm/ModeManager.h"
#include "../Team RenderStorm/SplatMapping.h"
#include "../../Team SimBridge/EntityManager.h"
#include "../../Team SimBridge/EntityBase.h"
#include "../../Team Visioneers/ScalingManager.h"

UIManager* UIManager::UIManagerInstance = nullptr;

TWeakObjectPtr<UObject> UIManager::ActiveWorldContext;
TWeakObjectPtr<UUserWidget> UIManager::ActiveMenu;
TWeakObjectPtr<UWidget> UIManager::ActiveAnchor;
FVector2D UIManager::ActiveGap = FVector2D(0.f, 4.f);
FTSTicker::FDelegateHandle UIManager::TickerHandle;
bool UIManager::bTickerRunning = false;

UIManager::UIManager()
{
}

void UIManager::RegisterMenuPath(EMenus MenuType, const TCHAR* ClassPath)
{
	if (UClass* cls = LoadClass<UUserWidget>(nullptr, ClassPath))
	{
		WidgetClassMap.Add(MenuType, cls);
		loadingManager->WidgetClassMap = WidgetClassMap;
	}
}

void UIManager::RegisterMenuPathVR(EMenusVR MenuType, const TCHAR* ClassPath)
{
	int a = 0;
	if (UClass* cls = LoadClass<UUserWidget>(nullptr, ClassPath))
	{
		WidgetClassMapVR.Add(MenuType, cls);
		loadingManager->WidgetClassMapVR = WidgetClassMapVR;
	}
}

void UIManager::InitScreenMenu()
{
	//const FString ConfigPath = FPaths::Combine(FPaths::ProjectContentDir(), TEXT("Archive/ModesConfig.xml"));
	//if (!LoadModesFromConfig(ConfigPath, GetTransientPackage()))
	//{
	//	return;
	//}
	ActiveMode = AModeManager::getInstance()->getActiveMode();
	if (!ActiveMode)
	{
		return;
	}
	CreateMenu(EMenus::MainMenu);
	CreateMenu(EMenus::StatusBar);
	CreateMenu(EMenus::FileDropDown);
	CreateMenu(EMenus::ViewDropDown);
	CreateMenu(EMenus::SettingsDropDown);
	CreateMenu(EMenus::ObserverDropDown);
	CreateMenu(EMenus::HelpDropDown);
	CreateMenu(EMenus::EntityList);
	CreateMenu(EMenus::TrailDropDown);
	CreateMenu(EMenus::MarkersDropDown);
	CreateMenu(EMenus::EntityVisualsDropDown);
	CreateMenu(EMenus::ListDropDown);
	CreateMenu(EMenus::TerrainEditorDropDown);
	CreateMenu(EMenus::GraphicsDropDown);
	CreateMenu(EMenus::LocklinesDropDown);
	CreateMenu(EMenus::CoveragesDropDown);
	CreateMenu(EMenus::DrawingsDropDown);

	if (ActiveMode->bMenuVisible)
	{
		ShowMenu(EMenus::MainMenu);
	}
	else
	{
		HideMenu(EMenus::MainMenu);
	}

	if (ActiveMode->bStatusBarVisible)
	{
		ShowMenu(EMenus::StatusBar);
	}
	else {
		HideMenu(EMenus::StatusBar);
	}
}

TMap<EMenus, TObjectPtr<UUserWidget>> UIManager::InitializeScreenMenu()
{
	WidgetClassMap.Empty();
	MenuWidgetMap.Empty();
	RegisterMenuPath(EMenus::MainMenu, TEXT("/Game/Blueprints/UserInterface/WBP_MainMenu.WBP_MainMenu_C"));
	RegisterMenuPath(EMenus::FileDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_FileDropDown.WBP_FileDropDown_C"));
	RegisterMenuPath(EMenus::ViewDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_ViewDropDown.WBP_ViewDropDown_C"));
	RegisterMenuPath(EMenus::SettingsDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_SettingsDropDown.WBP_SettingsDropDown_C"));
	RegisterMenuPath(EMenus::ObserverDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_ObserverDropDown.WBP_ObserverDropDown_C"));
	RegisterMenuPath(EMenus::HelpDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_HelpDropDown.WBP_HelpDropDown_C"));
	RegisterMenuPath(EMenus::EntityList, TEXT("/Game/Blueprints/UserInterface/WBP_EntityListUI.WBP_EntityListUI_C"));
	RegisterMenuPath(EMenus::TrailDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_TrailsDropDown.WBP_TrailsDropDown_C"));
	RegisterMenuPath(EMenus::MarkersDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_MarkersDropDown.WBP_MarkersDropDown_C"));
	RegisterMenuPath(EMenus::EntityVisualsDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_EntityVisualsDropDown.WBP_EntityVisualsDropDown_C"));
	RegisterMenuPath(EMenus::ListDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_ListDropDown.WBP_ListDropDown_C"));
	RegisterMenuPath(EMenus::TerrainEditorDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_TerrainDropDown.WBP_TerrainDropDown_C"));
	RegisterMenuPath(EMenus::GraphicsDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_GraphicsDropDown.WBP_GraphicsDropDown_C"));
	RegisterMenuPath(EMenus::LocklinesDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_Locklines.WBP_Locklines_C"));
	RegisterMenuPath(EMenus::CoveragesDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_Coverages.WBP_Coverages_C"));
	RegisterMenuPath(EMenus::DrawingsDropDown, TEXT("/Game/Blueprints/UserInterface/WBP_DrawingsDropDown.WBP_DrawingsDropDown_C"));
	RegisterMenuPath(EMenus::StatusBar, TEXT("/Game/Blueprints/UserInterface/WBP_StatusBar.WBP_StatusBar_C"));

	InitScreenMenu();

	TObjectPtr<UUserWidget>* EntityListWeakPtr = MenuWidgetMap.Find(EMenus::EntityList);

	UUserWidget* EntityListWidget = EntityListWeakPtr->Get();
	if (EntityListWidget)
		EntityListUIWidget = Cast<UEntityListUI>(EntityListWidget);

	TObjectPtr<UUserWidget>* ListPtr = MenuWidgetMap.Find(EMenus::ListDropDown);
	UUserWidget* ListWidget = ListPtr->Get();
	if (ListWidget)
		ListDropDownWidget = Cast<UListDropDown>(ListWidget);

	TObjectPtr<UUserWidget>* ViewPtr = MenuWidgetMap.Find(EMenus::ViewDropDown);
	UUserWidget* ViewWidget = ViewPtr->Get();
	if (ViewWidget)
		ViewDropDownWidget = Cast<UViewDropDown>(ViewWidget);


	return MenuWidgetMap;

}

TMap<EMenusVR, TWeakObjectPtr<AVRWidgetActor>> UIManager::InitializeVRMenu()
{
	//AFreeCameraPawn* FreeCamPawn = Cast<AFreeCameraPawn>(PlayerPawn);
	WidgetClassMapVR.Empty();
	MenuWidgetMapVR.Empty();
	RegisterMenuPathVR(EMenusVR::MainMenu, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_VRMainMenu.WBP_VRMainMenu_C"));
	RegisterMenuPathVR(EMenusVR::ShortcutToolbar, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_VRShortcutToolbar.WBP_VRShortcutToolbar_C"));
	RegisterMenuPathVR(EMenusVR::MapLayers, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_MapLayersVR.WBP_MapLayersVR_C"));
	RegisterMenuPathVR(EMenusVR::BattlespaceGraphics, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_BattlespaceGraphics.WBP_BattlespaceGraphics_C"));
	RegisterMenuPathVR(EMenusVR::EntityVisuals, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_EntityVisuals.WBP_EntityVisuals_C"));
	RegisterMenuPathVR(EMenusVR::EntityLabels, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_EntityLabel.WBP_EntityLabel_C"));
	RegisterMenuPathVR(EMenusVR::Trails, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_Trails.WBP_Trails_C"));
	RegisterMenuPathVR(EMenusVR::Drawings, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_Drawings.WBP_Drawings_C"));

	return MenuWidgetMapVR;
}

UIManager* UIManager::GetInstance()
{
	if (UIManagerInstance == nullptr)
	{
		UIManagerInstance = new UIManager();
	}
	return UIManagerInstance;
}

bool UIManager::LoadModesFromConfig(const FString& ConfigFilePath, UObject* Outer)
{
	FXmlFile XmlFile(ConfigFilePath);
	if (!XmlFile.IsValid())
	{
		return false;
	}
	const FXmlNode* RootNode = XmlFile.GetRootNode();
	if (!RootNode || RootNode->GetTag() != TEXT("METAVERSEModesConfig"))
	{
		return false;
	}
	FString RequestedActiveModeName;
	if (const FXmlNode* ActiveModeNode = RootNode->FindChildNode(TEXT("ActiveMode")))
	{
		if (const FXmlNode* ActiveTypeNode = ActiveModeNode->FindChildNode(TEXT("ActiveUIType")))
		{
			RequestedActiveModeName = ActiveTypeNode->GetContent().TrimStartAndEnd();
		}
	}
	if (RequestedActiveModeName.IsEmpty())
	{
		return false;
	}
	const FXmlNode* ModesNode = RootNode->FindChildNode(TEXT("Modes"));
	if (!ModesNode)
	{
		return false;
	}
	const TArray<FXmlNode*>& ModeNodes = ModesNode->GetChildrenNodes();
	const FXmlNode* MatchedModeNode = nullptr;
	for (const FXmlNode* ModeNode : ModeNodes)
	{
		if (!ModeNode || ModeNode->GetTag() != TEXT("Mode"))
		{
			continue;
		}
		const FXmlNode* NameNode = ModeNode->FindChildNode(TEXT("ModeName"));
		if (!NameNode)
		{
			continue;
		}
		const FString ThisModeName = NameNode->GetContent().TrimStartAndEnd();
		if (ThisModeName.Equals(RequestedActiveModeName, ESearchCase::IgnoreCase))
		{
			MatchedModeNode = ModeNode;
			break;
		}
	}
	if (!MatchedModeNode)
	{
		return false;
	}
	ActiveMode = NewObject<UMetaverseMode>(GetTransientPackage());
	if (!ActiveMode)
	{
		return false;
	}
	ActiveMode->AddToRoot();
	if (!ActiveMode->InitFromXmlModeNode(MatchedModeNode))
	{
		ActiveMode = nullptr;
		return false;
	}
	return true;
}

void UIManager::CreateMenu(EMenus MenuType)
{
	if (!MenuWidgetMap.Contains(MenuType))
	{
		TSoftClassPtr<UUserWidget>* ClassPtr = WidgetClassMap.Find(MenuType);
		if (!World)
			return;
		UClass* widgetClass = ClassPtr->LoadSynchronous();
		if (!widgetClass) return;
		UUserWidget* Widget = CreateWidget<UUserWidget>(World, widgetClass);
		if (!Widget) return;
		if (Widget)
		{
			MenuWidgetMap.Add(MenuType, Widget);
		}
	}

}

void UIManager::CreateMenuVR(EMenusVR MenuTypeVR)
{
	if (!MenuWidgetMapVR.Contains(MenuTypeVR))
	{
		const TSubclassOf<UUserWidget>* ClassPtr = WidgetClassMapVR.Find(MenuTypeVR);
		if (!World)
			return;

		PlayerPawn = World->GetFirstPlayerController()->GetPawn();

		if (PlayerPawn) {
			FreeCamPawn = Cast<AFreeCameraPawn>(PlayerPawn);
			if (FreeCamPawn && FreeCamPawn->LeftController) {
				if (MenuTypeVR != EMenusVR::ShortcutToolbar) {
					VRActor = World->SpawnActor<AVRWidgetActor>(AVRWidgetActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
					VRActor->AttachToComponent(FreeCamPawn->LeftController, FAttachmentTransformRules::KeepRelativeTransform);
					VRActor->SetActorRelativeLocation(FVector(3.000000, -9.000000, -14.000000));
					VRActor->SetActorRelativeRotation(FRotator(-30.000000, 180.000000, -161.000000));
				}
				else {
					ToolbarVRActor = World->SpawnActor<AVRWidgetActor>(AVRWidgetActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
					ToolbarLocation(MenuTypeVR);
				}
			}
		}

		if (ClassPtr && MenuTypeVR != EMenusVR::ShortcutToolbar)
		{
			VRActor->SetVRWidget(*ClassPtr);
			MenuWidgetMapVR.Add(MenuTypeVR, VRActor);
		}

		if ((ClassPtr && MenuTypeVR == EMenusVR::ShortcutToolbar)) {
			ToolbarVRActor->SetVRWidget(*ClassPtr);
			MenuWidgetMapVR.Add(EMenusVR::ShortcutToolbar, ToolbarVRActor);
		}

	}

}

void UIManager::HideMenu(EMenus MenuType)
{
	if (MenuWidgetMap.Contains(MenuType))
	{
		MenuWidgetMap[MenuType]->RemoveFromViewport();
	}

}

void UIManager::ShowMenu(EMenus MenuType)
{
	if (MenuWidgetMap.Contains(MenuType))
	{
		MenuWidgetMap[MenuType]->AddToViewport(0);
	}
}

void UIManager::ShowMenuVR(EMenusVR MenuTypeVR)
{

	TWeakObjectPtr<AVRWidgetActor>* VRActorPtr = MenuWidgetMapVR.Find(MenuTypeVR);
	if (!VRActorPtr)
	{
		CreateMenuVR(MenuTypeVR);
		MenuWidgetMapVR[MenuTypeVR]->ShowWidget();
	}
	else
	{
		MenuWidgetMapVR[MenuTypeVR]->ShowWidget();
	}

	if (MenuHistory.Num() > 0 && MenuHistory.Last() == MenuTypeVR) return;
	MenuHistory.Add(MenuTypeVR);
}

//-------------------------------POSITION START
FVector2D UIManager::BottomLeftViewportPos(UWidget* Anchor)
{
	if (!Anchor) return FVector2D::ZeroVector;
	const FGeometry& geo = Anchor->GetCachedGeometry();
	const FVector2D LocalBL(0.f, geo.GetLocalSize().Y);
	//const FVector2D Abs = geo.LocalToAbsolute(LocalBL);
	FVector2D Pixel, Viewport;
	USlateBlueprintLibrary::LocalToViewport(ActiveWorldContext.Get(), geo, LocalBL, Pixel, Viewport);
	return Viewport;
}

void UIManager::Reposition()
{
	if (!ActiveMenu.IsValid() || !ActiveAnchor.IsValid())
	{
		close();
		return;
	}
	FVector2D Target = BottomLeftViewportPos(ActiveAnchor.Get()) + ActiveGap;
	ActiveMenu->ForceLayoutPrepass();
	const FVector2D MenuSize = ActiveMenu->GetDesiredSize();
	const FVector2D ViewSize = UWidgetLayoutLibrary::GetViewportSize(ActiveWorldContext.Get());
	if (Target.Y + MenuSize.Y > ViewSize.Y)
	{
		const FVector2D AnchorBL = BottomLeftViewportPos(ActiveAnchor.Get());
		Target.Y = FMath::Max(0.f, AnchorBL.Y - ActiveGap.Y - MenuSize.Y);
	}
	Target.X = FMath::Clamp(Target.X, 0.f, FMath::Max(0.f, ViewSize.X - MenuSize.X));
	Target.Y = FMath::Clamp(Target.Y, 0.f, FMath::Max(0.f, ViewSize.Y - MenuSize.Y));
	ActiveMenu->SetAlignmentInViewport(FVector2D(0.f, 0.f));
	ActiveMenu->SetPositionInViewport(Target, false);
}

bool UIManager::Tick(float)
{
	if (!ActiveMenu.IsValid() || !ActiveAnchor.IsValid() || !ActiveWorldContext.IsValid())
	{
		close();
		return false;
	}
	Reposition();
	return true;
}

void UIManager::StartTicker()
{
	if (bTickerRunning) return;
	TickerHandle = FTSTicker::GetCoreTicker().AddTicker(FTickerDelegate::CreateStatic(&UIManager::Tick), 0.f);
	bTickerRunning = true;
}

void UIManager::StopTicker()
{
	if (TickerHandle.IsValid())
	{
		FTSTicker::GetCoreTicker().RemoveTicker(TickerHandle);
		TickerHandle.Reset();
		bTickerRunning = false;
	}

}

FVector2D UIManager::GetWidgetLocalSize(UWidget* w, UObject* WorldContext)
{
	const FGeometry& geo = w->GetCachedGeometry();
	FVector2D ViewportPos, PixelPos;
	USlateBlueprintLibrary::LocalToViewport(WorldContext, geo, FVector2D(0.f, 0.f), PixelPos, ViewportPos);
	return ViewportPos;
}

FVector2D UIManager::GetButtonSize(UWidget* w)
{
	if (!w) return FVector2D::ZeroVector;
	return w->GetCachedGeometry().GetLocalSize();
}

FVector2D UIManager::CalculateForwardMenuPosition(UObject* WorldContext, UWidget* Anchor, UUserWidget* Menu)
{
	FVector2D BtnPos = GetWidgetLocalSize(Anchor, WorldContext);
	FVector2D BtnSize = GetButtonSize(Anchor);
	FVector2D MenuSize = Menu->GetDesiredSize();
	FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(WorldContext);
	FVector2D MenuPos = FVector2D(BtnPos.X + BtnSize.X, BtnPos.Y);
	if (MenuPos.X + MenuSize.X > ViewportSize.X)
	{
		MenuPos.X = BtnPos.X - MenuSize.X;
	}
	const float VerticalOffset = 0.f;
	const float HorizontalOffset = 17.f;
	MenuPos.X += HorizontalOffset;
	MenuPos.Y += VerticalOffset;
	return MenuPos;
}

void UIManager::CloseAllOpenMenu()
{
	for (UUserWidget* OpenedMenu1 : OpenMenu)
	{
		if (OpenedMenu1) OpenedMenu1->RemoveFromViewport();

		if (ButtonSates.bIsObjectList == true)
		{
			ButtonSates.bIsObjectList = false;
			MenuWidgetMap[EMenus::EntityList]->RemoveFromViewport();
		}
	}

	OpenMenu.Empty();
}

void UIManager::Toggle(UObject* WorldContextObject, UWidget* AnchorButton, UUserWidget* MenuInstance, float GapX, float GapY)
{
	if (!AnchorButton || !WorldContextObject || !MenuInstance) return;
	if (ActiveMenu.IsValid() && ActiveAnchor.Get() == AnchorButton)
	{
		close();
		return;
	}
	close();
	//if (!MenuInstance->IsInViewport()) MenuInstance->AddToViewport(1000);
	MenuInstance->SetIsFocusable(true);
	MenuInstance->ForceLayoutPrepass();
	ActiveWorldContext = WorldContextObject;
	ActiveMenu = MenuInstance;
	ActiveAnchor = AnchorButton;
	ActiveGap = FVector2D(GapX, GapY);
	Reposition();
	StartTicker();
}

void UIManager::close()
{
	if (ActiveMenu.IsValid())
	{
		ActiveMenu->RemoveFromViewport();
	}
	ActiveMenu.Reset();
	ActiveAnchor.Reset();
	ActiveWorldContext.Reset();
	StopTicker();
}

//-------------------------------POSITION END

void UIManager::HidAllMenus()
{
	for (const TPair<EMenus, TObjectPtr<UUserWidget>>& element : MenuWidgetMap) {
		if (element.Key != EMenus::MainMenu && element.Key != EMenus::EntityList && element.Key != EMenus::StatusBar) {
			element.Value->RemoveFromParent();
			element.Value->RemoveFromViewport();
			
		}
	}
}

void UIManager::HideMenuVR(EMenusVR MenuTypeVR)
{
	if (MenuWidgetMapVR.Contains(MenuTypeVR)) {
		MenuWidgetMapVR[MenuTypeVR]->HideWidget();
	}
}

void UIManager::UpdateFPS(int fps)
{
	if (!ADisplayManager::GetInstance()->isVRMode)
	{
		UHeadMountedDisplayFunctionLibrary::EnableHMD(false);
	}
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		return;
	}

	if (StatusBar)
	{
		StatusBar->SetFPS(fps);
	}
	else
	{
		TObjectPtr<UUserWidget>* MainMenuPtr = MenuWidgetMap.Find(EMenus::StatusBar);
		UUserWidget* MainMenuWidget = MainMenuPtr->Get();
		if (MainMenuWidget)
			StatusBar = Cast<UStatusBar>(MainMenuWidget);
		StatusBar->SetFPS(fps);
	}

}

void UIManager::UpdateFPSVR(int fps)
{
	if (!ADisplayManager::GetInstance()->isVRMode) return;
	if (Toolbar)
	{
		Toolbar->SetFPS(fps);
	}
	else
	{
		TWeakObjectPtr<AVRWidgetActor>* ActorWeakPtr = MenuWidgetMapVR.Find(EMenusVR::ShortcutToolbar);
		if (ActorWeakPtr && ActorWeakPtr->IsValid())
		{
			AVRWidgetActor* WidgetActor = ActorWeakPtr->Get();
			UWidgetComponent* ActorWidgetComponnt = WidgetActor->FindComponentByClass<UWidgetComponent>();
			if (ActorWidgetComponnt)
			{
				UUserWidget* ActorUserWidget = ActorWidgetComponnt->GetWidget();
				if (ActorUserWidget)
				{
					Toolbar = Cast<UVRShortcutToolbar>(ActorUserWidget);
					Toolbar->SetFPS(fps);
				}
			}

		}
	}
}

void UIManager::ToolbarLocation(EMenusVR MenuType)
{
	if (MenuType != EMenusVR::ShortcutToolbar)
		return;
	//CameraLocation = FreeCamPawn->Camera->GetComponentLocation();
	ToolbarVRActor->SetActorRelativeLocation(CameraLocation + FVector(50.0f, 10.0f, -30.0f));
	ToolbarVRActor->SetActorRelativeRotation(FRotator(2.000000f, -180.000000f, 0.000000f));
	ToolbarVRActor->WidgetComponent->SetDrawAtDesiredSize(true);

}

UIManager::~UIManager()
{
	UIManagerInstance = nullptr;
	delete UIManagerInstance;

}

//-----------FOR VR BUTTONS STATE
void UIManager::SetState(EButtonsName button)
{
	
	switch (button)
	{
	case EButtonsName::ShadedRelief:
	{
		ButtonSates.bIsTerrainVisuals = !ButtonSates.bIsTerrainVisuals;
		if (isShadedVisible)
		{
			isShadedVisible = false;
			ATerrainManager::GetInstance()->ShiftToShadedReleif(isShadedVisible);
		}
		else
		{
			isShadedVisible = true;
			ATerrainManager::GetInstance()->ShiftToShadedReleif(isShadedVisible);
		}
		break;
	}

	case EButtonsName::ToggleBorder:
	{
		ButtonSates.bIsToggleBorder = !ButtonSates.bIsToggleBorder;
		ATerrainManager::GetInstance()->ToggleInternationalBorder(ButtonSates.bIsToggleBorder);
		break;
	}

	case EButtonsName::SplatMap:
	{
		ButtonSates.bIsTerrainSplat = !ButtonSates.bIsTerrainSplat;
		if (ASplatMapping::GetInstance())  	ASplatMapping::GetInstance()->SetPolygonOverlaysVisible(ButtonSates.bIsTerrainSplat);
		break;
	}

	case EButtonsName::ObjectList:
	{
		ButtonSates.bIsObjectList = !ButtonSates.bIsObjectList;
		if (ButtonSates.bIsObjectList == true)
		{
			ShowMenu(EMenus::EntityList);
		}
		else {
			HideMenu(EMenus::EntityList);

		}
		break;
	}

	case EButtonsName::Analytics:
	{
		ButtonSates.bIsAnalytics = !ButtonSates.bIsAnalytics;
		ADisplayManager::GetInstance()->FreeCamPawn->ToggleStatsTable(0);
		break;
	}
	case EButtonsName::StatusBar:
		break;

	case EButtonsName::TextureModel:
	{
		ButtonSates.bIsTextureModel = !ButtonSates.bIsTextureModel;
		ButtonSates.bIsForceBasedModel = false;
		ButtonSates.bIsMil2525Model = false;
		EntityManager::GetEntityManagerInstance()->ShowTexturedModel();
		break;
	}

	case EButtonsName::ForceBasedModel:
	{
		ButtonSates.bIsForceBasedModel = !ButtonSates.bIsForceBasedModel;
		ButtonSates.bIsTextureModel = false;
		ButtonSates.bIsMil2525Model = false;
		EntityManager::GetEntityManagerInstance()->ShowColoredModel();
		break;
	}

	case EButtonsName::Mil2525Model:
	{
		ButtonSates.bIsMil2525Model = !ButtonSates.bIsMil2525Model;
		ButtonSates.bIsTextureModel = false;
		ButtonSates.bIsForceBasedModel = false;
		EntityManager::GetEntityManagerInstance()->ShowMil2525Model();
		break;
	}

	case EButtonsName::Hook:
	{
		ButtonSates.bIsHook = !ButtonSates.bIsHook;
		if (SelectedEntity)
			ADisplayManager::GetInstance()->FreeCamPawn->ToggleHook(SelectedEntity, true);
		break;
	}

	case EButtonsName::Unhook:
	{
		ButtonSates.bIsUnhook = !ButtonSates.bIsUnhook;
		if (SelectedEntity)
			ADisplayManager::GetInstance()->FreeCamPawn->ToggleHook(SelectedEntity, false);
		break;
	}

	case EButtonsName::Compass:
	{
		ButtonSates.bIsCompass = !ButtonSates.bIsCompass;

		ADisplayManager::GetInstance()->FreeCamPawn->ToggleCompass(0);
		break;

	}

	case EButtonsName::HorizontalTrail:
	{
		ButtonSates.bIsHorizontalTrail = !ButtonSates.bIsHorizontalTrail;
		if (!trailController)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			trailController = World->SpawnActor<ATrailController>(
				ATrailController::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
		}

		TArray<AEntityBase*> remoteentities = EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList();
		for (AEntityBase* Entity : remoteentities)
		{
			Entity->toggleTrail(ButtonSates.bIsHorizontalTrail);
		}
		trailController->toggleTrailVisibility(ButtonSates.bIsHorizontalTrail);

		break;
	}

	case EButtonsName::VerticalTrail:
	{
		ButtonSates.bIsVerticalTrail = !ButtonSates.bIsVerticalTrail;
		if (!trailController)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			trailController = World->SpawnActor<ATrailController>(
				ATrailController::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
		}

		TArray<AEntityBase*> remoteentities = EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList();
		for (AEntityBase* Entity : remoteentities)
		{
			Entity->toggleVerticalTrail(ButtonSates.bIsVerticalTrail);
		}
		trailController->toggleVerticalTrailVisisbility(ButtonSates.bIsVerticalTrail);

		break;
	}

	case EButtonsName::EntityLabels:
	{
		ButtonSates.bIsEntityLabels = !ButtonSates.bIsEntityLabels;
		AScalingManager::GetInstance()->isShowLabel = ButtonSates.bIsEntityLabels;
		break;
	}

	case EButtonsName::AllLocklines:
	{
		ButtonSates.bIsAllLocklines = !ButtonSates.bIsAllLocklines;

		TArray<AEntityBase*> remoteentities = EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList();
		for (AEntityBase* Entity : remoteentities)
		{
			if (!IsValid(Entity)) continue;
			if (ButtonSates.bIsAllLocklines == true)
			{
				Entity->SetLockLineType(ELockLineType::All);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::All;

			}
			else if (ButtonSates.bIsSameLockline == true) {
				Entity->SetLockLineType(ELockLineType::SameOnly);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::SameOnly;
			}
			else if (ButtonSates.bIsOpposingLockline == true)
			{
				Entity->SetLockLineType(ELockLineType::OpposingOnly);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::OpposingOnly;
			}
			else {
				Entity->SetLockLineType(ELockLineType::None);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::None;
			}
			Entity->SetLockLineVisibility(ButtonSates.bIsAllLocklines);
		}
		break;
	}

	case EButtonsName::OpposingLockline:
	{
		ButtonSates.bIsOpposingLockline = !ButtonSates.bIsOpposingLockline;
		TArray<AEntityBase*> remoteentities = EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList();
		for (AEntityBase* Entity : remoteentities)
		{
			if (!IsValid(Entity)) continue;
			if (ButtonSates.bIsAllLocklines == true)
			{
				Entity->SetLockLineType(ELockLineType::All);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::All;

			}
			else if (ButtonSates.bIsSameLockline == true) {
				Entity->SetLockLineType(ELockLineType::SameOnly);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::SameOnly;
			}
			else if (ButtonSates.bIsOpposingLockline == true)
			{
				Entity->SetLockLineType(ELockLineType::OpposingOnly);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::OpposingOnly;
			}
			else {
				Entity->SetLockLineType(ELockLineType::None);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::None;
			}
			Entity->SetLockLineVisibility(ButtonSates.bIsOpposingLockline);
		}
		break;
	}

	case EButtonsName::SameLockline:
	{
		ButtonSates.bIsSameLockline = !ButtonSates.bIsSameLockline;
		TArray<AEntityBase*> remoteentities = EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList();
		for (AEntityBase* Entity : remoteentities)
		{
			if (!IsValid(Entity)) continue;
			if (ButtonSates.bIsAllLocklines == true)
			{
				Entity->SetLockLineType(ELockLineType::All);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::All;

			}
			else if (ButtonSates.bIsSameLockline == true) {
				Entity->SetLockLineType(ELockLineType::SameOnly);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::SameOnly;
			}
			else if (ButtonSates.bIsOpposingLockline == true)
			{
				Entity->SetLockLineType(ELockLineType::OpposingOnly);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::OpposingOnly;
			}
			else {
				Entity->SetLockLineType(ELockLineType::None);
				EntityManager::GetEntityManagerInstance()->GLockLineType = ELockLineType::None;
			}

			Entity->SetLockLineVisibility(ButtonSates.bIsSameLockline);
		}
		break;
	}

	case EButtonsName::GroundCoverages:
	{
		ButtonSates.bIsGroundCoverages = !ButtonSates.bIsGroundCoverages;
		UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(ButtonSates.bIsGroundCoverages, ERemoteEntityType::RADAR);
		UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(ButtonSates.bIsGroundCoverages, ERemoteEntityType::GENERAL_VEHICLE);
		UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(ButtonSates.bIsGroundCoverages, ERemoteEntityType::ARMORED_VEHICLE);
		UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(ButtonSates.bIsGroundCoverages, ERemoteEntityType::SHIPS);
		break;
	}

	case EButtonsName::GroundCoveragesFootprints:
	{
		ButtonSates.bIsGroundCoveragesFootprints = !ButtonSates.bIsGroundCoveragesFootprints;
		UCoveragesManager::GetInstance()->ToggleFootPrintsVisibility(ButtonSates.bIsGroundCoveragesFootprints);
		break;
	}

	case EButtonsName::DomeRing:
	{
		//ButtonSates.bIsDomeRing = !ButtonSates.bIsDomeRing;

		UCoveragesManager::GetInstance()->ToggleHorizontalRings(ButtonSates.bIsDomeRing);

		break;
	}

	case EButtonsName::HeightVectorRings:
	{
		//ButtonSates.bIsHeightVectorRings = !ButtonSates.bIsHeightVectorRings;
		EntityManager::GetEntityManagerInstance()->bRingsVisible = ButtonSates.bIsHeightVectorRings;
		break;
	}

	case EButtonsName::AircraftCoverage:
	{
		ButtonSates.bIsAircraftCoverage = !ButtonSates.bIsAircraftCoverage;
		UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(ButtonSates.bIsAircraftCoverage, ERemoteEntityType::FIXEDWING_AIRCRAFT);
		break;
	}

	case EButtonsName::AircraftOriginalCoverage:
	{
		ButtonSates.bIsAircraftOriginalCoverage = !ButtonSates.bIsAircraftOriginalCoverage;
		UCoveragesManager::GetInstance()->ToggleAircraftsDefaultAndOriginal(ButtonSates.bIsAircraftOriginalCoverage);
		break;
	}

	case EButtonsName::HeadingVector:
	{
		ButtonSates.bIsHeadingVector = !ButtonSates.bIsHeadingVector;
		if (!trailController)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			trailController = World->SpawnActor<ATrailController>(
				ATrailController::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		trailController->toggleForwardVectors(ButtonSates.bIsHeadingVector);

		break;
	}

	case EButtonsName::DownVector:
	{
		ButtonSates.bIsDownVector = !ButtonSates.bIsDownVector;
		if (!trailController)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			trailController = World->SpawnActor<ATrailController>(
				ATrailController::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		trailController->toggleGroundVectors(ButtonSates.bIsDownVector);

		break;
	}

	case EButtonsName::UpVector:
	{
		ButtonSates.bIsUpVector = !ButtonSates.bIsUpVector;
		if (!trailController)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			trailController = World->SpawnActor<ATrailController>(
				ATrailController::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		trailController->toggleUpVectors(ButtonSates.bIsUpVector);

		break;
	}
	break;
	case EButtonsName::Drawings:
	{
		ButtonSates.bIsDrawings = !ButtonSates.bIsDrawings;
		UDWGXDrawingManager::Get(World)->ToggleVisibility(ButtonSates.bIsDrawings);
		break;
	}

	case EButtonsName::DrawingsProjection:
	{
		ButtonSates.bIsDrawingsProjection = !ButtonSates.bIsDrawingsProjection;
		UDWGXDrawingManager::Get(World)->ToggleProjectionVisibility(ButtonSates.bIsDrawingsProjection);
		break;
	}

	case EButtonsName::Trail30Sec:
	{
		ButtonSates.bIsTrail30Sec = !ButtonSates.bIsTrail30Sec;
		ButtonSates.bIsTrailLifetime = false;
		ButtonSates.bIsTrail1Min = false;
		for (TActorIterator<ARibbonMeshActor> It(World); It; ++It) {
			ARibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(ERibbonTrailMode::Last30Seconds);

			}
		}

		for (TActorIterator<AVerticalRibbonMeshActor> It(World); It; ++It) {
			AVerticalRibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(EVerticalRibbonTrailMode::Last30Seconds);
			}
		}
		break;
	}

	case EButtonsName::Trail1Min:
	{
		ButtonSates.bIsTrail1Min = !ButtonSates.bIsTrail1Min;
		ButtonSates.bIsTrailLifetime = false;
		ButtonSates.bIsTrail30Sec = false;
		for (TActorIterator<ARibbonMeshActor> It(World); It; ++It) {
			ARibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(ERibbonTrailMode::Last60Seconds);

			}
		}

		for (TActorIterator<AVerticalRibbonMeshActor> It(World); It; ++It) {
			AVerticalRibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(EVerticalRibbonTrailMode::Last60Seconds);
			}
		}
		break;
	}

	case EButtonsName::TrailLifetime:
	{
		ButtonSates.bIsTrailLifetime = !ButtonSates.bIsTrailLifetime;
		ButtonSates.bIsTrail1Min = false;
		ButtonSates.bIsTrail30Sec = false;
		for (TActorIterator<ARibbonMeshActor> It(World); It; ++It) {
			ARibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(ERibbonTrailMode::Lifetime);

			}
		}

		for (TActorIterator<AVerticalRibbonMeshActor> It(World); It; ++It) {
			AVerticalRibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(EVerticalRibbonTrailMode::Lifetime);
			}
		}

		break;
	}

	case EButtonsName::ShortcutToolBar:
	{
		ButtonSates.bIsShortcutToolBar = !ButtonSates.bIsShortcutToolBar;
		if (ButtonSates.bIsShortcutToolBar)
		{
			ShowMenuVR(EMenusVR::ShortcutToolbar);
		}
		else
		{
			HideMenuVR(EMenusVR::ShortcutToolbar);
		}
		break;
	}
	case EButtonsName::Borders:
	{
		ButtonSates.bIsBorders = !ButtonSates.bIsBorders;

		break;
	}
	case EButtonsName::PakCities:
	{
		ButtonSates.bIsPakCities = !ButtonSates.bIsPakCities;

		AAirBaseManager::getInstance()->UpdatePakistanCitiesPinVisibility(ButtonSates.bIsPakCities);
		break;
	}
	case EButtonsName::IndCities:
	{
		ButtonSates.bIsIndCities = !ButtonSates.bIsIndCities;
		AAirBaseManager::getInstance()->UpdateIndianCitiesPinVisibility(ButtonSates.bIsIndCities);
		break;
	}

	case EButtonsName::IndBases:
	{
		ButtonSates.bIsIndBases = !ButtonSates.bIsIndBases;
		AAirBaseManager::getInstance()->UpdateIndianAirbasePinVisibility(ButtonSates.bIsIndBases);
		break;
	}

	case EButtonsName::PakBases:
	{
		ButtonSates.bIsPakBases = !ButtonSates.bIsPakBases;
		AAirBaseManager::getInstance()->UpdatePakistanBasePinVisibility(ButtonSates.bIsPakBases);
		break;
	}

	case EButtonsName::Towns:
		break;

	case EButtonsName::InternationalBorder:
	{
		ButtonSates.bIsInternationalBorder = !ButtonSates.bIsInternationalBorder;
		ATerrainManager::GetInstance()->ToggleInternationalBorder(ButtonSates.bIsToggleBorder);
		break;
	}

	case EButtonsName::EntitySmall:
	{
		ButtonSates.bIsEntitySmall = !ButtonSates.bIsEntitySmall;
		ButtonSates.bIsEntityMedium = false;
		ButtonSates.bIsEntityLarge = false;
		AScalingManager::GetInstance()->SetEntityScalingFactor(Multiplier::Small);
		break;
	}

	case EButtonsName::EntityMedium:
	{
		ButtonSates.bIsEntityMedium = !ButtonSates.bIsEntityMedium;
		ButtonSates.bIsEntitySmall = false;
		ButtonSates.bIsEntityLarge = false;
		AScalingManager::GetInstance()->SetEntityScalingFactor(Multiplier::Medium);
		break;
	}

	case EButtonsName::EntityLarge:
	{
		ButtonSates.bIsEntityLarge = !ButtonSates.bIsEntityLarge;
		ButtonSates.bIsEntitySmall = false;
		ButtonSates.bIsEntityMedium = false;
		AScalingManager::GetInstance()->SetEntityScalingFactor(Multiplier::Large);
		break;
	}

	case EButtonsName::LabelSmall:
	{
		ButtonSates.bIsLabelSmall = !ButtonSates.bIsLabelSmall;
		ButtonSates.bIsLabelMedium = false;
		ButtonSates.bIsLabelLarge = false;
		AScalingManager::GetInstance()->SetEntityLabelScalingFactor(Multiplier::Small);
		break;
	}

	case EButtonsName::LabelMedium:
	{
		ButtonSates.bIsLabelMedium = !ButtonSates.bIsLabelMedium;
		ButtonSates.bIsLabelSmall = false;
		ButtonSates.bIsLabelLarge = false;
		AScalingManager::GetInstance()->SetEntityLabelScalingFactor(Multiplier::Medium);
		break;
	}

	case EButtonsName::LabelLarge:
	{
		ButtonSates.bIsLabelLarge = !ButtonSates.bIsLabelLarge;
		ButtonSates.bIsLabelMedium = false;
		ButtonSates.bIsLabelSmall = false;
		AScalingManager::GetInstance()->SetEntityLabelScalingFactor(Multiplier::Large);
		break;
	}

	case EButtonsName::LabelOffset1:
	{
		ButtonSates.bIsLabelOffset1 = !ButtonSates.bIsLabelOffset1;
		ButtonSates.bIsLabelOffset2 = false;
		ButtonSates.bIsLabelOffset3 = false;
		AScalingManager::GetInstance()->SetEntityLabelOffsetFactor(Multiplier::Small);
		break;
	}

	case EButtonsName::LabelOffset2:
	{
		ButtonSates.bIsLabelOffset2 = !ButtonSates.bIsLabelOffset2;
		ButtonSates.bIsLabelOffset1 = false;
		ButtonSates.bIsLabelOffset3 = false;
		AScalingManager::GetInstance()->SetEntityLabelOffsetFactor(Multiplier::Medium);
		break;
	}

	case EButtonsName::LabelOffset3:
	{
		ButtonSates.bIsLabelOffset3 = !ButtonSates.bIsLabelOffset3;
		ButtonSates.bIsLabelOffset1 = false;
		ButtonSates.bIsLabelOffset2 = false;
		AScalingManager::GetInstance()->SetEntityLabelOffsetFactor(Multiplier::Large);
		break;
	}

	default:
		break;
	}
}

//--------------FOR SCREEN BUTTON STATES
void UIManager::SetStateofScreen(EButtonsName button, bool Value)
{
	ActiveMode = AModeManager::getInstance()->getActiveMode();
	if (ActiveMode)
	{
		if (FButtonStateStruct* State = ActiveMode->ButtonStates.Find(button))
		{
			State->FeatureActive = Value;   // store new state
		}
	}
	TMap<EButtonsName, FButtonStateStruct>& Map = ActiveMode->ButtonStates;
	auto SetFeatureActive = [&Map](EButtonsName Name, bool bOn)
		{
			if (FButtonStateStruct* State = Map.Find(Name))
			{
				State->FeatureActive = bOn;
			}
		};
	auto GetFeatureActive = [&Map](EButtonsName Name)-> bool
		{
			if (FButtonStateStruct* State = Map.Find(Name))
			{
				return State->FeatureActive;
			} return false;
		};

	switch (button)
	{
	case EButtonsName::ShadedRelief:
	{
		SetFeatureActive(EButtonsName::ShadedRelief, Value);
		ATerrainManager::GetInstance()->ShiftToShadedReleif(Value);
		break;
	}

	case EButtonsName::ToggleBorder:
	{
		SetFeatureActive(EButtonsName::InternationalBorder, Value);
		ATerrainManager::GetInstance()->ToggleInternationalBorder(Value);
		break;
	}

	case EButtonsName::SplatMap:
	{
		if (ASplatMapping::GetInstance()) {
		SetFeatureActive(EButtonsName::SplatMap, Value);
		ASplatMapping::GetInstance()->SetPolygonOverlaysVisible(Value);
	}
		break;
	}

	case EButtonsName::ObjectList:
	{
		if (Value == true)
		{
			ShowMenu(EMenus::EntityList);
		}
		else {
			HideMenu(EMenus::EntityList);

		}
		SetFeatureActive(EButtonsName::ObjectList, Value);
		break;
	}

	case EButtonsName::Analytics:
	{
		SetFeatureActive(EButtonsName::Analytics, Value);
		ADisplayManager::GetInstance()->FreeCamPawn->ToggleStatsTable(0);
		break;
	}
	case EButtonsName::StatusBar:
		break;

	case EButtonsName::TextureModel:
	{
		bool bNewValue = Value;
		if (FButtonStateStruct* State = Map.Find(EButtonsName::TextureModel))
		{
			if (!State->FeatureActive && Value == true)
			{
				bNewValue = true;
			}
			else if (State->FeatureActive && Value == true)
			{
				bNewValue = false;
			}
		}
		SetFeatureActive(EButtonsName::TextureModel, bNewValue);
		SetFeatureActive(EButtonsName::ForceBasedModel, false);
		SetFeatureActive(EButtonsName::Mil2525Model, false);
		EntityManager::GetEntityManagerInstance()->ShowTexturedModel();
		break;
	}

	case EButtonsName::ForceBasedModel:
	{
		bool bNewValue = Value;
		if (FButtonStateStruct* State = Map.Find(EButtonsName::ForceBasedModel))
		{
			if (!State->FeatureActive && Value == true)
			{
				bNewValue = true;
			}
			else if (State->FeatureActive && Value == true)
			{
				bNewValue = false;
			}
		}
		SetFeatureActive(EButtonsName::TextureModel, false);
		SetFeatureActive(EButtonsName::ForceBasedModel, bNewValue);
		SetFeatureActive(EButtonsName::Mil2525Model, false);

		EntityManager::GetEntityManagerInstance()->ShowColoredModel();
		break;
	}

	case EButtonsName::Mil2525Model:
	{
		bool bNewValue = Value;
		if (FButtonStateStruct* State = Map.Find(EButtonsName::Mil2525Model))
		{
			if (!State->FeatureActive && Value == true)
			{
				bNewValue = true;
			}
			else if (State->FeatureActive && Value == true)
			{
				bNewValue = false;
			}
		}
		SetFeatureActive(EButtonsName::TextureModel, false);
		SetFeatureActive(EButtonsName::ForceBasedModel, false);
		SetFeatureActive(EButtonsName::Mil2525Model, bNewValue);

		EntityManager::GetEntityManagerInstance()->ShowMil2525Model();
		break;
	}

	case EButtonsName::Hook:
	{
		if (SelectedEntity)
			ADisplayManager::GetInstance()->FreeCamPawn->ToggleHook(SelectedEntity, true);
		break;
	}

	case EButtonsName::Unhook:
	{
		if (SelectedEntity)
			ADisplayManager::GetInstance()->FreeCamPawn->ToggleHook(SelectedEntity, false);
		break;
	}

	case EButtonsName::Compass:
	{
		SetFeatureActive(EButtonsName::Compass, Value);
		ADisplayManager::GetInstance()->FreeCamPawn->ToggleCompass(0);
		break;
	}

	case EButtonsName::HorizontalTrail:
	{
		if (!trailController)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			trailController = World->SpawnActor<ATrailController>(
				ATrailController::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
		}

		TArray<AEntityBase*> remoteentities = EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList();
		for (AEntityBase* Entity : remoteentities)
		{
			Entity->toggleTrail(Value);
		}
		trailController->toggleTrailVisibility(Value);
		SetFeatureActive(EButtonsName::HorizontalTrail, Value);

		break;
	}

	case EButtonsName::VerticalTrail:
	{
		if (!trailController)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			trailController = World->SpawnActor<ATrailController>(
				ATrailController::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
		}

		TArray<AEntityBase*> remoteentities = EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList();
		for (AEntityBase* Entity : remoteentities)
		{
			Entity->toggleVerticalTrail(Value);
		}
		trailController->toggleVerticalTrailVisisbility(Value);
		SetFeatureActive(EButtonsName::VerticalTrail, Value);
		break;
	}

	case EButtonsName::EntityLabels:
	{
		SetFeatureActive(EButtonsName::EntityLabels, Value);
		AScalingManager::GetInstance()->isShowLabel = Value;
		break;
	}

	case EButtonsName::AllLocklines:
	{
		SetFeatureActive(EButtonsName::AllLocklines , Value);
		const bool bAll = GetFeatureActive(EButtonsName::AllLocklines);
		const bool bSame = GetFeatureActive(EButtonsName::SameLockline);
		const bool bOpposing = GetFeatureActive(EButtonsName::OpposingLockline);
		ELockLineType NewType = ELockLineType::None;
		if (bAll)
		{
			NewType = ELockLineType::All;
		}
		else if (bSame)
		{
			NewType = ELockLineType::SameOnly;
		}
		else if (bOpposing)
		{
			NewType = ELockLineType::OpposingOnly;
		}
		else
		{
			NewType = ELockLineType::None;
		}

		TArray<AEntityBase*> remoteentities = EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList();
		for (AEntityBase* Entity : remoteentities)
		{
			if (!IsValid(Entity)) continue;
			Entity->SetLockLineType(NewType);
			EntityManager::GetEntityManagerInstance()->GLockLineType = NewType;
			Entity->SetLockLineVisibility(bAll);
		}
		break;
	}

	case EButtonsName::OpposingLockline:
	{
		SetFeatureActive(EButtonsName::OpposingLockline, Value);
		const bool bAll = GetFeatureActive(EButtonsName::AllLocklines);
		const bool bSame = GetFeatureActive(EButtonsName::SameLockline);
		const bool bOpposing = GetFeatureActive(EButtonsName::OpposingLockline);
		ELockLineType NewType = ELockLineType::None;
		if (bAll)
		{
			NewType = ELockLineType::All;
		}
		else if (bSame)
		{
			NewType = ELockLineType::SameOnly;
		}
		else if (bOpposing)
		{
			NewType = ELockLineType::OpposingOnly;
		}
		else
		{
			NewType = ELockLineType::None;
		}

		TArray<AEntityBase*> remoteentities = EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList();
		for (AEntityBase* Entity : remoteentities)
		{
			if (!IsValid(Entity)) continue;
			Entity->SetLockLineType(NewType);
			EntityManager::GetEntityManagerInstance()->GLockLineType =NewType;
			Entity->SetLockLineVisibility(bOpposing);
		}
		break;
	}

	case EButtonsName::SameLockline:
	{
		SetFeatureActive(EButtonsName::SameLockline, Value);
		const bool bAll = GetFeatureActive(EButtonsName::AllLocklines);
		const bool bSame = GetFeatureActive(EButtonsName::SameLockline);
		const bool bOpposing = GetFeatureActive(EButtonsName::OpposingLockline);
		ELockLineType NewType = ELockLineType::None;
		if (bAll)
		{
			NewType = ELockLineType::All;
		}
		else if (bSame)
		{
			NewType = ELockLineType::SameOnly;
		}
		else if (bOpposing)
		{
			NewType = ELockLineType::OpposingOnly;
		}
		else
		{
			NewType = ELockLineType::None;
		}

		TArray<AEntityBase*> remoteentities = EntityManager::GetEntityManagerInstance()->getRemoteEntitiesList();
		for (AEntityBase* Entity : remoteentities)
		{
			if (!IsValid(Entity)) continue;
			Entity->SetLockLineType(NewType);
			EntityManager::GetEntityManagerInstance()->GLockLineType = NewType;
			Entity->SetLockLineVisibility(bSame);
		}
		break;
	}

	case EButtonsName::GroundCoverages:
	{
		SetFeatureActive(EButtonsName::GroundCoverages, Value);
		UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(Value, ERemoteEntityType::RADAR);
		UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(Value, ERemoteEntityType::GENERAL_VEHICLE);
		UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(Value, ERemoteEntityType::ARMORED_VEHICLE);
		UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(Value, ERemoteEntityType::SHIPS);
		if (!Value && GetFeatureActive(EButtonsName::DomeRing))
		{
			SetFeatureActive(EButtonsName::DomeRing, false);
			UCoveragesManager::GetInstance()->ToggleHorizontalRings(false);
		}
		break;
	}

	case EButtonsName::GroundCoveragesFootprints:
	{
		SetFeatureActive(EButtonsName::GroundCoveragesFootprints, Value);
		UCoveragesManager::GetInstance()->ToggleFootPrintsVisibility(Value);
		break;
	}

	case EButtonsName::DomeRing:
	{
		const bool bCoveragesOn = GetFeatureActive(EButtonsName::GroundCoverages);
		if (Value && !bCoveragesOn)
		{
			SetFeatureActive(EButtonsName::DomeRing, false);
			UCoveragesManager::GetInstance()->ToggleHorizontalRings(false);
		}
		else
		{
			SetFeatureActive(EButtonsName::DomeRing, Value);
			UCoveragesManager::GetInstance()->ToggleHorizontalRings(Value);
		}
		
		break;
	}

	case EButtonsName::DownVector:
	{
		bool bCurrent = GetFeatureActive(EButtonsName::DownVector);
		
		if (!trailController)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			trailController = World->SpawnActor<ATrailController>(
				ATrailController::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		trailController->toggleGroundVectors(Value);
		if (!bCurrent)
		{
			SetFeatureActive(EButtonsName::HeightVectorRings, false);
			EntityManager::GetEntityManagerInstance()->bRingsVisible = false;
		}
		break;
	}

	case EButtonsName::HeightVectorRings:
	{
		bool bParent = GetFeatureActive(EButtonsName::DownVector);
		if (!bParent)
		{
			SetFeatureActive(EButtonsName::HeightVectorRings, false);
			EntityManager::GetEntityManagerInstance()->bRingsVisible = false;
			return;
		}
		bool bCurrent = GetFeatureActive(EButtonsName::HeightVectorRings);
		
		SetFeatureActive(EButtonsName::HeightVectorRings, bCurrent);
		EntityManager::GetEntityManagerInstance()->bRingsVisible = bCurrent;
		
		break;
	}

	case EButtonsName::AircraftCoverage:
	{
		SetFeatureActive(EButtonsName::AircraftCoverage, Value);
		UCoveragesManager::GetInstance()->ToggleVisibilityOfCoveragesByRemoteEntityType(Value, ERemoteEntityType::FIXEDWING_AIRCRAFT);
		break;
	}

	case EButtonsName::AircraftOriginalCoverage:
	{
		UCoveragesManager::GetInstance()->ToggleAircraftsDefaultAndOriginal(Value);
		break;
	}

	case EButtonsName::HeadingVector:
	{
		if (!trailController)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			trailController = World->SpawnActor<ATrailController>(
				ATrailController::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		trailController->toggleForwardVectors(Value);
		SetFeatureActive(EButtonsName::HeadingVector, Value);
		break;
	}

	case EButtonsName::UpVector:
	{
		if (!trailController)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			trailController = World->SpawnActor<ATrailController>(
				ATrailController::StaticClass(),
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);
		}
		trailController->toggleUpVectors(Value);
		SetFeatureActive(EButtonsName::UpVector, Value);
		break;
	}
	break;
	case EButtonsName::Drawings:
	{
		SetFeatureActive(EButtonsName::Drawings, Value);
		UDWGXDrawingManager::Get(World)->ToggleVisibility(Value);
		break;
	}

	case EButtonsName::DrawingsProjection:
	{
		SetFeatureActive(EButtonsName::DrawingsProjection, Value);
		UDWGXDrawingManager::Get(World)->ToggleProjectionVisibility(Value);
		break;
	}

	case EButtonsName::HorizontalTrail30Sec:
	{
		SetFeatureActive(EButtonsName::HorizontalTrail30Sec, Value);
		SetFeatureActive(EButtonsName::HorizontalTrail1Min, false);
		SetFeatureActive(EButtonsName::HorizontalTrailLifetime, false);
		ERibbonTrailMode Mode = ERibbonTrailMode::Last30Seconds;
		
		for (TActorIterator<ARibbonMeshActor> It(World); It; ++It) {
			ARibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(Mode);

			}
		}
		break;
	}

	case EButtonsName::VerticalTrail30Sec:
	{
		SetFeatureActive(EButtonsName::VerticalTrail30Sec, Value);
		SetFeatureActive(EButtonsName::VerticalTrail1Min, false);
		SetFeatureActive(EButtonsName::VerticalTrailLifetime, false);
		EVerticalRibbonTrailMode VMode = EVerticalRibbonTrailMode::Last30Seconds;
	
		for (TActorIterator<AVerticalRibbonMeshActor> It(World); It; ++It) {
			AVerticalRibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(VMode);
			}
		}
		break;
	}

	case EButtonsName::HorizontalTrail1Min:
	{
		SetFeatureActive(EButtonsName::HorizontalTrail30Sec, false);
		SetFeatureActive(EButtonsName::HorizontalTrail1Min, Value);
		SetFeatureActive(EButtonsName::HorizontalTrailLifetime, false);
		ERibbonTrailMode Mode = ERibbonTrailMode::Last60Seconds;
		
		for (TActorIterator<ARibbonMeshActor> It(World); It; ++It) {
			ARibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(Mode);

			}
		}
		break;
	}

	case EButtonsName::VerticalTrail1Min:
	{
		SetFeatureActive(EButtonsName::VerticalTrail30Sec, false);
		SetFeatureActive(EButtonsName::VerticalTrail1Min, Value);
		SetFeatureActive(EButtonsName::VerticalTrailLifetime, false);
		EVerticalRibbonTrailMode VMode = EVerticalRibbonTrailMode::Last60Seconds;
		
		for (TActorIterator<AVerticalRibbonMeshActor> It(World); It; ++It) {
			AVerticalRibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(VMode);
			}
		}
		break;
	}

	case EButtonsName::HorizontalTrailLifetime:
	{
		SetFeatureActive(EButtonsName::HorizontalTrail30Sec, false);
		SetFeatureActive(EButtonsName::HorizontalTrail1Min, false);
		SetFeatureActive(EButtonsName::HorizontalTrailLifetime, Value);
		ERibbonTrailMode Mode = ERibbonTrailMode::Lifetime;
		
		for (TActorIterator<ARibbonMeshActor> It(World); It; ++It) {
			ARibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(Mode);

			}
		}
		break;
	}

	case EButtonsName::VerticalTrailLifetime:
	{
		SetFeatureActive(EButtonsName::VerticalTrail30Sec, false);
		SetFeatureActive(EButtonsName::VerticalTrail1Min, false);
		SetFeatureActive(EButtonsName::VerticalTrailLifetime, Value);
		EVerticalRibbonTrailMode VMode = EVerticalRibbonTrailMode::Lifetime;
	
		for (TActorIterator<AVerticalRibbonMeshActor> It(World); It; ++It) {
			AVerticalRibbonMeshActor* Trail = *It;
			if (Trail)
			{
				Trail->SetTrailMode(VMode);
			}
		}
		break;
	}

	case EButtonsName::Borders:
	{
		break;
	}
	case EButtonsName::PakCities:
	{
		SetFeatureActive(EButtonsName::PakCities, Value);
		AAirBaseManager::getInstance()->UpdatePakistanCitiesPinVisibility(Value);
		break;
	}
	case EButtonsName::IndCities:
	{
		SetFeatureActive(EButtonsName::IndCities, Value);
		AAirBaseManager::getInstance()->UpdateIndianCitiesPinVisibility(Value);
		break;
	}

	case EButtonsName::IndBases:
	{
		SetFeatureActive(EButtonsName::IndBases, Value);
		AAirBaseManager::getInstance()->UpdateIndianAirbasePinVisibility(Value);
		break;
	}

	case EButtonsName::PakBases:
	{
		SetFeatureActive(EButtonsName::PakBases, Value);
		AAirBaseManager::getInstance()->UpdatePakistanBasePinVisibility(Value);
		break;
	}

	case EButtonsName::Towns:
		break;

	case EButtonsName::InternationalBorder:
	{
		ATerrainManager::GetInstance()->ToggleInternationalBorder(Value);
		break;
	}

	case EButtonsName::Scaling:
	{
		SetFeatureActive(EButtonsName::Scaling, Value);
		break;
	}

	case EButtonsName::Vegetation:
		SetFeatureActive(EButtonsName::Vegetation, Value);
		break;

	case EButtonsName::VisualGraphics:
		SetFeatureActive(EButtonsName::VisualGraphics, Value);
		break;
	case EButtonsName::Blink:
		SetFeatureActive(EButtonsName::Blink, Value);
		break;


	default:
		break;
	}
}

void UIManager::ShutDown() {
	UIManagerInstance = nullptr;
}
