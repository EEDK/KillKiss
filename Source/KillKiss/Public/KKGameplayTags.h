// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace KKGameplayTags
{
	//InputTag;
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump)
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_OpenAttributeMenu)

	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable)
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld)
	//~InputTag;

	//Player Tags
	KILLKISS_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_OpenAttributeMenu);
	//~Player Tags
}
