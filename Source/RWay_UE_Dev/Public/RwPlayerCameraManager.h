// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "RwPlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class RWAY_UE_DEV_API ARwPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	ARwPlayerCameraManager();
	
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void SetCameraTarget(float InArmLength, float InFOV, float InInterpSpeed = 5.f);
	
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void ResetCameraTarget();
	
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float DefaultArmLength = 300.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float BaseFOV = 90.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float DefaultInterpSpeed = 5.0f;
	
private:
	float TargetArmLength;
	float CurrentArmLength;
	float TargetFOV;
	float CurrentFOV;
	float InterpSpeed;
};
