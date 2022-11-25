// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemyManager.generated.h"

// �����ð��� �ѹ��� ���� ����� �ʹ�.
// �ʿ�Ӽ� : ������, �����ð�, ����ð�
UCLASS()
class IMERSESHOOT_API ACEnemyManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemyManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	// �ʿ�Ӽ� : ������, �����ð�, ����ð�
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<class ACEnemy> EnemyFactory;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Settings", meta=(AllowPrivateAccess = true))
	float CreateTime = 2;

	float CurrnetTime = 0;
};
