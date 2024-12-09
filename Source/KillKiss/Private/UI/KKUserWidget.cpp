// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KKUserWidget.h"

void UKKUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
