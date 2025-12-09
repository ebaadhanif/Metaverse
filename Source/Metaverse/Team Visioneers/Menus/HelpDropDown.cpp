// Fill out your copyright notice in the Description page of Project Settings.


#include "HelpDropDown.h"
#include "UIManager.h"

void UHelpDropDown::NativeConstruct()
{
	MenuDepth = 1;

	if (UsersGuideButton)
	{
		UsersGuideButton->OnClicked.Clear();
		UsersGuideButton->OnClicked.AddUniqueDynamic(this, &UHelpDropDown::OnGuideButtonClick);
	}
	if (AboutUsButton)
	{
		AboutUsButton->OnClicked.Clear();
		AboutUsButton->OnClicked.AddUniqueDynamic(this, &UHelpDropDown::OnAboutUsButtonClick);
	}
}
void UHelpDropDown::OnGuideButtonClick()
{
}
void UHelpDropDown::OnAboutUsButtonClick()
{
}


