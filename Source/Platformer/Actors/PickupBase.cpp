// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Platformer/Characters/PlatformerDude.h"

#define OUT

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);

	TraceSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Trace Spawn Point"));
	TraceSpawnPoint->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlatformerDude>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerActor = Cast<AActor>(Player);
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShowDebug)
	{
		DrawDebugSphere(GetWorld(), TraceSpawnPoint->GetComponentLocation(), Radius, 12, FColor::Red, false, 0.2);
	}
	Pickup();
}

void APickupBase::Pickup()
{
	TArray<FHitResult> PickupResults;
	FVector TraceStart = TraceSpawnPoint->GetComponentLocation();
	FVector TraceEnd(TraceStart.X, TraceStart.Y, TraceStart.Z + 0.001);
	FCollisionShape TraceSphere = FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams PickupParams;
	PickupParams.AddIgnoredActor(this);

	bool bDidPickup = GetWorld()->SweepMultiByChannel(OUT PickupResults, TraceStart, TraceEnd, FQuat::Identity, ECC_GameTraceChannel2, TraceSphere, PickupParams);
	
	if (bDidPickup)
	{
		UE_LOG(LogTemp, Error, TEXT("Player picked me up"));
		if (bIsHealthPickup)
		{
			UE_LOG(LogTemp, Error, TEXT("I am a health pickup btw"));
			Player->SetHealth();
		}
		else if (bIsDJumpPickup)
		{
			UE_LOG(LogTemp, Error, TEXT("I am a double jump pickup btw"));
			Player->SetDJump(true);
		}
		else if (bIsDInvPickup)
		{
			UE_LOG(LogTemp, Error, TEXT("I am a invincible pickup btw"));
			Player->SetInvincible(true);
		}
		Destroy();
	}	
}