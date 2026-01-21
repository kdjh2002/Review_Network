// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreHudWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class REVIEW_NETWORK_API UScoreHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void UpdateName(FText InName);

	UFUNCTION(BlueprintCallable)
	void UpdateIntValue(int32 InValue);

	UFUNCTION(BlueprintCallable)
	void UpdateFloatValue(float InValue);

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Name = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Value = nullptr;
};
