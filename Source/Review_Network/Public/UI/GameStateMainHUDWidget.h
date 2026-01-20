// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStateMainHUDWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class REVIEW_NETWORK_API UGameStateMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()


protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	
	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateTimeDisplay();	//시간갱신함수

	UFUNCTION(BlueprintCallable, Category = "Game Data")
	void UpdateGameOverDisplay();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> GameOverText = nullptr;

private:
	TWeakObjectPtr<class ATestGameState> CachedGameState = nullptr;
};
