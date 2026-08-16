// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollectibleComponent.generated.h"

class UShapeComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RWAY_UE_DEV_API UCollectibleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UCollectibleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectible")
	bool bIsKeyItem = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collectible")
	FName KeyID;

	UFUNCTION()
	void HandleOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
	);
	
private:
	UShapeComponent* CollisionComponent;
	
};
