// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActor.h"
#include "Engine/TriggerVolume.h"
#include "Kismet/GameplayStatics.h"

#define OUT

// Sets default values
ATriggerActor::ATriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (TriggerArea != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("It works"));
	}
}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ManageTrigger();
}

void ATriggerActor::ManageTrigger()
{
	if (TriggerArea != nullptr)
	{
		TArray<AActor*> Result;
		TriggerArea->GetOverlappingActors(OUT Result);
		for (AActor* OverlapActor : Result)
		{
			FDamageEvent DamageEvent;
			OverlapActor->TakeDamage(1, DamageEvent, GetInstigatorController(), this);
		}
	}
}