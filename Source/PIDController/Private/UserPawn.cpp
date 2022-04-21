// Fill out your copyright notice in the Description page of Project Settings.


#include "UserPawn.h"
#include "Kismet/GameplayStatics.h"
#include "BallBase.h"

// Sets default values
AUserPawn::AUserPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Ball = Cast<ABallBase>(UGameplayStatics::GetActorOfClass(this, ABallBase::StaticClass()));


	MaxForce = 100000.0f;

	TargetHight = 130.f;
	CurrentHight = 0.f;
	ForceApply = 0.f;

	ErrorP = 0.f;
	ErrorI = 0.f;
	ErrorD = 0.f;

	FrameCounter = 0;

	Kp = 0.1f;
	Ki = 0.01f;
	Kd = 0.2f;
}

// Called when the game starts or when spawned
void AUserPawn::BeginPlay()
{
	Super::BeginPlay();

	ErrorP = TargetHight - Ball->GetActorLocation().Z;
	ErrorI += ErrorP;
	ErrorD = ErrorP;
}

// Called every frame
void AUserPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AutoPIDControl();
	CurrentHight = Ball->GetActorLocation().Z;
}

// Called to bind functionality to input
void AUserPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("AddForce"), this, &AUserPawn::GiveForce);
}

void AUserPawn::GetPIDError()
{
}

void AUserPawn::AutoPIDControl()
{
	if(++FrameCounter == 6)
	{
		ErrorD = (TargetHight - Ball->GetActorLocation().Z) - ErrorP;
		ErrorP = TargetHight - Ball->GetActorLocation().Z;
		ErrorI = 0.999 * ErrorI + ErrorP;
		FrameCounter = 0;
	}
	ForceApply = Kp * ErrorP + Ki * ErrorI + Kd * ErrorD;
	GiveForce(ForceApply);
}

void AUserPawn::GiveForce(float Value)
{
	Ball->AddForce(Value * MaxForce);
}
