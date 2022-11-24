// Fill out your copyright notice in the Description page of Project Settings.


#include "CPlayer.h"
#include "ImerseShoot.h"
#include <Components/BoxComponent.h>
#include "CBullet.h"
#include <Kismet/GameplayStatics.h>

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
	if (BulletFactory == nullptr)
	{
		return;
	}

	// �Ѿ� �߻��ϱ�
	FVector Location = GetActorLocation();
	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<ACBullet>(BulletFactory, Location, FRotator(0,0,0), Params);

	// �Ѿ� �߻� ���� ���
	UGameplayStatics::PlaySound2D(GetWorld(), BulletSound);
}

