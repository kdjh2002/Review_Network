// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreHudWidget.h"
#include "Components/TextBlock.h"


void UScoreHudWidget::UpdateName(FText InName)
{
	Name->SetText(InName);
}

void UScoreHudWidget::UpdateIntValue(int32 InValue)
{
	Value->SetText(FText::AsNumber(InValue));
}

void UScoreHudWidget::UpdateFloatValue(float InValue)
{
	Value->SetText(FText::AsNumber(static_cast<int32>(InValue)));
}
