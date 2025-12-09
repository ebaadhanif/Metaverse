#include "VRBattlespaceGraphics.h"
#include "Kismet/GameplayStatics.h"
#include "DWGXDrawingManager.h"
#include "../DisplayManager.h"
#include "../../Team RenderStorm/TrailController.h"
#include "../../Team RenderStorm/RibbonMeshActor.h"
#include "../../Team RenderStorm/VerticalRibbonMeshActor.h"
#include "../../Team RenderStorm/GroundVectorActor.h"
#include "../../Team RenderStorm/ForwardVectorActor.h"
#include "../../Team SimBridge/EntityManager.h"
#include "../../Team SimBridge/EntityBase.h"

void UVRBattlespaceGraphics::NativeConstruct()
{
	 if (EntityVisualsButton)
	 {
	 	 EntityVisualsButton->OnClicked.Clear();
	 	 EntityVisualsButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnEntityVisualsButtonClick);
	 }
	 if (EntityLabelButton)
	 {
	 	 EntityLabelButton->OnClicked.Clear();
	 	 EntityLabelButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnEntityLabelButtonClick);
	 }
	 if (LockLinesButton)
	 {
		 LockLinesButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		 LockLinesButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		 LockLinesButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		 UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsAllLocklines, ImageLocklinesToggle);
	 	 LockLinesButton->OnClicked.Clear();
	 	 LockLinesButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnLockLinesButtonClick);
	 }
	 if (CoveragesButton)
	 {
		 CoveragesButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		 CoveragesButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		 CoveragesButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		 UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsGroundCoverages, ImageCoveragesToggle);
	 	 CoveragesButton->OnClicked.Clear();
	 	 CoveragesButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnCoveragesButtonClick);
	 }
	 if (TrailsButton)
	 {
	 	 TrailsButton->OnClicked.Clear();
	 	 TrailsButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnTrailsButtonClick);
	 }
	 if (HeadingVectorButton)
	 {
		 HeadingVectorButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		 HeadingVectorButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		 HeadingVectorButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		 UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsHeadingVector, ImageHeadingToggle);
	 	 HeadingVectorButton->OnClicked.Clear();
	 	 HeadingVectorButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnHeadingVectorButtonClick);
	 }
	 if (HeightVectorButton)
	 {
		 HeightVectorButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		 HeightVectorButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		 HeightVectorButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		 UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsDownVector, ImageHeightToggle);
	 	 HeightVectorButton->OnClicked.Clear();
	 	 HeightVectorButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnHeightVectorButtonClick);
	 }
	 if (RotationUpButton)
	 {
		 RotationUpButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		 RotationUpButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		 RotationUpButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		 UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsUpVector, ImageUpToggle);
	 	 RotationUpButton->OnClicked.Clear();
	 	 RotationUpButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnRotationUpButtonClick);
	 }
	 if (DrawingsButton)
	 {
	 	 DrawingsButton->OnClicked.Clear();
	 	 DrawingsButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnDrawingsButtonClick);
	 }
	 if (BackButton)
	 {
	 	 BackButton->OnClicked.Clear();
	 	 BackButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnBackButtonClick);
	 }
	 if (HomeButton)
	 {
	 	 HomeButton->OnClicked.Clear();
	 	 HomeButton->OnClicked.AddUniqueDynamic(this, &UVRBattlespaceGraphics::OnHomeButtonClick);
	 }

}

void UVRBattlespaceGraphics::OnEntityVisualsButtonClick()
{
	 WidgetHandling(EMenusVR::EntityVisuals);
}

void UVRBattlespaceGraphics::OnEntityLabelButtonClick()
{
	 WidgetHandling(EMenusVR::EntityLabels);
}


void UVRBattlespaceGraphics::OnLockLinesButtonClick()
{
	 UIManager::GetInstance()->SetState(EButtonsName::AllLocklines);
	 UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsAllLocklines, ImageLocklinesToggle);
	 
}

void UVRBattlespaceGraphics::OnCoveragesButtonClick()
{
	 UIManager::GetInstance()->SetState(EButtonsName::GroundCoverages);
	 UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsGroundCoverages, ImageCoveragesToggle);
}

void UVRBattlespaceGraphics::OnTrailsButtonClick()
{
	 WidgetHandling(EMenusVR::Trails);
}

void UVRBattlespaceGraphics::OnHeadingVectorButtonClick()
{
	 UIManager::GetInstance()->SetState(EButtonsName::HeadingVector);
	 UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsHeadingVector, ImageHeadingToggle);
}

void UVRBattlespaceGraphics::OnHeightVectorButtonClick()
{
	 UIManager::GetInstance()->SetState(EButtonsName::DownVector);
	 UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsDownVector, ImageHeightToggle);
}

void UVRBattlespaceGraphics::OnRotationUpButtonClick()
{
	 UIManager::GetInstance()->SetState(EButtonsName::UpVector);
	 UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsUpVector, ImageUpToggle);
}

void UVRBattlespaceGraphics::OnDrawingsButtonClick()
{
	 WidgetHandling(EMenusVR::Drawings);
}

void UVRBattlespaceGraphics::OnBackButtonClick()
{
	 BackButtonClick();
}

void UVRBattlespaceGraphics::OnHomeButtonClick()
{
	 HomeButtonClick();
}