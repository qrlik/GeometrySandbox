// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseGeometryActor.h"
#include "GeometryHubActor.generated.h"

USTRUCT(BlueprintType)
struct FGeometryPayload {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> Class;

	UPROPERTY(EditAnywhere)
	FGeometryData Data;

	UPROPERTY(EditAnywhere)
	FTransform Transform;
};

UCLASS()
class GEOMETRYSANDBOX_API AGeometryHubActor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGeometryHubActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void DoActorSpawn1() const;
	void DoActorSpawn2() const;
	void DoActorSpawn3();
	void DoActorSpawn4();

	UFUNCTION()
	void OnColorChanged(const FLinearColor& Color, const FString& Name);
	void OnTimerFinished(AActor* Actor) const;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABaseGeometryActor> GeometryActor;

	UPROPERTY(EditAnywhere)
	TArray<FGeometryPayload> Payloads;

	UPROPERTY()
	ABaseGeometryActor* PropertyActor;

	ABaseGeometryActor* NonePropertyActor;

	TWeakObjectPtr<ABaseGeometryActor> WeakActor;
};
