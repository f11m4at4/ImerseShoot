// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyZone.h"
#include <Components/BoxComponent.h>
#include "../Public/CPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "CBullet.h"
// Sets default values
ADestroyZone::ADestroyZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������Ʈ ���
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	// Collision ������Ʈ�� ��Ʈ�� ���
	RootComponent = Collision;
	Collision->SetCollisionProfileName(TEXT("DestoryZone"));
}

// Called when the game starts or when spawned
void ADestroyZone::BeginPlay()
{
	Super::BeginPlay();
	
	// ������Ʈ �浹 ����
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ADestroyZone::OnComponentBeginOverlap);
}

// Called every frame
void ADestroyZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyZone::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �ε��� �༮�� �Ѿ��̸�
	if (OtherActor->IsA(ACBullet::StaticClass()))
	{
		// źâ�� �ְ� �ʹ�.
		auto Bullet = Cast<ACBullet>(OtherActor);
		Bullet->SetActive(false);
		ACPlayer::BulletPool.Add(Bullet);
	}
	else
	{
		// �ε��� �༮�� ���ְ�
		OtherActor->Destroy();
	}
}