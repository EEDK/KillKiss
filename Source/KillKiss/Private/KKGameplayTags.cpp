// Fill out your copyright notice in the Description page of Project Settings.


#include "KKGameplayTags.h"

namespace KKGameplayTags
{
	//InputTag;
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_1, "InputTag.1")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_2, "InputTag.2")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LMB, "InputTag.LMB")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_RMB, "InputTag.RMB")
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_OpenAttributeMenu, "InputTag.Toggleable.OpenAttributeMenu")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld")
	//~InputTag;

	//Ability Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_OpenAttributeMenu, "Player.Ability.OpenAttributeMenu")
	//~Ability Tags

	//Status Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_State_AttributeMenuOpen, "Player.State.AttributeMenuOpen")
	//~Status Tags

	//Attribute Tags
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Strength, "Attributes.Primary.Strength")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Intelligence, "Attributes.Primary.Intelligence")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Luck, "Attributes.Primary.Luck")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_DefensePower, "Attributes.Primary.DefensePower")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Primary_Vigor, "Attributes.Primary.Vigor")

	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_Armor, "Attributes.Secondary.Armor")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_ArmorPenetration, "Attributes.Secondary.ArmorPenetration")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitChance, "Attributes.Secondary.CriticalHitChance")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitDamage, "Attributes.Secondary.CriticalHitDamage")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_CriticalHitResistance, "Attributes.Secondary.CriticalHitResistance")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_HealthRegeneration, "Attributes.Secondary.HealthRegeneration")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_MaxHealth, "Attributes.Secondary.MaxHealth")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_ManaRegeneration, "Attributes.Secondary.ManaRegeneration")
	UE_DEFINE_GAMEPLAY_TAG(Attributes_Secondary_MaxMana, "Attributes.Secondary.MaxMana")
	//~Attribute Tags
}
