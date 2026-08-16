// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorAnimation.h"

#include "MyGameInstance.h"

// Sets default values for this component's properties
UDoorAnimation::UDoorAnimation()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UDoorAnimation::OpenDoor()
{
	if (bIsOpened) return;

	TargetPositions.Empty();
	UE_LOG(LogTemp, Warning, TEXT("DoorAnimation: Opening door amount - %d"), DoorMeshConfigs.Num());
	for (int32 i = 0; i < DoorMeshConfigs.Num(); ++i)
	{
		const FDoorMeshConfig& Config = DoorMeshConfigs[i];
		if (Config.MeshComponent && OriginalPositions.IsValidIndex(i))
		{
			FVector WorldOffset = GetDirectionVector(Config) * Config.MoveDistance;
			FVector LocalOffset = GetOwner()->GetActorTransform().InverseTransformVector(WorldOffset);
			TargetPositions.Add(OriginalPositions[i] + LocalOffset);
		}

		else
		{
			TargetPositions.Add(FVector::ZeroVector);
		}
	}

	bIsOpened = true;
	bIsMoving = true;
	SetComponentTickEnabled(true);
}

void UDoorAnimation::CloseDoor()
{
	if (!bIsOpened) return;

	TargetPositions.Empty();

	for (int32 i = 0; i < DoorMeshConfigs.Num(); ++i)
	{
		TargetPositions.Add(OriginalPositions.IsValidIndex(i) ? OriginalPositions[i] : FVector::ZeroVector);
	}

	bIsOpened = false;
	bIsMoving = true;
	SetComponentTickEnabled(true);
}

void UDoorAnimation::ToggleDoor()
{
	bIsOpened ? CloseDoor() : OpenDoor();
}

void UDoorAnimation::UnlockDoor()
{
	bIsLocked = false;
}

void UDoorAnimation::CacheOriginalPositions()
{
	OriginalPositions.Empty();
	for (const FDoorMeshConfig& Config : DoorMeshConfigs)
	{
		if (Config.MeshComponent)
		{
			OriginalPositions.Add(Config.MeshComponent->GetRelativeLocation());
		}
		else
		{
			OriginalPositions.Add(FVector::ZeroVector);
		}
	}
}

FVector UDoorAnimation::GetDirectionVector(const FDoorMeshConfig& Config) const
{
	AActor* Owner = GetOwner();
	if (!Owner)
	{
		return FVector::ZeroVector;
	}

	switch (Config.DoorMoveDirection)
	{
	case EDoorMoveDirection::Right: return Owner->GetActorRightVector();
	case EDoorMoveDirection::Left: return -Owner->GetActorRightVector();
	case EDoorMoveDirection::Up: return Owner->GetActorUpVector();
	case EDoorMoveDirection::Down: return -Owner->GetActorUpVector();
	case EDoorMoveDirection::Forward: return Owner->GetActorForwardVector();
	case EDoorMoveDirection::Backward: return -Owner->GetActorForwardVector();
	default:
		return FVector::ZeroVector;
	}
}

void UDoorAnimation::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                           UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                           const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
		
		if (GI && GI->Keys.Contains("MainGate"))
		{
			OpenDoor();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("DoorAnimation: You need the main gate key"));
		}
	}
}

void UDoorAnimation::OnTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		CloseDoor();
	}
}


// Called when the game starts
void UDoorAnimation::BeginPlay()
{
	Super::BeginPlay();

	CacheOriginalPositions();

	if (TriggerBox)
	{
		TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &UDoorAnimation::OnTriggerBeginOverlap);
		TriggerBox->OnComponentEndOverlap.AddDynamic(this, &UDoorAnimation::OnTriggerEndOverlap);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DoorAnimation: No TriggerBox assigned"));
	}
}


// Called every frame
void UDoorAnimation::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsMoving) return;

	bool bStillMoving = false;

	for (int32 i = 0; i < DoorMeshConfigs.Num(); ++i)
	{
		const FDoorMeshConfig& DoorMeshConfig = DoorMeshConfigs[i];
		if (!DoorMeshConfig.MeshComponent || !TargetPositions.IsValidIndex(i)) continue;

		FVector CurrentPosition = DoorMeshConfig.MeshComponent->GetRelativeLocation();
		FVector TargetPosition = TargetPositions[i];

		if (!CurrentPosition.Equals(TargetPosition, 0.5f))
		{
			DoorMeshConfig.MeshComponent->SetRelativeLocation(
				FMath::VInterpConstantTo(CurrentPosition, TargetPosition, DeltaTime, DoorMeshConfig.MoveSpeed));
			bStillMoving = true;
		}
		else
		{
			DoorMeshConfig.MeshComponent->SetRelativeLocation(TargetPosition);
		}

		if (!bStillMoving)
		{
			bIsMoving = false;
			SetComponentTickEnabled(false);
			OnDoorMoveComplete.Broadcast(bIsOpened);
		}
	}
}
