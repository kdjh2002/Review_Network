// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameStateMainHUDWidget.h"
#include "UI/ScoreHudWidget.h"
#include "Framework/TestGameState.h"
#include "Framework/NetPlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

void UGameStateMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameOverText->SetVisibility(ESlateVisibility::Hidden);	//처음엔 가려두기
	GameOverBackground->SetVisibility(ESlateVisibility::Hidden);	//처음엔 가려두기
	ReplayButton->SetVisibility(ESlateVisibility::Hidden);	//처음엔 가려두기

}

void UGameStateMainHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(this));
	}

	UpdateTimeDisplay();
	UpdateGameOverDisplay();
	UpdateScoreDisplay();
}

void UGameStateMainHUDWidget::UpdateTimeDisplay()
{
	if (CachedGameState.IsValid())	//있을떄
	{
		//FloorToInt : 인티저보다 수학계산 빠르게 나옴
		int32 Total = FMath::FloorToInt(CachedGameState->GetGameElapsedTime());	//전체시간
		int32 Minutes = Total / 60;
		int32 Seconds = Total % 60;
		//문자열 : TEXT("%02d:%02d") -> 00:00
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}

void UGameStateMainHUDWidget::UpdateGameOverDisplay()
{

	if (CachedGameState->IsGameOver())
	{
		GameOverText->SetVisibility(ESlateVisibility::HitTestInvisible);
		GameOverBackground->SetVisibility(ESlateVisibility::HitTestInvisible);
		ReplayButton->SetVisibility(ESlateVisibility::Visible);

		int32 MyPoint = 0;
		int32 EnemyPoint = 0;

		//점수 가져오기
		for (APlayerState* PS : CachedGameState->PlayerArray)
		{
			ANetPlayerState* NetPS = Cast<ANetPlayerState>(PS);
			if (NetPS)
			{
				if (NetPS == GetOwningPlayerState())
				{
					MyPoint = NetPS->MyScore;
				}
				else
				{
					EnemyPoint = NetPS->MyScore;
				}
			}
		}

		//승패 비교하기
		if (MyPoint > EnemyPoint)
		{
			GameOverText->SetText(FText::FromString(TEXT("YOU WIN!!")));
			GameOverText->SetColorAndOpacity(FLinearColor::Green);
		}
		else if (MyPoint < EnemyPoint)
		{
			GameOverText->SetText(FText::FromString(TEXT("YOU Lose...")));
			GameOverText->SetColorAndOpacity(FLinearColor::Red);
		}
		else
		{
			GameOverText->SetText(FText::FromString(TEXT("Tie")));
			GameOverText->SetColorAndOpacity(FLinearColor::Yellow);
		}

	}
	else
	{
		GameOverText->SetVisibility(ESlateVisibility::Hidden);	//처음엔 가려두기
		GameOverBackground->SetVisibility(ESlateVisibility::Hidden);	//처음엔 가려두기
		ReplayButton->SetVisibility(ESlateVisibility::Hidden);	//처음엔 가려두기

	}
}

void UGameStateMainHUDWidget::UpdateScoreDisplay()
{
	// GameState에는 현재 접속한 플레이어 목록(PlayerArray)이 있습
	for (APlayerState* PS : CachedGameState->PlayerArray)
	{
		ANetPlayerState* NetPS = Cast<ANetPlayerState>(PS);

		if (NetPS)
		{
			if (NetPS == GetOwningPlayerState())	//자기자신인지 //로컬플레이어
			{
				if (MyScore)	//내점수
				{
					MyScore->UpdateName(FText::FromString(TEXT("ME")));
					MyScore->UpdateIntValue(NetPS->MyScore);
				}
			}
			else
			{
				if (EnemyScore)	//적 점수
				{
					EnemyScore->UpdateName(FText::FromString(TEXT("ENEMY")));
					EnemyScore->UpdateIntValue(NetPS->MyScore);
				}
			}
		}
	}
}
