// Copyright Epic Games, Inc. All Rights Reserved.

#include "FaceMeshGeneratorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Framework/Application/SlateApplication.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FFaceMeshGeneratorStyle::StyleInstance = nullptr;

void FFaceMeshGeneratorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FFaceMeshGeneratorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FFaceMeshGeneratorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("FaceMeshGeneratorStyle"));
	return StyleSetName;
}

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FFaceMeshGeneratorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("FaceMeshGeneratorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("FaceMeshGenerator")->GetBaseDir() / TEXT("Resources"));

	Style->Set("FaceMeshGenerator.OpenPluginWindow", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));

	return Style;
}

void FFaceMeshGeneratorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FFaceMeshGeneratorStyle::Get()
{
	return *StyleInstance;
}
