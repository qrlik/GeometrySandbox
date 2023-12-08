// Fill out your copyright notice in the Description page of Project Settings.

#include "SandboxPlayerController.h"

#include "SandboxPawn.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogSandboxPlayerController, All, All)

void ASandboxPlayerController::BeginPlay() {
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASandboxPawn::StaticClass(), Pawns);
}

void ASandboxPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	InputComponent->BindAction("ChangePawn", IE_Pressed, this, &ASandboxPlayerController::ChangePawn);
}

void ASandboxPlayerController::ChangePawn() {
	if (Pawns.Num() < 2) {
		return;
	}
	const auto CurrentPawn = Cast<APawn>(Pawns[PawnIndex]);
	PawnIndex = (PawnIndex + 1) % Pawns.Num();

	if (!CurrentPawn || GetPawn() == CurrentPawn) {
		return;
	}
	Possess(CurrentPawn);
	UE_LOG(LogSandboxPlayerController, Error, TEXT("Change Player Pawn"));
}
