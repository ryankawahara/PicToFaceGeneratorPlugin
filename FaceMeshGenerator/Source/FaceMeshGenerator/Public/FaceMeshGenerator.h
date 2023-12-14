// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "SelectionPanel.h"
#include "Widgets/Text/SMultiLineEditableText.h"
#include "Widgets/Input/SMultiLineEditableTextBox.h"
#include "Widgets/Input/SCheckBox.h"


class FToolBarBuilder;
class FMenuBuilder;

class FFaceMeshGeneratorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void OnWorkerThreadComplete();


	void OnTaskCompleted();
	DECLARE_DELEGATE(FMyTaskCompletedDelegate);
	FMyTaskCompletedDelegate MyTaskCompletedDelegate;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	FReply ExecuteButtonClicked();
	
	TSharedPtr<SButton> ExecuteButton;
	TSharedPtr<SMultiLineEditableTextBox> ConsoleDisplay;
	TSharedPtr<SCheckBox> ImportTextureCheckbox;
	void UpdateUIFromMainThread(bool change);
	USelectionPanel* SelectionPanelObject;
	FString originalMeshName;


	
private:

	void RegisterMenus();

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

	USelectionPanel* SelectionPanel;
	TSharedPtr<class IDetailsView> PropertyWidget;



private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
