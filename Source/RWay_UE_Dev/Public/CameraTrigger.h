// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraTrigger.generated.h"

class UBoxComponent;

UCLASS()
class RWAY_UE_DEV_API ACameraTrigger : public AActor
{
	GENERATED_BODY()

public:
	ACameraTrigger();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* TriggerBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float TargetArmLength = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float TargetFOV = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float InterSpeed = 3.0f;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex);
};
