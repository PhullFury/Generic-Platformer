// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

#define OUT

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = Mesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	//Mesh->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	ProjectileMovement->ProjectileGravityScale = GravityScale;
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	InitialLifeSpan = LifeSpan;
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

	bool bDidHit = GetWorld()->SweepMultiByChannel(OUT SweepResults, TraceStart, TraceEnd, FQuat::Identity, ECC_GameTraceChannel3, TraceSphere, ProjectileParams);

	if (bDidHit)
	{
		FVector HitDirection = -TraceEnd;
		for (FHitResult SweepResult : SweepResults)
		{
			AActor* HitActor = SweepResult.GetActor();
			if (HitActor != nullptr)
			{
				FPointDamageEvent ProjectileEvent(ProjectileDamage, SweepResult, HitDirection, nullptr);
				HitActor->TakeDamage(ProjectileDamage, ProjectileEvent, GetInstigatorController(), this);
			}
		}
	}

	Destroy();
}

void AProjectileBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("OnHit is being called"));

	AActor* MyOwner = GetOwner();
	if (!MyOwner)
	{
		return;
	}

	if (OtherActor && OtherActor != MyOwner && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, ProjectileDamage, GetInstigatorController(), this, DamageType);
	}
	Destroy();
}

//try this onhit method next time