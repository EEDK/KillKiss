// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KKWidgetController.h"
#include "DataAssets/UIData/DataAsset_AttributeInfo.h"
#include "AttributeMenuWidgetController.generated.h"

struct FGameplayAttribute;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAttributeInfo&, Info);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class KILLKISS_API UAttributeMenuWidgetController : public UKKWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FAttributeInfoSignature AttributeInfoDelegate;

private:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataAsset_AttributeInfo> AttributeInfo;
	
	void BroadAttributeInfo(const FGameplayTag& InTag, const FGameplayAttribute& Attribute) const;
};
