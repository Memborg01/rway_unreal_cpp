// Fill out your copyright notice in the Description page of Project Settings.


#include "RwPlayerController.h"
#include "RwPlayerCameraManager.h"

ARwPlayerController::ARwPlayerController()
{
	PlayerCameraManagerClass = ARwPlayerCameraManager::StaticClass();
}
