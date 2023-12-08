// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SandboxPawn.generated.h"

UCLASS()
class GEOMETRYSANDBOX_API ASandboxPawn : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASandboxPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere)
	float Velocity = 300.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveForward(float Amount);
	void MoveSide(float Amount);

	FVector VelocityVector = FVector::ZeroVector;
};
