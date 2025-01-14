// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KKAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class KILLKISS_API AKKAIController : public AAIController
{
	GENERATED_BODY()

public:
	AKKAIController();

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
