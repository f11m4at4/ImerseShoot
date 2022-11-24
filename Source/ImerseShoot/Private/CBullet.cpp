// Fill out your copyright notice in the Description page of Project Settings.


#include "CBullet.h"
#include <Components/BoxComponent.h>

// Sets default values
ACBullet::ACBullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 등록
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	// Collision 컴포넌트를 루트로 등록
	RootComponent = Collision;
	Collision->SetBoxExtent(FVector(32, 12, 32));
	Collision->SetCollisionProfileName(TEXT("Bullet"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(Collision);
	BodyMesh->SetRelativeScale3D(FVector(1, 0.25f, 0.7f));
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// BodyMesh StaticMesh 데이터 할당
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));

	// 로드완료되면
	if (TempMesh.Succeeded())
	{
		// BodyMesh 에 할당
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	// 로드완료되면
	if (TempMat.Succeeded())
	{
		// BodyMesh 에 할당
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

