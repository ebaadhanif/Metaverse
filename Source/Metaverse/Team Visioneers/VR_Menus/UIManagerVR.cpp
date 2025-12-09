#include "UIManagerVR.h"
#include "../DisplayManager.h"
#include "VRWidgetActor.h"
#include <HanTracking.h>

UUIManagerVR* UUIManagerVR::UIManagerVRInstance = nullptr;

UUIManagerVR::UUIManagerVR()
{
}
void UUIManagerVR::RegisterMenuPath(EMenusVR MenuType, const TCHAR* ClassPath)
{
	int a = 0;
	if (UClass* cls = LoadClass<UUserWidget>(nullptr, ClassPath))
	{
		WidgetClassMap.Add(MenuType, cls);
	}
}


void UUIManagerVR::Initialize()
{

	WidgetClassMap.Empty();
	MenuWidgetMap.Empty();
	RegisterMenuPath(EMenusVR::MainMenu, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_VRMainMenu.WBP_VRMainMenu_C"));
	RegisterMenuPath(EMenusVR::ShortcutToolbar, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_VRShortcutToolbar.WBP_VRShortcutToolbar_C"));
	RegisterMenuPath(EMenusVR::MapLayers, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_MapLayersVR.WBP_MapLayersVR_C"));
	RegisterMenuPath(EMenusVR::BattlespaceGraphics, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_BattlespaceGraphics.WBP_BattlespaceGraphics_C"));
	RegisterMenuPath(EMenusVR::EntityVisuals, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_EntityVisuals.WBP_EntityVisuals_C"));
	RegisterMenuPath(EMenusVR::EntityLabels, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_EntityLabel.WBP_EntityLabel_C"));
	RegisterMenuPath(EMenusVR::Trails, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_Trails.WBP_Trails_C"));
	RegisterMenuPath(EMenusVR::Drawings, TEXT("/Game/Blueprints/VR_UserInterfaces/WBP_Drawings.WBP_Drawings_C"));

}

UUIManagerVR* UUIManagerVR::GetInstance()
{
	if (UIManagerVRInstance == nullptr)
	{
		UIManagerVRInstance = NewObject<UUIManagerVR>();
	}
	return UIManagerVRInstance;
}

void UUIManagerVR::UpdateFPS(int fps)
{
	if (Toolbar)
	{
		Toolbar->SetFPS(fps);
	}
	else
	{
		TWeakObjectPtr<AVRWidgetActor>* ActorWeakPtr = MenuWidgetMap.Find(EMenusVR::ShortcutToolbar);
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

void UUIManagerVR::CreateMenu(EMenusVR MenuType)
{
	if (!MenuWidgetMap.Contains(MenuType))
	{
		AFreeCameraPawn* FreeCamPawn = nullptr;
		
		const TSubclassOf<UUserWidget>* ClassPtr = WidgetClassMap.Find(MenuType);
		if (!World)
			return;
		AVRWidgetActor* VRActor = World->SpawnActor<AVRWidgetActor>(AVRWidgetActor::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);
		
			if (VRActor) {
				APawn* PlayerPawn = World->GetFirstPlayerController()->GetPawn();

				if (PlayerPawn) {
					FreeCamPawn = Cast<AFreeCameraPawn>(PlayerPawn);
					if (FreeCamPawn && FreeCamPawn->LeftController && IsValid(FreeCamPawn->LeftController)) {
						if (MenuType != EMenusVR::ShortcutToolbar) {
							VRActor->AttachToComponent(FreeCamPawn->LeftController, FAttachmentTransformRules::KeepRelativeTransform);
							VRActor->SetActorRelativeLocation(FVector(3.0f, -3.0f, -11.0f));
						}
						else {
							VRActor->AttachToComponent(FreeCamPawn->Camera, FAttachmentTransformRules::KeepRelativeTransform);
							VRActor->SetActorRelativeLocation(FVector(48.000000f, -20.000000f, -10.000000f));
							VRActor->SetActorRelativeRotation(FRotator(2.000000f, -180.000000f, 0.000000f));
							/*VRActor->SetActorLocation(FVector( 64.000000f, 2.000000f,  -10.000000f));*/
							VRActor->WidgetComponent->SetDrawAtDesiredSize(true);
							VRActor->WidgetComponent->SetVisibility(false);
						}
					}
				}
			}
		

		if (ClassPtr)
		{
			VRActor->SetVRWidget(*ClassPtr);
			MenuWidgetMap.Add(MenuType, VRActor);
		}

		
	}

}

void UUIManagerVR::ShowMenu(EMenusVR MenuType)
{
	/*TWeakObjectPtr<AVRWidgetActor>* VRActor = MenuWidgetMap.Find(MenuType);
	if (!VRActor)
	{
		CreateMenu(MenuType);
		if (MenuWidgetMap.Num() > 0 || MenuWidgetMap[MenuType] != NULL)
			MenuWidgetMap[MenuType]->ShowWidget();
	}
	else
	{
		if(MenuWidgetMap.Num()> 0 || MenuWidgetMap[MenuType]!=NULL)
			MenuWidgetMap[MenuType]->ShowWidget();
		MenuWidgetMap[MenuType]->ShowWidget();
	}*/
}

void UUIManagerVR::HideMenu(EMenusVR MenuType)
{/*
	FString str= FString::Printf(TEXT("ADisplayManager::GetInstance()->vr : %d"), ADisplayManager::GetInstance()->vr);
	GEngine->AddOnScreenDebugMessage(0,10,FColor::Black, str);
	if (!ADisplayManager::GetInstance()->vr)
		return;
	if (MenuWidgetMap.Contains(MenuType)) {
		MenuWidgetMap[MenuType]->HideWidget();
	}*/
}