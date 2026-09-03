// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DecalInstancerProjector.generated.h"

class UBoxComponent;

UCLASS()
class RWAY_UE_DEV_API ADecalInstancerProjector : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADecalInstancerProjector();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	virtual void PostEditMove(bool bFinished) override;
#endif
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* ProjectorBox;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	TSubclassOf<AActor> ActorsToSpawn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (ClampMin = "0", ClampMax = "1000"))
	int32 SpawnDensity = 50;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomization")
	FVector2D ScaleRange = FVector2D(0.5, 1.5);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomization")
	FVector RotationRange = FVector(360.f, 360.f, 360.f);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float SurfaceOffset = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float IntersectionBias = 0.7f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	float MinSpawnDistance = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	bool bAutoUpdateOnEditor = true;
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void SpawnActors();
	
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void ClearSpawnedActors();
	
private:
	UPROPERTY()
	TArray<AActor*> SpawnedActors;
	
	float CalculateGeometryComplexity(const FVector& Location, const TArray<AActor*>& OverlappingActors);
	bool IsValidSpawnLocation(const FVector& Location);
};
