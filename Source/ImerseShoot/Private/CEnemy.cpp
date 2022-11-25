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

	// ������Ʈ ���
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	// Collision ������Ʈ�� ��Ʈ�� ���
	RootComponent = Collision;
	Collision->SetBoxExtent(FVector(50));
	Collision->SetCollisionProfileName(TEXT("Enemy"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(Collision);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BodyMesh->SetRelativeLocation(FVector(-50, 0, 20));
	BodyMesh->SetRelativeRotation(FRotator(0, 270, -270));

	// BodyMesh StaticMesh ������ �Ҵ�
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("StaticMesh'/Game/Drone/Drone_low.Drone_low'"));

	// �ε�Ϸ�Ǹ�
	if (TempMesh.Succeeded())
	{
		// BodyMesh �� �Ҵ�
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	//ConstructorHelpers::FObjectFinder<UMaterialInterface> TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	//// �ε�Ϸ�Ǹ�
	//if (TempMat.Succeeded())
	//{
	//	// BodyMesh �� �Ҵ�
	//	BodyMesh->SetMaterial(0, TempMat.Object);
	//}
}

// Called when the game starts or when spawned
void ACEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Target = UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass());

	// ������Ʈ �浹 ����
	Collision->OnComponentBeginOverlap.AddDynamic(this, &ACEnemy::OnComponentBeginOverlap);

	int32 rand = FMath::RandRange(1, 10);
	// Ÿ���� �ִٸ� Ÿ�������� �̵��ϵ��� �ϰ�ʹ�.
	if (Target && rand < 6)
	{
		Direction = Target->GetActorLocation() - GetActorLocation();
		Direction.Normalize();
	}
	else
	{
		Direction = FVector::DownVector;
	}

	// Ÿ�ٹ������� ����ȸ����Ű��
	FRotator Rot = FRotationMatrix::MakeFromXY(Direction, GetActorRightVector()).Rotator();
	SetActorRotation(Rot);
}

// Ÿ���� ���� �̵��ϰ� �ʹ�.
// �ʿ�Ӽ� : Ÿ��, ����
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
	// �ε��� �༮�� DestoryZone �̸� �ƹ�ó���� ���� �ʴ´�.
	if (OtherActor->IsA(ADestroyZone::StaticClass()))
	{
		return;
	}

	// ����ȿ�� �߻���Ű��
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionFactory, GetActorLocation());

	// �ε��� �༮�� �Ѿ��̸�
	if (OtherActor->IsA(ACBullet::StaticClass()))
	{
		// źâ�� �ְ� �ʹ�.
		auto Bullet = Cast<ACBullet>(OtherActor);
		Bullet->SetActive(false);
		ACPlayer::BulletPool.Add(Bullet);
		// 1. Player �� �־�� �Ѵ�.
		/*auto Player = Cast<ACPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), ACPlayer::StaticClass()));
		if (Player != nullptr)
		{
			Player->BulletPool.Add(Bullet);
		}*/
	}
	else
	{
		// �ε��� �༮�� ���ְ�
		OtherActor->Destroy();
	}

	// ���� ��������.
	Destroy();
}

