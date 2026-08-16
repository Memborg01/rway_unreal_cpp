// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "DoorAnimation.generated.h"

UENUM(BlueprintType)
enum class EDoorMoveDirection : uint8
{
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down"),
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward")
};

USTRUCT(BlueprintType)
struct  FDoorMeshConfig
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UStaticMeshComponent* MeshComponent = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	EDoorMoveDirection DoorMoveDirection = EDoorMoveDirection::Right;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	float MoveDistance = 200.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	float MoveSpeed = 150.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorMoveComplete, bool, bOpened);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RWAY_UE_DEV_API UDoorAnimation : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDoorAnimation();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UBoxComponent* TriggerBox = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	TArray<FDoorMeshConfig> DoorMeshConfigs;
	
	UPROPERTY(BlueprintAssignable, Category = "Door")
	FOnDoorMoveComplete OnDoorMoveComplete;
	
	UFUNCTION(BlueprintCallable, Category="Door Mechanics")
	void OpenDoor();
	
	UFUNCTION(BlueprintCallable, Category="Door Mechanics")
	void CloseDoor();
	
	UFUNCTION(BlueprintCallable, Category="Door Mechanics")
	void ToggleDoor();
	
	UFUNCTION(BlueprintCallable, Category="Door Mechanics")
	void UnlockDoor();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	bool bIsOpened = false;
	bool bIsMoving = false;
	bool bIsLocked = true;
	
	TArray<FVector> OriginalPositions;
	TArray<FVector> TargetPositions;
	
	void CacheOriginalPositions();
	FVector GetDirectionVector(const FDoorMeshConfig& Config) const;
	
	UFUNCTION()
	void OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
