// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"

#define OUT

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = Mesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileMovement->ProjectileGravityScale = GravityScale;
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShowDebug)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 6, FColor::Red, true);
	}
}

void AProjectileBase::PDamage()
{
	TArray<FHitResult> SweepResults;
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation();
	
	//draw a cylinder as the trace shape instead of a circle cause how would a cirlce even work
	//start the cylinder at the center of the projectile and make it go slightyly longer than the radius of the projectile and slighlity thicker too
}