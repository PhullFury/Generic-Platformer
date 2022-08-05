// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

#define OUT

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = Mesh;

	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particle"));
	TrailParticle->SetupAttachment(Mesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->ProjectileGravityScale = GravityScale;
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMovement->OnProjectileBounce.AddDynamic(this, &AProjectileBase::OnBounce);
	BounceCount = 0;
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShowDebug)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 6, FColor::Red, true);
	}

	PDamage();
}

void AProjectileBase::PDamage()
{
	TArray<FHitResult> SweepResults;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + Radius;
	FCollisionShape TraceSphere = FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams ProjectileParams;
	ProjectileParams.AddIgnoredActor(this);

	bool bDidHit;
	if (bIsPlayer)
	{
		bDidHit = GetWorld()->SweepMultiByChannel(OUT SweepResults, TraceStart, TraceEnd, FQuat::Identity, ECC_GameTraceChannel4, TraceSphere, ProjectileParams);
	}
	else if (!bIsPlayer)
	{
		bDidHit = GetWorld()->SweepMultiByChannel(OUT SweepResults, TraceStart, TraceEnd, FQuat::Identity, ECC_GameTraceChannel3, TraceSphere, ProjectileParams);
	}

	if (bDidHit)
	{
		FVector HitDirection = -TraceEnd;
		for (FHitResult SweepResult : SweepResults)
		{
			AActor* HitActor = SweepResult.GetActor();
			if (HitActor != nullptr && HitActor != GetOwner())
			{
				FPointDamageEvent ProjectileEvent(ProjectileDamage, SweepResult, HitDirection, nullptr);
				HitActor->TakeDamage(ProjectileDamage, ProjectileEvent, GetInstigatorController(), this);
				Destroy();
			}
		}
	}	
}

void AProjectileBase::OnBounce(const FHitResult& HitResult, const FVector& Vector)
{
	if (bIsPlayer)
	{
		BounceCount++;
		UE_LOG(LogTemp, Error, TEXT("Bounce number: %i"), BounceCount);
		if (BounceCount == MaxBounceCount)
		{
			Destroy();
		}
	}
}