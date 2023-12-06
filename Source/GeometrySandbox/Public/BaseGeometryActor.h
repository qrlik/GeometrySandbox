// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "BaseGeometryActor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTimerFinished, AActor*);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnColorChange, const FLinearColor&, Color, const FString&, Name);

UENUM(BlueprintType)
enum class EMovementType : uint8 { Sin = 0, Static = 1 };

USTRUCT(BlueprintType)
struct FGeometryData {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement")
	float Amplitude = 50.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement")
	float Frequency = 2.f;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Movement")
	EMovementType MovementType = EMovementType::Static;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Design")
	FLinearColor Color = FLinearColor::Black;

	UPROPERTY(EditInstanceOnly, Category = "Design")
	float TimerRate = 1.f;
};

UCLASS()
class GEOMETRYSANDBOX_API ABaseGeometryActor : public AActor {
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseGeometryActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintCallable)
	void SetGeometryData(const FGeometryData& Data) { GeometryData = Data; }

	UFUNCTION(BlueprintCallable)
	const FGeometryData& GetGeometryData() const { return GeometryData; }

	FOnTimerFinished OnTimerFinished;
	UPROPERTY(BlueprintAssignable)
	FOnColorChange OnColorChange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void PrintStringTypes() const;
	void ProcessMovement();
	void SetColor(const FLinearColor& Color) const;
	void OnTimerFired();

	FVector InitialLocation;
	FTimerHandle TimerHandle;
	int32 MaxTimerCount = 5;
	int32 TimerCount = 0;

	UPROPERTY(EditInstanceOnly, Category = "Geometry")
	FGeometryData GeometryData;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

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
