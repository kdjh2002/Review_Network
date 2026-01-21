// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerStateCharacter.generated.h"

UCLASS()
class REVIEW_NETWORK_API APlayerStateCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerStateCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	UFUNCTION(Server, Reliable)
	void Server_AddScore(int32 Point);

	void Server_AddScore_Implementation(int32 Point);
	UFUNCTION(BlueprintCallable, Category = "Test")
	void TestAddScore();


};
