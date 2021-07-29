// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomMovComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API UCustomMovComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCustomMovComp();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Movement")
		float StopTime = 2.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float MoveDist = 200.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float MoveSpeed = 2.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		float MinDist = 5.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool bMoveX = true;
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool bMoveY = false;
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool bMoveZ = false;
	UPROPERTY(EditAnywhere, Category = "Movement")
		bool bPositiveMove = true;

	FVector OwnerLocation;
	bool bCanMove;
	bool bIsTurn;
	float TimeSinceStop;
	float CurrentX;
	float CurrentY;
	float CurrentZ;

	void HandleMoveEnd();
	void Movement(float DeltaTime);
	void PositiveMovement(float DeltaTime);
	void NegativeMovement(float DeltaTime);
};