// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "SelectionPanel.h"

class FToolBarBuilder;
class FMenuBuilder;

class FFaceMeshGeneratorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	FReply ExecuteButtonClicked();
	
	
private:

	void RegisterMenus();
	USelectionPanel* SelectionPanelObject;

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	USelectionPanel* SelectionPanel;
	TSharedPtr<class IDetailsView> PropertyWidget;


private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
