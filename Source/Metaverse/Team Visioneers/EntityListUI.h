// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/EditableText.h"
#include "Components/SizeBox.h"
#include "Components/VerticalBox.h"
#include "Menus/ListDropDown.h"
#include "EntityListUI.generated.h"

class UScrollBox;
class UButton;
class UTextBlock;
class ACameraActor;
class AFreeCameraPawn;
class AEntityBase;

/**
 *
 */
UCLASS()
class METAVERSE_API UEntityListUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void AddEntityCallsignTolist(AEntityBase* entity);
	void RemoveEntityCallsignFromList(AEntityBase* entity);
	void SelectEntity(AEntityBase* entity);
	void SearchEntityList(const FString& SearchTerm);
	UFUNCTION(BlueprintCallable)
	void SetListVisibility(bool bVisibile);
	UListDropDown* DropDown;
private:
	UFUNCTION()
	void OnEntityButtonClick();
	UFUNCTION(BlueprintCallable, Category = "Search")
	void OnSearchTextChanged(const FText& SearchText);

	TArray<AEntityBase*> entities;
	FString CurrentSearchQuery;
protected:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* EntityScrollBox = nullptr;
	//UPROPERTY(meta = (BindWidget))
	//UVerticalBox* VerticalBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UEditableText* SearchTextBox = nullptr;

	UPROPERTY()
	TMap<UButton*, AEntityBase*> ButtonToEntityMap;

	UButton* EntityButton = nullptr;
	UTextBlock* Label = nullptr;

};
