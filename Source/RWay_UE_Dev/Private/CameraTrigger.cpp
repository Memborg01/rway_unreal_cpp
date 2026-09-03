// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraTrigger.h"

#include "RwPlayerCameraManager.h"
#include "Components/BoxComponent.h"


// Sets default values
ACameraTrigger::ACameraTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = TriggerBox;

	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->SetGenerateOverlapEvents(true);
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACameraTrigger::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ACameraTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void ACameraTrigger::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	if (!OtherActor) return;

	APawn* Pawn = Cast<APawn>(OtherActor);

	if (Pawn && Pawn->IsPlayerControlled())
	{
		UE_LOG(LogTemp, Warning, TEXT("CameraTrigger: Player entered trigger"));
		APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
		if (PC && PC->PlayerCameraManager)
		{
			ARwPlayerCameraManager* CameraManager = Cast<ARwPlayerCameraManager>(PC->PlayerCameraManager);
			if (CameraManager)
			{
				UE_LOG(LogTemp, Warning, TEXT("CameraTrigger: Setting camera target"));
				CameraManager->SetCameraTarget(TargetArmLength, TargetFOV, InterSpeed);
			}
		}
	}
}

void ACameraTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor) return;

	APawn* Pawn = Cast<APawn>(OtherActor);

	if (Pawn && Pawn->IsPlayerControlled())
	{
		APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
		if (PC && PC->PlayerCameraManager)
		{
			ARwPlayerCameraManager* CameraManager = Cast<ARwPlayerCameraManager>(PC->PlayerCameraManager);
			if (CameraManager)
			{
				CameraManager->ResetCameraTarget();
			}
		}
	}
}
