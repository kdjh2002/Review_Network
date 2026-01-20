// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestGameState.h"
#include "Net/UnrealNetwork.h"

ATestGameState::ATestGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority()) //시간업데이트는 서버에서만 클라이언트(플레이어)는 시간을 받기만
	{
		GameElapsedTime -= DeltaTime;
		//UE_LOG(LogTemp, Log, TEXT("Time Update : %.2f"), GameElapsedTime);

		//계산결과가 0밑이면 강제로 0.0f으로 고정
		GameElapsedTime = FMath::Max(GameElapsedTime, 0.0f);
	}
}

void ATestGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestGameState, GameElapsedTime);	//복제시켜줌
}
