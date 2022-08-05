// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

// Called when the game starts or when spawned
void APlatformerAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehaviorTree != nullptr)
	{
		RunBehaviorTree(AIBehaviorTree);
		GetBlackboardComponent()->SetValueAsVector(TEXT("WalkStartLocation"), GetPawn()->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("WalkEndLocation"), GetPawn()->GetActorLocation() + (GetPawn()->GetActorRotation().Vector() * WalkLength));
	}}