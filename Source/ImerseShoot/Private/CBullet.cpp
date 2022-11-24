// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"
#include <Components/BoxComponent.h>

// Sets default values
ACBullet::ACBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������Ʈ ���
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	// Collision ������Ʈ�� ��Ʈ�� ���
	RootComponent = Collision;
	Collision->SetBoxExtent(FVector(32, 12, 32));
	Collision->SetCollisionProfileName(TEXT("Bullet"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(Collision);
	BodyMesh->SetRelativeScale3D(FVector(1, 0.25f, 0.7f));
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BodyMesh StaticMesh ������ �Ҵ�
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	// �ε�Ϸ�Ǹ�
	if (TempMesh.Succeeded())
	{
		// BodyMesh �� �Ҵ�
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	// �ε�Ϸ�Ǹ�
	if (TempMat.Succeeded())
	{
		// BodyMesh �� �Ҵ�
		BodyMesh->SetMaterial(0, TempMat.Object);
	}
}

// Called when the game starts or when spawned
void ACBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// P = P0 + vt
	FVector P = GetActorLocation() + FVector::UpVector * speed * DeltaTime;
	SetActorLocation(P);
}

