// Fill out your copyright notice in the Description page of Project Settings.


#include "RwPlayerCameraManager.h"

ARwPlayerCameraManager::ARwPlayerCameraManager()
{
	CurrentArmLength = DefaultArmLength;
	TargetArmLength = DefaultArmLength;

	CurrentFOV = BaseFOV;
	TargetFOV = BaseFOV;

	InterpSpeed = DefaultInterpSpeed;
}

void ARwPlayerCameraManager::SetCameraTarget(float InArmLength, float InFOV, float InInterpSpeed)
{
	TargetArmLength = InArmLength;
	TargetFOV = InFOV;
	if (InInterpSpeed > 0.f)
	{
		InterpSpeed = InInterpSpeed;
	}
}

void ARwPlayerCameraManager::ResetCameraTarget()
{
	TargetArmLength = DefaultArmLength;
	TargetFOV = BaseFOV;
	InterpSpeed = DefaultInterpSpeed;
}

void ARwPlayerCameraManager::UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime)
{
	Super::UpdateViewTarget(OutVT, DeltaTime);
	
	CurrentArmLength = FMath::FInterpTo(CurrentArmLength, TargetArmLength, DeltaTime, InterpSpeed);
	CurrentFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, InterpSpeed);
	
	float DeltaLength = CurrentArmLength - DefaultArmLength;
	FVector Forward = OutVT.POV.Rotation.Vector();
	
	OutVT.POV.Location -= Forward * DeltaLength;
	OutVT.POV.FOV = CurrentFOV;
}
