// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "ImerseShoot.h"
#include <Components/BoxComponent.h>
#include "CBullet.h"
#include <Kismet/GameplayStatics.h>

TArray<ACBullet*> ACPlayer::BulletPool;
// Sets default values
ACPlayer::ACPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// ������Ʈ ���
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	// Collision ������Ʈ�� ��Ʈ�� ���
	RootComponent = Collision;
	Collision->SetBoxExtent(FVector(50));
	Collision->SetCollisionProfileName(TEXT("Player"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(Collision);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BodyMesh->SetRelativeRotation(FRotator(0, 90, 90));
	BodyMesh->SetRelativeScale3D(FVector(6));
	// BodyMesh StaticMesh ������ �Ҵ�
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("StaticMesh'/Game/SpaceShip/Spaceship_ARA.Spaceship_ARA'"));

	// �ε�Ϸ�Ǹ�
	if(TempMesh.Succeeded())
	{
		// BodyMesh �� �Ҵ�
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	//ConstructorHelpers::FObjectFinder<UMaterialInterface> TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	//
	//// �ε�Ϸ�Ǹ�
	//if (TempMat.Succeeded())
	//{
	//	// BodyMesh �� �Ҵ�
	//	BodyMesh->SetMaterial(0, TempMat.Object);
	//}
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// �̸� �Ѿ��� ���� źâ�� �־����
	for (int32 i=0;i<BulletPoolSize;i++)
	{
		// 1. �Ѿ��� ������ �Ѵ�.
		auto Bullet = GetWorld()->SpawnActor<ACBullet>(BulletFactory, FVector(10000), FRotator(0, 0, 0), Params);
		// 2. źâ�� �Ѿ� �ֱ�
		BulletPool.Add(Bullet);
		// 3. ��Ȱ��ȭ ��������
		Bullet->SetActive(false);
	}
}

void ACPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// BulletPool �� �������
	ACPlayer::BulletPool.RemoveAll([&](const ACBullet* Bullet)
		{
			return true;
		}
	);
}

// Called every frame
void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �̵��ϰ� �ʹ�.
	// P = P0 + vt
	FVector P0 = GetActorLocation();
	FVector vt = direction * speed * DeltaTime;
	FVector P = P0 + vt;
	SetActorLocation(P);
}

// Called to bind functionality to input
void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// ����ڰ� ������ �Է¸��ΰ��� ó���� �Լ��� �����ִ� ��
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ACPlayer::Horizontal);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ACPlayer::Vertical);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ACPlayer::Fire);
}

void ACPlayer::Horizontal(float value)
{
	direction.Y = value;
}

void ACPlayer::Vertical(float value)
{
	direction.Z = value;
}

void ACPlayer::Fire()
{
	// ����ڰ� �߻��ư�� ������ �Ѿ� �߻��ϱ�
	//if (BulletFactory == nullptr)
	//{
	//	return;
	//}

	//// �Ѿ� �߻��ϱ�
	//FVector Location = GetActorLocation();
	//FActorSpawnParameters Params;
	//Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//GetWorld()->SpawnActor<ACBullet>(BulletFactory, Location, FRotator(0,0,0), Params);

	// źâ���� �Ѿ� �ϳ� ������ �߻��ϱ�
	if (BulletPool.Num() > 0)
	{
		auto Bullet = BulletPool[0];
		BulletPool.RemoveAt(0);
		// �ѱ���ġ�� ������ ����
		Bullet->SetActorLocation(GetActorLocation());
		Bullet->SetActive(true);
	}

	// �Ѿ� �߻� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), BulletSound);
}

