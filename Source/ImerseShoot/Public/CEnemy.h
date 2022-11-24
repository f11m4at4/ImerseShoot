// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemy.generated.h"

UCLASS()
class IMERSESHOOT_API ACEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// ���� ��� �ö󰡰� �ʹ�.
	UPROPERTY(EditAnywhere, Category = "Settings")
	float speed = 500;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* Collision;
	// staticmesh component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BodyMesh;

	// �ʿ�Ӽ� : Ÿ��, ����
	UPROPERTY(EditAnywhere)
	class AActor* Target;
	FVector Direction;

	// ����ȿ������
	UPROPERTY(EditAnywhere, Category="Settings")
	class UParticleSystem* ExplosionFactory;
	
public:
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
