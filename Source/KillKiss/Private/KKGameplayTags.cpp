// Fill out your copyright notice in the Description page of Project Settings.


#include "KKGameplayTags.h"

namespace KKGameplayTags
{
	//InputTag;
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_OpenAttributeMenu, "InputTag.OpenAttributeMenu")

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable")
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld")
	//~InputTag;

	//Player Tags
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_OpenAttributeMenu, "Player.Ability.OpenAttributeMenu")
	//~Player Tags
}
