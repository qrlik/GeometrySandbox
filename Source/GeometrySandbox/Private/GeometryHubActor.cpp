// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"
#include "Engine/World.h"

// Sets default values
AGeometryHubActor::AGeometryHubActor() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay() {
	Super::BeginPlay();

	DoActorSpawn1();
	DoActorSpawn2();
	DoActorSpawn3();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AGeometryHubActor::DoActorSpawn1() const {
	if (const auto World = GetWorld()) {
		for (auto i = 0; i < 10; ++i) {
			auto Transform = FTransform{ FRotator::ZeroRotator, FVector{ 0.f, 300.f * i, 300.f } };
			if (auto* Actor = World->SpawnActor<ABaseGeometryActor>(GeometryActor, Transform)) {
				FGeometryData Data;
				Data.MovementType = FMath::RandBool() ? EMovementType::Sin : EMovementType::Static;
				Actor->setGeometryData(Data);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn2() const {
	if (const auto World = GetWorld()) {
		for (auto i = 0; i < 10; ++i) {
			auto Transform = FTransform{ FRotator::ZeroRotator, FVector{ 0.f, 300.f * i, 700.f } };
			if (auto* Actor = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryActor, Transform)) {
				FGeometryData Data;
				Data.Color = FLinearColor::MakeRandomColor();
				Data.MovementType = FMath::RandBool() ? EMovementType::Sin : EMovementType::Static;
				Actor->setGeometryData(Data);
				Actor->FinishSpawning(Transform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn3() const {
	if (const auto World = GetWorld()) {
		for (const auto& [Class, Data, Transform] : Payloads) {
			if (auto* Actor = World->SpawnActorDeferred<ABaseGeometryActor>(Class, Transform)) {
				Actor->setGeometryData(Data);
				Actor->FinishSpawning(Transform);
			}
		}
	}
}
