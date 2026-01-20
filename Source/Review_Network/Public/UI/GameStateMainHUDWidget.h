// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStateMainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class REVIEW_NETWORK_API UGameStateMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateTimeDisplay();	//시간갱신함수

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TimeText = nullptr;

private:
	TWeakObjectPtr<class ATestGameState> CachedGameState = nullptr;
};
