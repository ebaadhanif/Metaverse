#include "VRMapLayers.h"


void UVRMapLayers::NativeConstruct()
{
	if (BorderButton)
	{
		BorderButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		BorderButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		BorderButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsBorders, ImageBorderToggle);
		BorderButton->OnClicked.Clear();
		BorderButton->OnClicked.AddUniqueDynamic(this, &UVRMapLayers::OnBorderButtonClick);
	}
	if (CitiesButton)
	{
		CitiesButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		CitiesButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		CitiesButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsPakCities, ImageCitiesToggle);
		CitiesButton->OnClicked.Clear();
		CitiesButton->OnClicked.AddUniqueDynamic(this, &UVRMapLayers::OnCitiesButtonClick);
	}
	if (BasesButton)
	{
		BasesButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		BasesButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		BasesButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsPakBases, ImageBasesToggle);
		BasesButton->OnClicked.Clear();
		BasesButton->OnClicked.AddUniqueDynamic(this, &UVRMapLayers::OnBasesButtonClick);
	}
	if (TownsButton)
	{
		TownsButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		TownsButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		TownsButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTowns, ImageTownsToggle);
		TownsButton->OnClicked.Clear();
		TownsButton->OnClicked.AddUniqueDynamic(this, &UVRMapLayers::OnTownsButtonClick);
	}
	if (InternationalBorderButton)
	{
		InternationalBorderButton->SetClickMethod(EButtonClickMethod::PreciseClick);
		InternationalBorderButton->SetPressMethod(EButtonPressMethod::ButtonPress);
		InternationalBorderButton->SetTouchMethod(EButtonTouchMethod::DownAndUp);
		UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsToggleBorder, ImageIntBorderToggle);
		InternationalBorderButton->OnClicked.Clear();
		InternationalBorderButton->OnClicked.AddUniqueDynamic(this, &UVRMapLayers::OnInternationalBorderButtonClick);
	}
	if (BackButton)
	{
		BackButton->OnClicked.Clear();
		BackButton->OnClicked.AddUniqueDynamic(this, &UVRMapLayers::OnBackButtonClick);
	}
	if (HomeButton)
	{
		HomeButton->OnClicked.Clear();
		HomeButton->OnClicked.AddUniqueDynamic(this, &UVRMapLayers::OnHomeButtonClick);
	}

}

void UVRMapLayers::OnBorderButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::ToggleBorder);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsBorders, ImageBorderToggle);
}

void UVRMapLayers::OnCitiesButtonClick()
{
	bool Pakstate = UIManager::GetInstance()->ButtonSates.bIsPakCities;
	bool Indstate = UIManager::GetInstance()->ButtonSates.bIsIndCities;
	if (Pakstate && Indstate)
	{
		UpdateVisual(false, ImageCitiesToggle);
	}
	else
	{
		UpdateVisual(true, ImageCitiesToggle);
	}
	UIManager::GetInstance()->SetState(EButtonsName::PakCities);
	UIManager::GetInstance()->SetState(EButtonsName::IndCities);
}


void UVRMapLayers::OnBasesButtonClick()
{
	bool Pakstate = UIManager::GetInstance()->ButtonSates.bIsPakBases;
	bool Indstate = UIManager::GetInstance()->ButtonSates.bIsIndBases;
	if (Pakstate && Indstate)
	{
		UpdateVisual(false ,ImageBasesToggle);

	}
	else
	{
		UpdateVisual(true ,ImageBasesToggle);

	}

	UIManager::GetInstance()->SetState(EButtonsName::PakBases);
	UIManager::GetInstance()->SetState(EButtonsName::IndBases);
}

void UVRMapLayers::OnTownsButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::Towns);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsTowns, ImageTownsToggle);
}

void UVRMapLayers::OnInternationalBorderButtonClick()
{
	UIManager::GetInstance()->SetState(EButtonsName::InternationalBorder);
	UpdateVisual(UIManager::GetInstance()->ButtonSates.bIsToggleBorder, ImageIntBorderToggle);
}

void UVRMapLayers::OnBackButtonClick()
{
	BackButtonClick();
}

void UVRMapLayers::OnHomeButtonClick()
{
	HomeButtonClick();
}
