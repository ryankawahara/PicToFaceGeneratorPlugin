// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include <filesystem>
#include "Async/Async.h"
#include "FaceMeshGenerator.h"


class FACEMESHGENERATOR_API PluginRunnableThread : public FRunnable
{
public:
	DECLARE_DELEGATE(FOnThreadCompleted);
	FOnThreadCompleted OnThreadCompletedDelegate;

	void BindOnThreadCompleted(const FOnThreadCompleted& Callback);

	//PluginRunnableThread(const FString& Command);
	PluginRunnableThread(const FString& InMeshName, const FString& InExecute, const FDirectoryPath& InOutputPath, TSharedPtr<SButton> ExecuteButton, FFaceMeshGeneratorModule* InOwner);

	virtual ~PluginRunnableThread() override;

	bool Init() override; // Do your setup here, allocate memory, ect.
	bool bShouldStartThread;
	uint32 Run() override; // Main data processing happens here
	uint32 Start(); // Main data processing happens here

	void Stop() override; // Clean up any memory you allocated here
	void OnThreadCompleted();
	void WriteToWidgetConsole(const FString& text);
	void ClearWidgetConsole();
	FGraphEventRef CompletionTask;

	FString CommandToExecute;
	FString cropCommand;
	FString MeshName;
	FString pluginsPath;
	FDirectoryPath outputPath;
	TSharedPtr<SButton> button;
	FString execute;
	FFaceMeshGeneratorModule* owner;
	bool bIsThreadComplete = false;
	bool IsDone() const;

	bool bIsFinished;

	// Thread handle. Control the thread using this, with operators like Kill and Suspend
	FRunnableThread* Thread;

	// Used to know when the thread should exit, changed in Stop(), read in Run()
	bool bRunThread;

};
