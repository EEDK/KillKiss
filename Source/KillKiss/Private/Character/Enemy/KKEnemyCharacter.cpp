// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/KKEnemyCharacter.h"

#include "AbilitySystem/KKAbilitySystemComponent.h"
#include "AbilitySystem/KKAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"
#include "Engine/AssetManager.h"
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

		OnHealthChanged.Broadcast(KKAttributeSet->GetCurrentHealth());
		OnMaxHealthChanged.Broadcast(KKAttributeSet->GetMaxHealth());
	}
}

void AKKEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());

	InitEnemyStartUpData();
}

void AKKEnemyCharacter::InitEnemyStartUpData() const
{
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
			}
		})
	);
}
