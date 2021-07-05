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
}