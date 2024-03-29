// Fill out your copyright notice in the Description page of Project Settings.

#include "Collider.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ColliderMovementComponent.h"

// Sets default values
ACollider::ACollider()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->SetupAttachment(GetRootComponent());
	SphereComponent->InitSphereRadius(40.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	if (StaticMesh.Succeeded()) {
		MeshComponent->SetStaticMesh(StaticMesh.Object);
		MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
		MeshComponent->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	}

	AutoPossessPlayer = EAutoReceiveInput::Player0;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	CustomMovementComponent = CreateDefaultSubobject<UColliderMovementComponent>(TEXT("CustomMovementComponent"));
	CustomMovementComponent->UpdatedComponent = RootComponent;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CameraInput = FVector2D(0.f);
}

// Called when the game starts or when spawned
void ACollider::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	FRotator NewSpringArmRotation = SpringArm->GetComponentRotation();
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch += CameraInput.Y, -80.f, -15.f);
	SpringArm->SetWorldRotation(NewSpringArmRotation);
}

// Called to bind functionality to input
void ACollider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACollider::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRIght"), this, &ACollider::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &ACollider::PitchCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &ACollider::YawCamera);
}

void ACollider::MoveForward(float input) {
	FVector Forward = GetActorForwardVector();
	AddMovementInput(input * Forward);

	if (CustomMovementComponent) {
		CustomMovementComponent->AddInputVector(Forward * input);
	}
}

void ACollider::MoveRight(float input) {
	FVector Right = GetActorRightVector();
	AddMovementInput(input * Right);

	if (CustomMovementComponent) {
		CustomMovementComponent->AddInputVector(Right * input);
	}
}

void ACollider::PitchCamera(float input) {
	CameraInput.Y = input;
}

void ACollider::YawCamera(float input) {
	CameraInput.X = input;
}

UPawnMovementComponent* ACollider::GetMovementComponent() const {
	return CustomMovementComponent;
}
