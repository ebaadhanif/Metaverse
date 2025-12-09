#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "../Team Visioneers/EntityListUI.h"
//#include "../Team Visioneers/ConfigMenuWidget.h"
#include "MetaverseHUD.generated.h"


UCLASS()
class METAVERSE_API AMetaverseHUD : public AHUD
{
	GENERATED_BODY()
public:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> TopBarMenuClass;
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> EntityListClass;
public:
    UUserWidget* TopBarMenuWidget;
    UEntityListUI* EntityListWidget;

    void ToggleMenuButton();

    AMetaverseHUD();
};
