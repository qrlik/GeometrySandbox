// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseActor, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor(): 
	Mesh(CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh")) 
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay()
{
	Super::BeginPlay();

	//PrintStringTypes();

	InitialLocation = GetActorLocation();
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto CurrentLocation = GetActorLocation();
	CurrentLocation.Z = InitialLocation.Z + Amplitude * FMath::Sin(Frequency * GetWorld()->GetTimeSeconds());
	SetActorLocation(CurrentLocation);
}

void ABaseGeometryActor::PrintStringTypes() const
{
	UE_LOG(LogBaseActor, Display, TEXT("Name: %s"), *Name);
	const FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	const FString HealthStr = "Health num = " + FString::SanitizeFloat(Health);
	const FString IsDeadStr = "isDead = " + FString((IsDead) ? "True" : "False");

	const FString Stat = FString::Printf(TEXT(" \n == All Stats == \n %s \n %s \n %s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, Name);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Stat, true, FVector2D{ 1.5f, 1.5f });
}
