// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameStateMainHUDWidget.generated.h"

class UTextBlock;
class UScoreHudWidget;
class UImage;
class UButton;
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

public:
	void UpdateScoreDisplay();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TimeText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> GameOverText = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UScoreHudWidget> MyScore = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UScoreHudWidget> EnemyScore = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> GameOverBackground = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UButton> ReplayButton = nullptr;

private:
	TWeakObjectPtr<class ATestGameState> CachedGameState = nullptr;
};
