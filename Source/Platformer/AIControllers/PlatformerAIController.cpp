// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Called when the game starts or when spawned
void APlatformerAIController::BeginPlay()
{
	Super::BeginPlay();

	bIsPlayerInSight = false;
	bCanCall = false;
	Player = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	if (AIBehaviorTree != nullptr)
	{
		RunBehaviorTree(AIBehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("WalkStartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("WalkEndLocation"), GetPawn()->GetActorLocation() + (GetPawn()->GetActorRotation().Vector() * WalkLength));
	}
}

void APlatformerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (AIBehaviorTree != nullptr)
	{
		if (bIsPlayerInSight)
		{
			GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), Player->GetActorLocation());
			GetBlackboardComponent()->ClearValue(TEXT("LastPlayerLocation"));
			bCanCall = true;
		}
		else if (!bIsPlayerInSight)
		{
			GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
			if (bCanCall)
			{
				GetBlackboardComponent()->SetValueAsVector(TEXT("LastPlayerLocation"), Player->GetActorLocation());
				bCanCall = false;
			}
		}
	}
}