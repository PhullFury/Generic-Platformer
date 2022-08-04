// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructibleBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestructibleBase::ADestructibleBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ADestructibleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestructibleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ADestructibleBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DestroyEffect != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DestroyEffect, GetActorLocation());
	}
	Destroy();

	return DamageAmount;
}