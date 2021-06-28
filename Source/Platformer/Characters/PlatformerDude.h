// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlatformerDude.generated.h"

UCLASS()
class PLATFORMER_API APlatformerDude : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlatformerDude();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
		float CharacterSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
		float JumpSpeed = 600.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
		float MaxSpeedModifier = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
		float SpeedChange = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "General", meta = (AllowPrivateAccess = true))
		bool ShowDebugStuff = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = true))
		float CylinderHeight = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = true))
		float CylinderRadius = 60.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = true))
		float StompDamage = 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = true))
		float InvincibilityTimer = 1.5;

	void MoveForward(float AxisValue);
	void MoveSideways(float AxisValue);
	void StartSprint();
	void StopSprint();
	void SetSpeed(float DeltaTime);
	void StompAttack();

	bool bIsSprinting;
	bool bCanTakeDamage;
	float CurrentSpeedModifier;
	float DamageTime;
};