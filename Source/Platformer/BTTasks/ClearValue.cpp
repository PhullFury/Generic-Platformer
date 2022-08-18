// Fill out your copyright notice in the Description page of Project Settings.


#include "ClearValue.h"
#include "BehaviorTree/BlackboardComponent.h"

UClearValue::UClearValue()
{
	NodeName = TEXT("Clear Value");
}

EBTNodeResult::Type UClearValue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

	return EBTNodeResult::Succeeded;
}