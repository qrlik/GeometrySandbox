// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometryHubActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogGeometryHub, All, All)

// Sets default values
AGeometryHubActor::AGeometryHubActor() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGeometryHubActor::BeginPlay() {
	Super::BeginPlay();

	// DoActorSpawn1();
	// DoActorSpawn2();
	// DoActorSpawn3();
	DoActorSpawn4();
}

// Called every frame
void AGeometryHubActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	UE_LOG(LogGeometryHub, Display, TEXT("Property pointer - %i, is valid - %i"), PropertyActor != nullptr, IsValid(PropertyActor));
	UE_LOG(LogGeometryHub, Display, TEXT("NonProperty pointer - %i, is valid - %i"), NonePropertyActor != nullptr, IsValid(NonePropertyActor));
	UE_LOG(LogGeometryHub, Display, TEXT("Weak pointer - %i, is valid - %i"), WeakActor.Get() != nullptr, WeakActor.IsValid());
}

void AGeometryHubActor::DoActorSpawn1() const {
	if (const auto World = GetWorld()) {
		for (auto i = 0; i < 10; ++i) {
			auto Transform = FTransform{ FRotator::ZeroRotator, FVector{ 0.f, 300.f * i, 300.f } };
			if (auto* Actor = World->SpawnActor<ABaseGeometryActor>(GeometryActor, Transform)) {
				FGeometryData Data;
				Data.MovementType = FMath::RandBool() ? EMovementType::Sin : EMovementType::Static;
				Actor->SetGeometryData(Data);
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
				Actor->SetGeometryData(Data);
				Actor->FinishSpawning(Transform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn3() {
	if (const auto World = GetWorld()) {
		for (const auto& [Class, Data, Transform] : Payloads) {
			if (auto* Actor = World->SpawnActorDeferred<ABaseGeometryActor>(Class, Transform)) {
				Actor->SetGeometryData(Data);
				Actor->OnColorChange.AddDynamic(this, &AGeometryHubActor::OnColorChanged);
				Actor->OnTimerFinished.AddUObject(this, &AGeometryHubActor::OnTimerFinished);
				Actor->FinishSpawning(Transform);
			}
		}
	}
}

void AGeometryHubActor::DoActorSpawn4() {
	if (const auto World = GetWorld()) {
		auto Transform1 = FTransform{ FRotator::ZeroRotator, FVector{ 0.f, 300.f, 700.f } };
		PropertyActor = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryActor, Transform1);

		auto Transform2 = FTransform{ FRotator::ZeroRotator, FVector{ 500.f, 300.f, 700.f } };
		NonePropertyActor = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryActor, Transform2);

		auto Transform3 = FTransform{ FRotator::ZeroRotator, FVector{ 1000.f, 300.f, 700.f } };
		WeakActor = World->SpawnActorDeferred<ABaseGeometryActor>(GeometryActor, Transform3);
	}
}

void AGeometryHubActor::OnColorChanged(const FLinearColor& Color, const FString& Name) {
	UE_LOG(LogGeometryHub, Warning, TEXT("Actor Name: %s Color: %s"), *Name, *Color.ToString());
}

void AGeometryHubActor::OnTimerFinished(AActor* Actor) const {
	if (Actor) {
		UE_LOG(LogGeometryHub, Error, TEXT("Timer finished: %s"), *Actor->GetName());
		if (auto Geometry = Cast<ABaseGeometryActor>(Actor)) {
			UE_LOG(LogGeometryHub, Display, TEXT("Cast successful, amplitude %f"), Geometry->GetGeometryData().Amplitude);
		}
		Actor->Destroy();
		// Actor->SetLifeSpan(2.f);
	}
}
