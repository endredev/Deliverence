// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class DELIVERANCE_API AFloater : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloater();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Actor Mesh Components")
		UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Float Variables")
		FVector InitLocation;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Float Variables")
		FVector PlacedLocation;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Float Variables")
		FVector WorldOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Float Variables")
		FVector InitialDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Float Variables")
		bool bShouldFloat;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Float Variables")
		bool bInitializeFloaterLocations;

	UPROPERTY(EditInstanceOnly, Category = "Float Variables")
		FVector InitialForce;

	UPROPERTY(EditInstanceOnly, Category = "Float Variables")
		FVector InitialTorque;

private:
	float RunningTime;
	float BaseZLocation;

	UPROPERTY(EditAnywhere, Category = "Float Variables")
		float A; // Amplitude
	UPROPERTY(EditAnywhere, Category = "Float Variables")
		float B; // Period
	UPROPERTY(EditAnywhere, Category = "Float Variables")
		float C; // Phase Shift
	UPROPERTY(EditAnywhere, Category = "Float Variables")
		float D; // Vertical Shift

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};