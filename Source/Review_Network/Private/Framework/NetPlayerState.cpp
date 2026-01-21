// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/NetPlayerState.h"
#include "Framework/MainHUD.h"
#include "Net/UnrealNetwork.h"
#include "Character/PlayerStateCharacter.h"


void ANetPlayerState::AddMyScore(int32 Point)
{
	if (HasAuthority())
	{
		MyScore += Point;
		OnRep_MyScore();	//서버는 리플리케이션이 없으니 수동으로 호출
	}
}


void ANetPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ANetPlayerState, MyScore);	//모든 클라이언트에 리플리케이션

}

void ANetPlayerState::OnRep_MyScore()
{
	// UI 갱신
	UE_LOG(LogTemp, Log, TEXT("[%d]Score : %d"), GetPlayerId(), MyScore);
	//if (!ScoreHud.IsValid())
	//{
	//	if (GetPlayerController())
	//	{
	//		//UE_LOG(LogTemp, Log, TEXT("플레이어 컨트롤러 있음"));
	//		AMainHUD* HUD = GetPlayerController()->GetHUD<AMainHUD>();
	//		if (HUD && HUD->GetMainHudWidget().IsValid())
	//		{
	//			//UE_LOG(LogTemp, Log, TEXT("HUD와 HUD위젯도 있음"));
	//			ScoreHud = Cast<UScoreHudWidget>(HUD->GetMainHudWidget().Get());
	//		}
	//	}
	//}


	//if (ScoreHud.IsValid())
	//{
	//	ScoreHud->UpdateScore(MyScore);
	//}
}

