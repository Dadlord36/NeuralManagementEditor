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
	return Asset.LoadSynchronous();
}

TWeakObjectPtr<const USlateWidgetStyleAsset> UNeuralEditorSettings::LoadAndGetTexBlockStyleAsset(const FSoftObjectPath& Asset) const
{
	UObject* LoadedAsset = Asset.ResolveObject();
	if (LoadedAsset == nullptr)
	{
		LoadedAsset = Asset.TryLoad();
	}

	const USlateWidgetStyleAsset* SlateAsset = Cast<USlateWidgetStyleAsset>(LoadedAsset);
	if (SlateAsset == nullptr)
	{
		// Log an error
		UE_LOG(LogTemp, Error, TEXT("Asset could not be loaded or is not a USlateWidgetStyleAsset"));
		return nullptr;
	}

	return MakeWeakObjectPtr(SlateAsset);
}

#undef LOCTEXT_NAMESPACE
