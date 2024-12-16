﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_AttributeInfo.generated.h"


USTRUCT(BlueprintType)
struct FAttributeInfo
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 * 
 */
UCLASS()
class KILLKISS_API UDataAsset_AttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION()
	FAttributeInfo FindAttributeInformationByTag(FGameplayTag InTag);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAttributeInfo> AttributeInfos;
};
