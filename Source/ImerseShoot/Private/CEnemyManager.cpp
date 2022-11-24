// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemyManager.h"
#include "CEnemy.h"

// Sets default values
ACEnemyManager::ACEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �����ð��� �ѹ��� ���� ����� �ʹ�.
	// 1. �ð��� �귶���ϱ�
	CurrnetTime += DeltaTime;
	// 2. �����ð��� �����ϱ�
	// ���� ����ð��� �����ð��� �ʰ��ߴٸ�
	if (CurrnetTime > CreateTime)
	{
		CurrnetTime = 0;

		// 3. ���� �����.
		// ������ġ
		FVector Location = GetActorLocation();
		// ȸ����
		FRotator Rot(0, 0, 0);
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ACEnemy>(EnemyFactory, Location, Rot, Params);
	}
}

