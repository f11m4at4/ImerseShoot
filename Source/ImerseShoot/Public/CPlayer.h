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
	// 사용자의 입력에따라 이동시키고 싶다.
	// 필요속성 : 이동속도, 방향
	UPROPERTY(EditAnywhere, Category="Settings")
	int32 speed = 500;

	UPROPERTY()
	FVector direction;

	// 코드에서 컴포넌트 추가하기
	UPROPERTY(VisibleAnywhere, Category="Components")
	class UBoxComponent* Collision;
	// staticmesh component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BodyMesh;

	// 사용자가 발사버튼을 누르면 총알을 쏘고싶다.
	// 총알공장
	UPROPERTY(EditDefaultsOnly, Category="Bullet")
	TSubclassOf<class ACBullet> BulletFactory;

	// 총알 발사 사운드
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	class USoundBase* BulletSound;
};

//디테일창
//Edit
//Visible
// - Anywhere 어디서든 수정가능하다. (클래스, 인스터스에서도)
// - DefaultsOnly BP 에디터
// - InstanceOnly 인스턴스 상태에서만
// 
// Graph 에서 사용
//BlueprintReadWrite
//BlueprintReadOnly
