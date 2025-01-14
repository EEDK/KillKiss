// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "KKGameplayTags.h"
#include "AbilitySystem/KKAbilitySystemLibrary.h"
#include "AbilitySystem/KKAttributeSet.h"
#include "Interface/CombatInterface.h"

struct FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance)

	FDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKKAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKKAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKKAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKKAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UKKAttributeSet, CriticalHitResistance, Target, false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                              FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	UCurveTable* CoefficientsTable = UKKAbilitySystemLibrary::GetDamageCalculationCoefficients(SourceAvatar);

	ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
	ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	// Set by Caller를 통한 Damage 값 가져오기
	float Damage = Spec.GetSetByCallerMagnitude(KKGameplayTags::Damage);

	// 방어구 관통력 효과 적용
	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,
	                                                           EvaluationParameters,
	                                                           TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.f);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef,
	                                                           EvaluationParameters,
	                                                           SourceArmorPenetration);

	const FRealCurve* ArmorPenetrationCurve = CoefficientsTable->FindCurve(FName("ArmorPenetration"), FString());
	const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());

	const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;

	const FRealCurve* EffectiveArmorCurve = CoefficientsTable->FindCurve(FName("EffectiveArmor"), FString());
	const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());

	Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;


	// Critical 구현
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef,
	                                                           EvaluationParameters,
	                                                           SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);

	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef,
	                                                           EvaluationParameters,
	                                                           SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage, 0.f);

	float TargetCriticalResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef,
	                                                           EvaluationParameters,
	                                                           TargetCriticalResistance);
	TargetCriticalResistance = FMath::Max<float>(TargetCriticalResistance, 0.f);

	const FRealCurve* CriticalHitResistanceCurve =
		CoefficientsTable->FindCurve(FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCurveCoefficient
		= CriticalHitResistanceCurve->Eval(SourceCombatInterface->GetPlayerLevel());

	const float EffectiveCriticalHitChance
		= SourceCriticalHitChance - TargetCriticalResistance * CriticalHitResistanceCurveCoefficient;

	const bool bCritical = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;

	UKKAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCritical);

	Damage = bCritical ? Damage * (SourceCriticalHitDamage / 100.f) : Damage;

	// 가드 여부 확인 (치명타가 안터졌을경우에만)
	if (!bCritical)
	{
		const float BlockChance = TargetArmor * 0.333f;
		const bool bBlock = FMath::RandRange(1, 100) <= BlockChance;

		Damage = bBlock ? Damage / 2.f : Damage;
		UKKAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlock);
	}

	const FGameplayModifierEvaluatedData EvaluatedData(UKKAttributeSet::GetIncomingDamageAttribute(),
	                                                   EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
