// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFloater::AFloater()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitLocation = FVector(0.0f);
	PlacedLocation = FVector(0.0f);
	WorldOrigin = FVector(0.0f);
	InitialDirection = FVector(0.0f);
	bInitializeFloaterLocations = false;
	bShouldFloat = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Custom static mesh"));
	InitialForce = FVector(20000000.f, 0.0f, 0.0f);
	InitialTorque = FVector(20000000.f, 0.0f, 0.0f);
	RunningTime = 0.0f;
	BaseZLocation = 0.0f;
	A = 0.f;
	B = 0.f;
	C = 0.f;
	D = 0.f;
}

// Called when the game starts or when spawned
void AFloater::BeginPlay()
{
	Super::BeginPlay();
	PlacedLocation = GetActorLocation();
	BaseZLocation = PlacedLocation.Z;

	float initialX = FMath::FRand() * 10000000;
	float initialY = FMath::FRand() * 10000000;
	float initialZ = FMath::FRand() * 10000000;

	if (bInitializeFloaterLocations) {
		SetActorLocation(InitLocation);
	}

	//StaticMesh->AddForce(FVector(initialX, initialY, initialZ));
	//StaticMesh->AddTorqueInRadians(InitialTorque);
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldFloat) {
		FVector NewLocation = GetActorLocation();

		NewLocation.Z = BaseZLocation + A * FMath::Sin(B * RunningTime - C) + D;

		SetActorLocation(NewLocation);
		RunningTime += DeltaTime;
	}
}

