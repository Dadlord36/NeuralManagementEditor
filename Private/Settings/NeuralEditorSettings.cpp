// Fill out your copyright notice in the Description page of Project Settings.


#include "Settings/NeuralEditorSettings.h"

#define LOCTEXT_NAMESPACE "NeuralEditor"

FName UNeuralEditorSettings::GetSectionName() const
{
	return "Neural Editor";
}

FText UNeuralEditorSettings::GetSectionDescription() const
{
	return LOCTEXT("NeuralEditor", "NeuralEditor related settings.");
}

TWeakObjectPtr<const USlateWidgetStyleAsset> UNeuralEditorSettings::LoadAndGetTexBlockStyleAsset(
	const TSoftObjectPtr<USlateWidgetStyleAsset>& Asset) const
{
	const auto Index = LoadedStyles.AddUnique(Asset.LoadSynchronous());
	checkf(LoadedStyles[Index], TEXT("Asset was not loaded for some reason"))
	return LoadedStyles[Index];
}

#undef LOCTEXT_NAMESPACE
