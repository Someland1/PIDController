// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UserPawn.generated.h"

UCLASS()
class PIDCONTROLLER_API AUserPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUserPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
		class ABallBase* Ball;
	UPROPERTY(EditAnywhere)
		float MaxForce;

	UPROPERTY(EditAnywhere)
		float TargetHight;
	UPROPERTY(VisibleAnywhere)
		float CurrentHight;
	UPROPERTY(VisibleAnywhere)
		float ForceApply;

	// Use to store errors;
	UPROPERTY(VisibleAnywhere)
		float ErrorP;
	UPROPERTY(VisibleAnywhere)
		float ErrorI;
	UPROPERTY(VisibleAnywhere)
		float ErrorD;

	// Use to store gain values;
	UPROPERTY(EditAnywhere)
		float Kp;
	UPROPERTY(EditAnywhere)
		float Ki;
	UPROPERTY(EditAnywhere)
		float Kd;

	int32 FrameCounter;

	// Set errors at current frame
	void GetPIDError();

	// Control location based on PID algorithm.
	void AutoPIDControl();

	// Give force with value
	void GiveForce(float Value);
};
