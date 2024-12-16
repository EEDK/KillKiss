// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/UIData/DataAsset_AttributeInfo.h"

FAttributeInfo UDataAsset_AttributeInfo::FindAttributeInformationByTag(FGameplayTag InTag)
{
	for (const FAttributeInfo& Info : AttributeInfos)
	{
		if (Info.AttributeTag.MatchesTagExact(InTag))
		{
			return Info;
		}
	}

	return FAttributeInfo();
}
