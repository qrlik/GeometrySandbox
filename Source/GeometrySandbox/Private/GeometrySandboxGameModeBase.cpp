// Fill out your copyright notice in the Description page of Project Settings.


#include "GeometrySandboxGameModeBase.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

AGeometrySandboxGameModeBase::AGeometrySandboxGameModeBase() {
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
}
