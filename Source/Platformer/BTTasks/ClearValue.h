// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ClearValue.generated.h"

UCLASS()
class PLATFORMER_API UClearValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UClearValue();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};