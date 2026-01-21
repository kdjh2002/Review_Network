// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestGameState.h"
#include "Net/UnrealNetwork.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

ATestGameState::ATestGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestGameState::BeginPlay()
{
	SpawnItem();	//아이템 스폰 함수 호출
}

void ATestGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() && !bGameOver) //시간업데이트는 서버에서만 클라이언트(플레이어)는 시간을 받기만
	{
		GameElapsedTime -= DeltaTime;
		//UE_LOG(LogTemp, Log, TEXT("Time Update : %.2f"), GameElapsedTime);

		//계산결과가 0밑이면 강제로 0.0f으로 고정
		//GameElapsedTime = FMath::Max(GameElapsedTime, 0.0f);

		//게임 종료일때 
		if (GameElapsedTime < 0.0f)
		{
			//게임이 종료되었습니다
			GameElapsedTime = 0.0f;
			bGameOver = true;
			OnRep_GameOver();
		}

		//스폰 시간 누적
		ItemSpawnTimer += DeltaTime;

		if (ItemSpawnTimer >= 3.0f)
		{
			SpawnItem();	//아이템 스폰 함수 호출

			ItemSpawnTimer -= 3.0f;		//시간 초기화
		}


	}
}

void ATestGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestGameState, GameElapsedTime);	//복제시켜줌
	DOREPLIFETIME(ATestGameState, bGameOver);	//복제시켜줌
}


void ATestGameState::SpawnItem()
{
	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSystem)
	{
		FNavLocation RandomLocation;

		//2. 2000범위안에 랜덤위치 찾기
		FVector Origin = FVector(1500.0f, 1780.0f, 90.0f);
		float Radius = 2000.0f;

		if (NavSystem->GetRandomPointInNavigableRadius(Origin, Radius, RandomLocation))
		{
			// 3. 찾은 위치에 스폰
			FVector SpawnLoc = RandomLocation.Location + FVector(0.0f, 0.0f, 50.0f);
			GetWorld()->SpawnActor<AActor>(PickupItemClass, SpawnLoc, FRotator::ZeroRotator);
		}
		}
}

void ATestGameState::OnRep_GameOver()
{
	// ★ 이 한 줄이면 게임 전체가 일시정지됩니다.
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (PC)
	{
		// 1. 움직임 차단
		PC->SetIgnoreMoveInput(true);
		PC->SetIgnoreLookInput(true);

		PC->bShowMouseCursor = true;
	}
}
