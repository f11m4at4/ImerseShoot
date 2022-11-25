// Fill out your copyright notice in the Description page of Project Settings.


#include "CEnemy.h"
#include <Components/BoxComponent.h>
#include "../Public/CPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "CBullet.h"
#include "DestroyZone.h"
// Sets default values
ACEnemy::ACEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 컴포넌트 등록
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	// Collision 컴포넌트를 루트로 등록
	RootComponent = Collision;
	Collision->SetBoxExtent(FVector(50));
	Collision->SetCollisionProfileName(TEXT("Enemy"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(Collision);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BodyMesh->SetRelativeLocation(FVector(-50, 0, 20));
	BodyMesh->SetRelativeRotation(FRotator(0, 270, -270));

	// BodyMesh StaticMesh 데이터 할당
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("StaticMesh'/Game/Drone/Drone_low.Drone_low'"));

	// 로드완료되면
	if (TempMesh.Succeeded())
	{
		// BodyMesh 에 할당
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	//ConstructorHelpers::FObjectFinder<UMaterialInterface> TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	//// 로드완료되면
	//if (TempMat.Succeeded())
	//{
	//	// BodyMesh 에 할당
	//	BodyMesh->SetMaterial(0, TempMat.Object);
	//}
}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Target = UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass());

	// 컴포넌트 충돌 설정
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnComponentBeginOverlap);

	int32 rand = FMath::RandRange(1, 10);
	// 타겟이 있다면 타겟쪽으로 이동하도록 하고싶다.
	if (Target && rand < 6)
	{
		Direction = Target->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
	}
	else
	{
		Direction = FVector::DownVector;
	}

	// 타겟방향으로 액터회전시키기
	FRotator Rot = FRotationMatrix::MakeFromXY(Direction, GetActorRightVector()).Rotator();
	SetActorRotation(Rot);
}

// 타겟을 따라서 이동하고 싶다.
// 필요속성 : 타겟, 방향
// Called every frame
void ACEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// P = P0 + vt
	FVector P = GetActorLocation() + Direction * speed * DeltaTime;
	SetActorLocation(P);

}

void ACEnemy::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 부딪힌 녀석이 DestoryZone 이면 아무처리도 하지 않는다.
	if (OtherActor->IsA(ADestroyZone::StaticClass()))
	{
		return;
	}

	// 폭발효과 발생시키기
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFactory, GetActorLocation());

	// 부딪힌 녀석이 총알이면
	if (OtherActor->IsA(ACBullet::StaticClass()))
	{
		// 탄창에 넣고 싶다.
		auto Bullet = Cast<ACBullet>(OtherActor);
		Bullet->SetActive(false);
		ACPlayer::BulletPool.Add(Bullet);
		// 1. Player 가 있어야 한다.
		/*auto Player = Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass()));
		if (Player != nullptr)
		{
			Player->BulletPool.Add(Bullet);
		}*/
	}
	else
	{
		// 부딪힌 녀석을 없애고
		OtherActor->Destroy();
	}

	// 나도 없어지자.
	Destroy();
}

