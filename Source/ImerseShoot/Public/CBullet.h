// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CBullet.generated.h"

UCLASS()
class IMERSESHOOT_API ACBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 위로 계속 올라가고 싶다.
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	float speed = 1000;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* Collision;
	// staticmesh component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* BodyMesh;
};
