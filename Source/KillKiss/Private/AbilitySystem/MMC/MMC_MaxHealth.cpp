// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMC/MMC_MaxHealth.h"

#include "AbilitySystem/KKAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	StrengthDef.AttributeToCapture = UKKAttributeSet::GetStrengthAttribute();
	StrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	StrengthDef.bSnapshot = false;

	VigorDef.AttributeToCapture = UKKAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(StrengthDef);
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Strength = 0.f;
	GetCapturedAttributeMagnitude(StrengthDef, Spec, EvaluationParameters, Strength);
	FMath::Max(Strength, 0.f);

	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluationParameters, Vigor);
	FMath::Max(Vigor, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());

	const int32 Level = CombatInterface->GetPlayerLevel();

	return Vigor * 10 + Strength * 2 + Level * 10;
}
