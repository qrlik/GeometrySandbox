// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseGeometryActor.h"
#include "Engine.h"
#include "Materials/MaterialInstanceDynamic.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryActor, All, All)

// Sets default values
ABaseGeometryActor::ABaseGeometryActor():
	Mesh(CreateDefaultSubobject<UStaticMeshComponent>("BaseMesh")) {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ABaseGeometryActor::BeginPlay() {
	Super::BeginPlay();

	// PrintStringTypes();

	InitialLocation = GetActorLocation();
	SetColor(GeometryData.Color);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ABaseGeometryActor::OnTimerFired, GeometryData.TimerRate, true);
}

// Called every frame
void ABaseGeometryActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	ProcessMovement();
}

void ABaseGeometryActor::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	UE_LOG(LogGeometryActor, Warning, TEXT("Actor is dead %s"), *GetName())
	Super::EndPlay(EndPlayReason);
}

void ABaseGeometryActor::ProcessMovement() {
	switch (GeometryData.MovementType) {
		case EMovementType::Sin: {
			auto CurrentLocation = GetActorLocation();
			CurrentLocation.Z = InitialLocation.Z + GeometryData.Amplitude * FMath::Sin(GeometryData.Frequency * GetWorld()->GetTimeSeconds());
			SetActorLocation(CurrentLocation);
			break;
		}
		case EMovementType::Static:
		default:
			break;
	}
}

void ABaseGeometryActor::SetColor(const FLinearColor& Color) const {
	if (!Mesh) {
		return;
	}
	if (const auto Material = Mesh->CreateAndSetMaterialInstanceDynamic(0)) {
		Material->SetVectorParameterValue("Color", Color);
	}
}

void ABaseGeometryActor::OnTimerFired() {
	if (TimerCount < MaxTimerCount) {
		++TimerCount;
		const auto NewColor = FLinearColor::MakeRandomColor();
		SetColor(NewColor);
		OnColorChange.Broadcast(NewColor, GetName());
	}
	else if (TimerCount == MaxTimerCount) {
		GetWorldTimerManager().ClearTimer(TimerHandle);
		OnTimerFinished.Broadcast(this);
	}
}

void ABaseGeometryActor::PrintStringTypes() const {
	UE_LOG(LogGeometryActor, Display, TEXT("Name: %s"), *Name);
	const FString WeaponsNumStr = "Weapons num = " + FString::FromInt(WeaponsNum);
	const FString HealthStr = "Health num = " + FString::SanitizeFloat(Health);
	const FString IsDeadStr = "isDead = " + FString((IsDead) ? "True" : "False");

	const FString Stat = FString::Printf(TEXT(" \n == All Stats == \n %s \n %s \n %s"), *WeaponsNumStr, *HealthStr, *IsDeadStr);

	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, Name);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Stat, true, FVector2D{ 1.5f, 1.5f });
	}
}
