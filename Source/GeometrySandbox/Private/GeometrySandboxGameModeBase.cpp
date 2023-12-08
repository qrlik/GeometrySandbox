// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometrySandboxGameModeBase.h"
#include "SandboxPawn.h"

AGeometrySandboxGameModeBase::AGeometrySandboxGameModeBase() {
	DefaultPawnClass = ASandboxPawn::StaticClass();
}
