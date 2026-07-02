// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstPersonShooterGameMode.generated.h"

/**
 *  Simple GameMode for a first person game
 */
UCLASS(abstract)
class AFirstPersonShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFirstPersonShooterGameMode();
};



