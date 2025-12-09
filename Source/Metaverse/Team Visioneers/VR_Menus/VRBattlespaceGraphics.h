#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VRMenuParent.h"
#include "..\Source\Metaverse\Team RenderStorm\TrailController.h"
#include "VRBattlespaceGraphics.generated.h"

/**
 * 
 */
UCLASS()
class METAVERSE_API UVRBattlespaceGraphics : public UVRMenuParent
{
	GENERATED_BODY()

public:
	 virtual void NativeConstruct() override;
	
protected:
	 bool bUpdatingLocklineUI = false;
	 UPROPERTY(meta = (BindWidget))
	 UButton* EntityVisualsButton;
	 UPROPERTY(meta = (BindWidget))
	 UButton* EntityLabelButton;
	 UPROPERTY(meta = (BindWidget))
	 UButton* LockLinesButton;
	 UPROPERTY(meta = (BindWidget))
	 UButton* CoveragesButton;
	 UPROPERTY(meta = (BindWidget))
	 UButton* TrailsButton;
	 UPROPERTY(meta = (BindWidget))
	 UButton* HeadingVectorButton;
	 UPROPERTY(meta = (BindWidget))
	 UButton* HeightVectorButton;
	 UPROPERTY(meta = (BindWidget))
	 UButton* RotationUpButton;
	 UPROPERTY(meta = (BindWidget))
	 UButton* DrawingsButton;
	 UPROPERTY(meta = (BindWidget))
	 UButton* BackButton;
	 UPROPERTY(meta = (BindWidget))
	 UButton* HomeButton;
	 UPROPERTY(meta = (BindWidget))
	 UImage* ImageLocklinesToggle;
	 UPROPERTY(meta = (BindWidget))
	 UImage* ImageCoveragesToggle;
	 UPROPERTY(meta = (BindWidget))
	 UImage* ImageHeadingToggle;
	 UPROPERTY(meta = (BindWidget))
	 UImage* ImageHeightToggle;
	 UPROPERTY(meta = (BindWidget))
	 UImage* ImageUpToggle;
private:
	 UFUNCTION()
	 void OnEntityVisualsButtonClick();
	 UFUNCTION()
	 void OnEntityLabelButtonClick();	 
	 UFUNCTION()
	 void OnLockLinesButtonClick();
	 UFUNCTION()
	 void OnCoveragesButtonClick();
	 UFUNCTION()
	 void OnTrailsButtonClick();
	 UFUNCTION()
	 void OnHeadingVectorButtonClick();
	 UFUNCTION()
	 void OnHeightVectorButtonClick();
	 UFUNCTION()
	 void OnRotationUpButtonClick();
	 UFUNCTION()
	 void OnDrawingsButtonClick();
	 UFUNCTION()
	 void OnBackButtonClick();
	 UFUNCTION()
	 void OnHomeButtonClick();

	 UPROPERTY()
	 ATrailController* trailController;
};
