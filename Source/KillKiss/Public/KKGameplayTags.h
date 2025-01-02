// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace KKGameplayTags
{
	//InputTag;
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump)

	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_1)
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_2)
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LMB)
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_RMB)

	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable)
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_OpenAttributeMenu)

	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld)
	//~InputTag;

	//Ability Tags
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_OpenAttributeMenu);
	//~Ability Tags

	// Shared Tags
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitPause);
	// ~Shared Tag

	//Event Tags
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_OnAttack);
	//~Event Tags

	//Status Tags
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_State_AttributeMenuOpen);
	//~Status Tags

	//Attribute Tags
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Strength);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Intelligence);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Luck);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_DefensePower);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Primary_Vigor);

	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_Armor);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ArmorPenetration);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitChance);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitDamage);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_CriticalHitResistance);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_HealthRegeneration);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxHealth);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_ManaRegeneration);
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attributes_Secondary_MaxMana);
	//~Attribute Tags
}
