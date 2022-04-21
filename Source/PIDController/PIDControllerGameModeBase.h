// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include <fstream>
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PIDControllerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PIDCONTROLLER_API APIDControllerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	APIDControllerGameModeBase();
	
protected:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	AActor* Ball;
	FString Path;
	class AUserPawn* Pawn;
	// ofstream FileStream;

public:
	void OpenFile(FString* Path);
	void WriteFile(FString* Path);

};
