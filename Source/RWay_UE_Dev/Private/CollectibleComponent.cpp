// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectibleComponent.h"
#include "Components/ShapeComponent.h"
#include "MyGameInstance.h"
#include "Chaos/CollectionPropertyFacade.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCollectibleComponent::UCollectibleComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCollectibleComponent::BeginPlay()
{
	Super::BeginPlay();
	TArray<UShapeComponent*> Shapes;
	GetOwner()->GetComponents<UShapeComponent>(Shapes);
	
	CollisionComponent = Shapes[0];
	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &UCollectibleComponent::HandleOverlap);
	}
}

void UCollectibleComponent::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	if (OtherActor == UGameplayStatics::GetPlayerPawn(this, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("Collectible collected"));
		if (bIsKeyItem)
		{
			UMyGameInstance* GI = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());

			if (GI && !KeyID.IsNone())
			{
				GI->bHasKey = true;
				GI->Keys.Add(KeyID);
			}
		}
		
		GetOwner()->Destroy();
	}
	
}
