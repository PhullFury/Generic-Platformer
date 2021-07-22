// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupBase.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values
APickupBase::APickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void APickupBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShowDebug)
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 12, FColor::Red, false, 0.2);
	}
	Pickup();
}

void APickupBase::Pickup()
{
	TArray<FHitResult> PickupResults;
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd(TraceStart.X, TraceStart.Y, TraceStart.Z + 0.001);
	FCollisionShape TraceSphere = FCollisionShape::MakeSphere(Radius);
	FCollisionQueryParams PickupParams;
	PickupParams.AddIgnoredActor(this);

	bool bDidPickup = GetWorld()->SweepMultiByChannel(OUT PickupResults, TraceStart, TraceEnd, FQuat::Identity, ECC_GameTraceChannel2, TraceSphere, PickupParams);
	
	if (bDidPickup)
	{
		UE_LOG(LogTemp, Error, TEXT("Player picked me up"));
	}
}