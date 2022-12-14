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

	// 컴포넌트 등록
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	// Collision 컴포넌트를 루트로 등록
	RootComponent = Collision;
	Collision->SetBoxExtent(FVector(50));
	Collision->SetCollisionProfileName(TEXT("Player"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	BodyMesh->SetupAttachment(Collision);
	BodyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BodyMesh->SetRelativeRotation(FRotator(0, 90, 90));
	BodyMesh->SetRelativeScale3D(FVector(6));
	// BodyMesh StaticMesh 데이터 할당
	ConstructorHelpers::FObjectFinder<UStaticMesh> TempMesh(TEXT("StaticMesh'/Game/SpaceShip/Spaceship_ARA.Spaceship_ARA'"));

	// 로드완료되면
	if(TempMesh.Succeeded())
	{
		// BodyMesh 에 할당
		BodyMesh->SetStaticMesh(TempMesh.Object);
	}

	//ConstructorHelpers::FObjectFinder<UMaterialInterface> TempMat(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	//
	//// 로드완료되면
	//if (TempMat.Succeeded())
	//{
	//	// BodyMesh 에 할당
	//	BodyMesh->SetMaterial(0, TempMat.Object);
	//}
}

// Called when the game starts or when spawned
void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters Params;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	// 미리 총알을 만들어서 탄창에 넣어놓자
	for (int32 i=0;i<BulletPoolSize;i++)
	{
		// 1. 총알을 만들어야 한다.
		auto Bullet = GetWorld()->SpawnActor<ACBullet>(BulletFactory, FVector(10000), FRotator(0, 0, 0), Params);
		// 2. 탄창에 총알 넣기
		BulletPool.Add(Bullet);
		// 3. 비활성화 시켜주자
		Bullet->SetActive(false);
	}
}

void ACPlayer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// BulletPool 을 비워주자
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

	// 이동하고 싶다.
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

	// 사용자가 정의한 입력매핑값과 처리할 함수를 묶어주는 곳
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
	// 상용자가 발사버튼을 누르면 총알 발사하기
	//if (BulletFactory == nullptr)
	//{
	//	return;
	//}

	//// 총알 발사하기
	//FVector Location = GetActorLocation();
	//FActorSpawnParameters Params;
	//Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	//GetWorld()->SpawnActor<ACBullet>(BulletFactory, Location, FRotator(0,0,0), Params);

	// 탄창에서 총알 하나 꺼내서 발사하기
	if (BulletPool.Num() > 0)
	{
		auto Bullet = BulletPool[0];
		BulletPool.RemoveAt(0);
		// 총구위치에 가져다 놓기
		Bullet->SetActorLocation(GetActorLocation());
		Bullet->SetActive(true);
	}

	// 총알 발사 사운드 재생
	UGameplayStatics::PlaySound2D(GetWorld(), BulletSound);
}

