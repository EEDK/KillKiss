// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/KKWidgetController.h"

void KKWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParms)
{
	PlayerController = WCParms.PlayerController;
	PlayerState = WCParms.PlayerState;
	AbilitySystemComponent = WCParms.AbilitySystemComponent;
	AttributeSet = WCParms.AttributeSet;
}

void KKWidgetController::BroadcastInitialValues()
{
}

void KKWidgetController::BindCallbacksToDependencies()
{
}
