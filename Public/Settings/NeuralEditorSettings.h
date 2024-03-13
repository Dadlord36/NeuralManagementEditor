// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "NeuralEditorSettings.generated.h"

/**
 * 
 */
UCLASS(config = NeuralEditor, meta=(DisplayName = "NeuralEditor"))
class NEURALMANAGEMENTEDITOR_API UNeuralEditorSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<const USlateWidgetStyleAsset> GetHeaderTitleTextStyle() const
	{
		return LoadAndGetTexBlockStyleAsset(HeaderTextStyleTitle);
	}

	// Implentation of the remaining getters
	TWeakObjectPtr<const USlateWidgetStyleAsset> GetHeaderTextStyleRoot() const
	{
		return LoadAndGetTexBlockStyleAsset(HeaderTextStyleRoot);
	}

	TWeakObjectPtr<const USlateWidgetStyleAsset> GetHeaderTextStyleSubroot() const
	{
		return LoadAndGetTexBlockStyleAsset(HeaderTextStyleSubroot);
	}

	TWeakObjectPtr<const USlateWidgetStyleAsset> GetMenuEntryTextStyleFunction() const
	{
		return LoadAndGetTexBlockStyleAsset(MenuEntryTextStyleFunction);
	}

	TWeakObjectPtr<const USlateWidgetStyleAsset> GetMenuEntryNameTextStyle() const
	{
		return LoadAndGetTexBlockStyleAsset(MenuEntryTextStyleName);
	}

	TWeakObjectPtr<const USlateWidgetStyleAsset> LoadAndGetTexBlockStyleAsset(const FSoftObjectPath& Asset) const;

	TWeakObjectPtr<const USlateWidgetStyleAsset> GetMenuEntryTextStyleSize() const
	{
		return LoadAndGetTexBlockStyleAsset(MenuEntryTextStyleSize);
	}

	virtual FName GetCategoryName() const override
	{
		return TEXT("Plugins");
	}

	virtual FName GetSectionName() const override;
	virtual FText GetSectionDescription() const override;

private:
	TWeakObjectPtr<const USlateWidgetStyleAsset> LoadAndGetTexBlockStyleAsset(const TSoftObjectPtr<USlateWidgetStyleAsset>& Asset) const;

private:
	UPROPERTY(VisibleAnywhere, Category = "Overtone")
	FSoftObjectPath HeaderTextStyleTitle = FSoftObjectPath("/Overtone/UI/Styles/SS_Text_HeaderStyle_Root.SS_Text_HeaderStyle_Root");
	UPROPERTY(VisibleAnywhere, Category = "Overtone")
	FSoftObjectPath HeaderTextStyleRoot = FSoftObjectPath("/Overtone/UI/Styles/SS_Text_HeaderStyle_Subroot.SS_Text_HeaderStyle_Subroot");
	UPROPERTY(VisibleAnywhere, Category = "Overtone")
	FSoftObjectPath HeaderTextStyleSubroot = FSoftObjectPath("/Overtone/UI/Styles/SS_Text_MenuEntry_Function.SS_Text_MenuEntry_Function");
	UPROPERTY(VisibleAnywhere, Category = "Overtone")
	FSoftObjectPath MenuEntryTextStyleFunction = FSoftObjectPath("/Overtone/UI/Styles/SS_Text_MenuEntry_Name.SS_Text_MenuEntry_Name");
	UPROPERTY(VisibleAnywhere, Category = "Overtone")
	FSoftObjectPath MenuEntryTextStyleName = FSoftObjectPath("/Overtone/UI/Styles/SS_Text_MenuEntry_Size.SS_Text_MenuEntry_Size");
	UPROPERTY(VisibleAnywhere, Category = "Overtone")
	FSoftObjectPath MenuEntryTextStyleSize = FSoftObjectPath("/Overtone/UI/Styles/SS_Text_Title.SS_Text_Title");
};
