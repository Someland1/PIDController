// Copyright Epic Games, Inc. All Rights Reserved.


#include "PIDControllerGameModeBase.h"
#include "BallBase.h"
#include "UserPawn.h"
#include "Kismet/GameplayStatics.h"

using namespace std;

APIDControllerGameModeBase::APIDControllerGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Ball = UGameplayStatics::GetActorOfClass(this, ABallBase::StaticClass());
	
}

void APIDControllerGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	Path = FPaths::GameSourceDir();
	Path += "file.txt";
	FFileHelper::SaveStringToFile(TEXT(""), *Path);
}

void APIDControllerGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	Pawn = Cast<AUserPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void APIDControllerGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Ball && Pawn)
	{
		FString BallHight = FString::SanitizeFloat(Ball->GetActorLocation().Z);
		FString TargetHight = FString::SanitizeFloat(Pawn->TargetHight);
		FString CurrentForce = FString::SanitizeFloat(Pawn->ForceApply);
		FFileHelper::SaveStringToFile(BallHight + "\t" + TargetHight + "\t" + CurrentForce + "\n", *Path, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Ball or Pawn cannot found."));
}