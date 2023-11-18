// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.generated.h"

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseGeometryActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void PrintStringTypes() const;

	UPROPERTY(EditAnywhere)
	FString Name = "John Connor";

	UPROPERTY(EditInstanceOnly, Category = "Weapon")
	int32 WeaponsNum = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Stat")
	int32 KillsNum = 7;

	UPROPERTY(EditAnywhere, Category = "Health")
	float Health = 34.4343123423;

	UPROPERTY(EditAnyWhere)
	bool IsDead = false;

	UPROPERTY(VisibleAnywhere)
	bool HasWeapon = false;
};
