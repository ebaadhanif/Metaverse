// Class Added by Ebaad, This class deals with Menu on Main Window of game 


#include "MetaverseHUD.h"
//#include "../Team Visioneers/ConfigMenuWidget.h"
#include "Blueprint/UserWidget.h"


void AMetaverseHUD::BeginPlay()
{
    Super::BeginPlay();

	if (TopBarMenuClass)
	{
		TopBarMenuWidget = CreateWidget<UUserWidget>(GetWorld(), TopBarMenuClass);
		if (TopBarMenuWidget)
		{
			if (EntityListClass)
			{
				EntityListWidget = Cast<UEntityListUI>(CreateWidget<UUserWidget>(GetWorld(), EntityListClass));

			}
			//TopBarMenuWidget->AddToViewport();
			//TopBarMenuWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create TopBarMenuWidget!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TopBarMenuClass is not set in CustomHUD!"));
	}
}

void AMetaverseHUD::ToggleMenuButton()
{
    if (TopBarMenuWidget)
    {
        ESlateVisibility CurrentVisibility = TopBarMenuWidget->GetVisibility();
        TopBarMenuWidget->SetVisibility(
            CurrentVisibility == ESlateVisibility::Visible ? ESlateVisibility::Hidden : ESlateVisibility::Visible);



    }
}

AMetaverseHUD::AMetaverseHUD()
{

    //static ConstructorHelpers::FClassFinder<UConfigMenuWidget> WidgetBPClass(TEXT("/Game/Blueprints/BP_MyConfigMenuWidget"));

    //if (WidgetBPClass.Succeeded())
    //{
    //    TopBarMenuClass = WidgetBPClass.Class;
    //  
    //}
    //static ConstructorHelpers::FClassFinder<UEntityListUI> WidgetBPEntityList(TEXT("/Game/Blueprints/W_EntityListUI"));

    //if (WidgetBPEntityList.Succeeded())
    //{
    //    EntityListClass = WidgetBPEntityList.Class;
    //}
}
