// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/KKEnemyCharacter.h"

#include "KKDebugHelper.h"
#include "KKGameplayTags.h"
#include "AbilitySystem/KKAbilitySystemComponent.h"
#include "AbilitySystem/KKAttributeSet.h"
#include "AI/KKAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/KKUserWidget.h"

AKKEnemyCharacter::AKKEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UKKAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UKKAttributeSet>(TEXT("AttributeSet"));

	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());
}

int32 AKKEnemyCharacter::GetPlayerLevel()
{
	return Level;
}

void AKKEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitAbilityActorInfo();
}

void AKKEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	KKAIController = Cast<AKKAIController>(NewController);
	KKAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	KKAIController->RunBehaviorTree(BehaviorTree);
	KKAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	KKAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"),
	                                                         CharacterClass != ECharacterClass::Warrior);
}

void AKKEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]()
		{
			if (UDataAsset_StartupDataBase* LoadedData = CharacterStartUpData.LoadSynchronous())
			{
				if (UKKAbilitySystemComponent* KKAbilitySystemComponent =
					Cast<UKKAbilitySystemComponent>(AbilitySystemComponent))
				{
					LoadedData->GiveToAbilitySystemComponent(KKAbilitySystemComponent, Level);
				}

				BindHealthChangeCallbacks();
			}
		})
	);
}


void AKKEnemyCharacter::BindHealthChangeCallbacks()
{
	if (UKKUserWidget* KKUserWidget = Cast<UKKUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		KKUserWidget->SetWidgetController(this);
	}

	if (const UKKAttributeSet* KKAttributeSet = Cast<UKKAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			KKAttributeSet->GetCurrentHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			KKAttributeSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->RegisterGameplayTagEvent(
			                        KKGameplayTags::Shared_Ability_HitPause).
		                        AddUObject(this, &AKKEnemyCharacter::HitReactTagChanged);

		OnHealthChanged.Broadcast(KKAttributeSet->GetCurrentHealth());
		OnMaxHealthChanged.Broadcast(KKAttributeSet->GetMaxHealth());
	}
}

void AKKEnemyCharacter::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;

	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? BaseWalkSpeed / 2.f : BaseWalkSpeed;
	KKAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
}
