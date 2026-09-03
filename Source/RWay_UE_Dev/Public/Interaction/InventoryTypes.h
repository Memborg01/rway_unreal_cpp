// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InventoryTypes.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	Key UMETA(DisplayName = "Key"),
	Health UMETA(DisplayName = "Health"),
	Weapon UMETA(DisplayName = "Weapon"),
	Generic UMETA(DisplayName = "Generic")
};

/**
 * 
 */

USTRUCT(BlueprintType)
struct FInventoryItem
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Blueprintable)
	FName ItemID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText ItemDescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemType ItemType = EItemType::Generic;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemQuantity = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxStackSize = 99;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UTexture2D> Icon;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemValue = 0.0f;
};

class RWAY_UE_DEV_API InventoryTypes
{
public:
	InventoryTypes();
	~InventoryTypes();
};
