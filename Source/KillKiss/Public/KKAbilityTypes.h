#pragma once

#include "GameplayEffectTypes.h"
#include "KKAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FKKGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}

	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FGameplayEffectContext* Duplicate() const
	{
		FKKGameplayEffectContext* NewContext = new FKKGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:
	UPROPERTY()
	bool bIsBlockedHit = false;

	UPROPERTY()
	bool bIsCriticalHit = false;

public:
	bool IsCriticalHit() const
	{
		return bIsCriticalHit;
	}

	bool IsBlockedHit() const
	{
		return bIsBlockedHit;
	}

	void SetBlockedHit(bool bInIsBlockedHit)
	{
		bIsBlockedHit = bInIsBlockedHit;
	}

	void SetCriticalHit(bool bInIsCriticalHit)
	{
		bIsCriticalHit = bInIsCriticalHit;
	}
};

template <>
struct TStructOpsTypeTraits<FKKGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FKKGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};
