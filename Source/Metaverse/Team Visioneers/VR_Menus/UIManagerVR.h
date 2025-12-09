// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "VRShortcutToolbar.h"
#include "Components/WidgetComponent.h"
#include "../../Public/AppConstEnumStruct.h"
#include "UIManagerVR.generated.h"


//class UVRMainMenu;
//class UVRShortcutToolbar;
class AVRWidgetActor;

UCLASS()
class METAVERSE_API UUIManagerVR : public UObject
{
	GENERATED_BODY()
public:
	static UUIManagerVR* GetInstance();
	void Initialize();
	void CreateMenu(EMenusVR MenuType);
	void ShowMenu(EMenusVR MenuType);
	void HideMenu(EMenusVR MenuType);
	void SetWorld(UWorld* world) { World = world; }
	void RegisterMenuPath(EMenusVR MenuType, const TCHAR* ClassPath);
	void UpdateFPS(int fps);
private:
	UUIManagerVR();
	static UUIManagerVR* UIManagerVRInstance;
protected:
	int ZOrder = 0;
	TSubclassOf<AVRWidgetActor> VRWidgetActorClass;
	UVRShortcutToolbar* Toolbar = nullptr;
	UPROPERTY()
	TMap<EMenusVR, TWeakObjectPtr<AVRWidgetActor>> MenuWidgetMap;
	UPROPERTY()
	TMap<EMenusVR, TSubclassOf<UUserWidget>> WidgetClassMap;

	FVector TargetPos;
	FVector PreviousPos;

	UWorld* World;

};
