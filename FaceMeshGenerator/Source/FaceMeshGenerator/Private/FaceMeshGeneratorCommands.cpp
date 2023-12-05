// Copyright Epic Games, Inc. All Rights Reserved.

#include "FaceMeshGeneratorCommands.h"

#define LOCTEXT_NAMESPACE "FFaceMeshGeneratorModule"

void FFaceMeshGeneratorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "FaceMeshGenerator", "Bring up FaceMeshGenerator window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
