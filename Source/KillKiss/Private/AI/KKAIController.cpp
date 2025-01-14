// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/KKAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AKKAIController::AKKAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));

	ensure(Blackboard && BehaviorTreeComponent);
}
