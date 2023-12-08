// Fill out your copyright notice in the Description page of Project Settings.


#include "SandboxPawn.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPawn, All, All)

// Sets default values
ASandboxPawn::ASandboxPawn() {
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ASandboxPawn::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ASandboxPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (!VelocityVector.IsZero()) {
		const auto NewLocation = GetActorLocation() + Velocity * DeltaTime * VelocityVector;
		SetActorLocation(NewLocation);
		VelocityVector = VelocityVector.Zero();
	}
}

// Called to bind functionality to input
void ASandboxPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent) {
		PlayerInputComponent->BindAxis("MoveForward", this, &ASandboxPawn::MoveForward);
		PlayerInputComponent->BindAxis("MoveSide", this, &ASandboxPawn::MoveSide);
	}
}

void ASandboxPawn::MoveForward(float Amount) {
	UE_LOG(LogSandboxPawn, Display, TEXT("MoveForward - %f"), Amount);
	VelocityVector.X = Amount;
}

void ASandboxPawn::MoveSide(float Amount) {
	UE_LOG(LogSandboxPawn, Display, TEXT("MoveSide - %f"), Amount);
	VelocityVector.Y = Amount;
}
