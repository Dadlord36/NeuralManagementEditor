// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "NeuralEditorSettings.generated.h"

/**
 * 
 */
UCLASS(config = NeuralEditor, defaultconfig, meta=(DisplayName = "NeuralEditor"))
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

	TWeakObjectPtr<const USlateWidgetStyleAsset> GetMenuEntryTextStyleSize() const
	{
		return LoadAndGetTexBlockStyleAsset(MenuEntryTextStyleSize);
	}

	virtual FName GetCategoryName() const override
	{
		return TEXT("Plugins");
	}

	virtual FName GetContainerName() const override
	{
		return TEXT("Project");
	}
	
	virtual FName GetSectionName() const override;
	virtual FText GetSectionDescription() const override;

private:
	TWeakObjectPtr<const USlateWidgetStyleAsset> LoadAndGetTexBlockStyleAsset(const TSoftObjectPtr<USlateWidgetStyleAsset>& Asset) const;

private:
	UPROPERTY(Config, EditAnywhere, Category = "Overtone")
	TSoftObjectPtr<USlateWidgetStyleAsset> HeaderTextStyleTitle;
	UPROPERTY(Config, EditAnywhere, Category = "Overtone")
	TSoftObjectPtr<USlateWidgetStyleAsset> HeaderTextStyleRoot;
	UPROPERTY(Config, EditAnywhere, Category = "Overtone")
	TSoftObjectPtr<USlateWidgetStyleAsset> HeaderTextStyleSubroot;
	UPROPERTY(Config, EditAnywhere, Category = "Overtone")
	TSoftObjectPtr<USlateWidgetStyleAsset> MenuEntryTextStyleFunction;
	UPROPERTY(Config, EditAnywhere, Category = "Overtone")
	TSoftObjectPtr<USlateWidgetStyleAsset> MenuEntryTextStyleName;
	UPROPERTY(Config, EditAnywhere, Category = "Overtone")
	TSoftObjectPtr<USlateWidgetStyleAsset> MenuEntryTextStyleSize;

	UPROPERTY(Transient)
	mutable TArray<TObjectPtr<USlateWidgetStyleAsset>> LoadedStyles;
};
