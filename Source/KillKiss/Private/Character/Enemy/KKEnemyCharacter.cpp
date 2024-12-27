// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/KKEnemyCharacter.h"

#include "AbilitySystem/KKAbilitySystemComponent.h"
#include "AbilitySystem/KKAttributeSet.h"
#include "DataAssets/StartupData/DataAsset_StartupDataBase.h"
#include "Engine/AssetManager.h"

AKKEnemyCharacter::AKKEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<UKKAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UKKAttributeSet>(TEXT("AttributeSet"));
}

int32 AKKEnemyCharacter::GetPlayerLevel()
{
	return Level;
}

void AKKEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
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
