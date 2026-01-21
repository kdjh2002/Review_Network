// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/PickupItem.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Character/PlayerStateCharacter.h"

// Sets default values
APickupItem::APickupItem()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true; // 서버에서 생성되면 클라에도 보여야 함

    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    RootComponent = SphereComp;
    SphereComp->SetSphereRadius(50.0f);
    SphereComp->SetCollisionProfileName(TEXT("OverlapAllDynamic")); // 겹침 감지용

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision); // 메시는 충돌 끔

}

void APickupItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    // ★ 점수 처리는 반드시 서버(Authority)에서만!
    if (HasAuthority())
    {
        APlayerStateCharacter* Character = Cast<APlayerStateCharacter>(OtherActor);
        if (Character)
        {
            // 캐릭터에게 점수 추가 요청 (이미 만드신 함수)
            Character->Server_AddScore_Implementation(1);

            // 아이템 삭제
            Destroy();
        }
    }
}


