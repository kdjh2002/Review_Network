// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TestGameState.generated.h"

/**
 * 
 */
UCLASS()
class REVIEW_NETWORK_API ATestGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ATestGameState();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	//시간처리를 위해
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//리플리케이티드가 되어야함

	//스폰함수
	void SpawnItem();
	UFUNCTION()
	void OnRep_GameOver();

public:
	//Getter함수
	inline float GetGameElapsedTime() const { return GameElapsedTime; }
	inline float IsGameOver() const { return bGameOver; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Spawner")
	TSubclassOf<class AActor> PickupItemClass;

protected:
	//서버 값이 클라이언트로 자동 동기화됨
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float GameElapsedTime = 60.0f;	//게임시간

	UPROPERTY(ReplicatedUsing = OnRep_GameOver, BlueprintReadOnly, Category = "Game Data")
	bool bGameOver = false;

	float ItemSpawnTimer = 0.0f;
};
