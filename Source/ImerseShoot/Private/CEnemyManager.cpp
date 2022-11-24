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

	// 일정시간에 한번씩 적을 만들고 싶다.
	// 1. 시간이 흘렀으니까
	CurrnetTime += DeltaTime;
	// 2. 생성시간이 됐으니까
	// 만약 경과시간이 생성시간을 초과했다면
	if (CurrnetTime > CreateTime)
	{
		CurrnetTime = 0;

		// 3. 적을 만든다.
		// 만들위치
		FVector Location = GetActorLocation();
		// 회전값
		FRotator Rot(0, 0, 0);
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<ACEnemy>(EnemyFactory, Location, Rot, Params);
	}
}

