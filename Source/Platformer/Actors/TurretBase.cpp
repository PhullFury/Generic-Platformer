// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretBase.h"
#include "Platformer/Actors/ProjectileBase.h"

// Sets default values
ATurretBase::ATurretBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = Mesh;

	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	SpawnPoint->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ATurretBase::BeginPlay()
{
	Super::BeginPlay();
	
	bCanShoot = true;
	TimeSinceShoot = GetWorld()->GetTimeSeconds();
}

// Called every frame
void ATurretBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld()->GetTimeSeconds() - TimeSinceShoot >= ShootTimer)
	{
		Shoot();
		//bCanShoot = true;
	}

	/*if (bCanShoot)
	{
		Shoot();
		bCanShoot = false;
		TimeSinceShoot = GetWorld()->GetTimeSeconds();
	}*/
}

void ATurretBase::Shoot()
{
	AProjectileBase* Bullet = GetWorld()->SpawnActor<AProjectileBase>(Projectile, SpawnPoint->GetComponentLocation(), SpawnPoint->GetComponentRotation());
	Bullet->SetOwner(this);
	TimeSinceShoot = GetWorld()->GetTimeSeconds();	
}