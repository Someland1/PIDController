// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBase.h"
#include "Components/SphereComponent.h"

// Sets default values
ABallBase::ABallBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set properties of root component (sphere component)
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));

	if (!SetRootComponent(SphereComp)) { UE_LOG(LogTemp, Warning, TEXT("Root Component Set Failed!~")); return; };
	SphereComp->SetSimulatePhysics(true);
	SphereComp->SetCollisionProfileName(TEXT("BlockAll"));

	// Set properities of Static Mesh Component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	if (!MeshComp) { UE_LOG(LogTemp, Warning, TEXT("Static Mesh Component set failed!~")); return; };
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetRelativeScale3D(FVector::OneVector * 0.6f);

}

// Called when the game starts or when spawned
void ABallBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABallBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallBase::AddForce(float Force)
{
	// This function should only be used in Tick function.
	// The physic system is follow the engine time, not real world time.
	SphereComp->AddForce(FVector::UpVector * Force);
}
