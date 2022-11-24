// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CPlayer.generated.h"

UCLASS()
class IMERSESHOOT_API ACPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Horizontal(float value);
	void Vertical(float value);
	void Fire();

public:
	// ������� �Է¿����� �̵���Ű�� �ʹ�.
	// �ʿ�Ӽ� : �̵��ӵ�, ����
	UPROPERTY(EditAnywhere, Category="Settings")
	int32 speed = 500;

	UPROPERTY()
	FVector direction;

	// �ڵ忡�� ������Ʈ �߰��ϱ�
	UPROPERTY(VisibleAnywhere, Category="Components")
	class UBoxComponent* Collision;
	// staticmesh component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BodyMesh;

	// ����ڰ� �߻��ư�� ������ �Ѿ��� ���ʹ�.
	// �Ѿ˰���
	UPROPERTY(EditDefaultsOnly, Category="Bullet")
	TSubclassOf<class ACBullet> BulletFactory;

	// �Ѿ� �߻� ����
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	class USoundBase* BulletSound;
};

//������â
//Edit
//Visible
// - Anywhere ��𼭵� ���������ϴ�. (Ŭ����, �ν��ͽ�������)
// - DefaultsOnly BP ������
// - InstanceOnly �ν��Ͻ� ���¿�����
// 
// Graph ���� ���
//BlueprintReadWrite
//BlueprintReadOnly
