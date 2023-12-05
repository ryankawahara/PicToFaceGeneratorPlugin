// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "FaceMeshGeneratorStyle.h"

class FFaceMeshGeneratorCommands : public TCommands<FFaceMeshGeneratorCommands>
{
public:

	FFaceMeshGeneratorCommands()
		: TCommands<FFaceMeshGeneratorCommands>(TEXT("FaceMeshGenerator"), NSLOCTEXT("Contexts", "FaceMeshGenerator", "FaceMeshGenerator Plugin"), NAME_None, FFaceMeshGeneratorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};