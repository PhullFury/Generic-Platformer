// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerActor.h"
#include "Engine/TriggerVolume.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Platformer/Characters/PlatformerDude.h"

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

	Player = Cast<APlatformerDude>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerActor = Cast<AActor>(Player);
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
		if (bDoesDamage)
		{
			ManageDamage();
		}		
		if (bIsFlagPost)
		{
			ManageFlag();
		}
	}
}

void ATriggerActor::ManageDamage()
{
	TArray<AActor*> Result;
	TriggerArea->GetOverlappingActors(OUT Result);
	for (AActor* OverlapActor : Result)
	{
		if (OverlapActor != this)
		{
			if (OverlapActor != PlayerActor)
			{
				FDamageEvent DamageEvent;
				OverlapActor->TakeDamage(TriggerDamage, DamageEvent, GetInstigatorController(), this);
				UE_LOG(LogTemp, Warning, TEXT("Non Player Damage"));
			}
			else if (OverlapActor == PlayerActor && !Player->GetInvincible())
			{
				FDamageEvent DamageEvent;
				OverlapActor->TakeDamage(TriggerDamage, DamageEvent, GetInstigatorController(), this);
				UE_LOG(LogTemp, Warning, TEXT("Player Damage"));
			}
		}

	}
}

void ATriggerActor::ManageFlag()
{
	TArray<AActor*> Result;
	TriggerArea->GetOverlappingActors(OUT Result);
	for (AActor* OverlapActor : Result)
	{
		if (OverlapActor != this)
		{
			if (OverlapActor == PlayerActor)
			{
				Player->GameEnd(true);
			}
		}
	}
}