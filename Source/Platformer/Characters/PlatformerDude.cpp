// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerDude.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"

#define OUT

// Sets default values
APlatformerDude::APlatformerDude()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;

	//might add a reset camera
}

// Called when the game starts or when spawned
void APlatformerDude::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = CharacterSpeed;
	bIsSprinting = false;
	bCanTakeDamage = true;
	CurrentSpeedModifier = 1;
	Health = MaxHealth;
	UE_LOG(LogTemp, Warning, TEXT("Health: %i"), Health);
}

// Called every frame
void APlatformerDude::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSpeed(DeltaTime);
	StompAttack();
	if(ShowDebugStuff)
	{
		UE_LOG(LogTemp, Warning, TEXT("Current Speed Modifier: %f"), CurrentSpeedModifier);
	}
	if (GetWorld()->GetTimeSeconds() - DamageTime >= InvincibilityTimer)
	{
		bCanTakeDamage = true;
	}
}

// Called to bind functionality to input
void APlatformerDude::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Forward"), this, &APlatformerDude::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Sideways"), this, &APlatformerDude::MoveSideways);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookSideways"), this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Pressed, this, &APlatformerDude::StartSprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), EInputEvent::IE_Released, this, &APlatformerDude::StopSprint);
}

void APlatformerDude::MoveForward(float AxisValue)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, AxisValue);
}

void APlatformerDude::MoveSideways(float AxisValue)
{
	FRotator Rotation = Controller->GetControlRotation();
	FRotator YawRotation(0, Rotation.Yaw, 0);
	FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, AxisValue);
}

void APlatformerDude::StartSprint()
{
	bIsSprinting = true;
}

void APlatformerDude::StopSprint()
{
	bIsSprinting = false;
}

void APlatformerDude::SetSpeed(float DeltaTime)
{
	GetCharacterMovement()->MaxWalkSpeed = CurrentSpeedModifier*CharacterSpeed;
	if (bIsSprinting && !GetVelocity().IsZero())
	{
		CurrentSpeedModifier = FMath::FInterpTo(CurrentSpeedModifier, MaxSpeedModifier, DeltaTime, SpeedChange);
		if (CurrentSpeedModifier >= MaxSpeedModifier-0.2)
		{
			CurrentSpeedModifier = MaxSpeedModifier;
		}
	}
	else if (!bIsSprinting)
	{
		CurrentSpeedModifier = FMath::FInterpTo(CurrentSpeedModifier, 1, DeltaTime, SpeedChange);
		if (CurrentSpeedModifier <= 1.2)
		{
			CurrentSpeedModifier = 1;
		}
		if (GetVelocity().IsZero())
		{
			CurrentSpeedModifier = 1;
		}
	}
}

void APlatformerDude::StompAttack()
{
	if (GetCharacterMovement()->IsFalling())
	{
		TArray<FHitResult> StompHitResults;
		FVector TraceStart = GetActorLocation();
		FVector TraceEnd(TraceStart.X, TraceStart.Y, TraceStart.Z - CylinderHeight);
		FCollisionShape	TraceCylinder = FCollisionShape::MakeCapsule(CylinderRadius, CylinderHeight/2);
		TraceCylinder.GetExtent();
		FCollisionQueryParams StompParams;
		StompParams.AddIgnoredActor(this);

		bool bDidStomp = GetWorld()->SweepMultiByChannel(OUT StompHitResults, TraceStart, TraceEnd, FQuat::Identity, ECC_GameTraceChannel1, TraceCylinder, StompParams);
		if (bDidStomp)
		{
			FVector HitDirection = -TraceEnd;
			for (FHitResult StompResult : StompHitResults)
			{
				AActor* StompedActor = StompResult.GetActor();
				if (StompedActor != nullptr)
				{
					FPointDamageEvent StompEvent(StompDamage, StompResult, HitDirection, nullptr);
					StompedActor->TakeDamage(StompDamage, StompEvent, GetController(), this);
				}
			}
		}
		if (ShowDebugStuff)
		{
			FVector StartVector = GetActorLocation();
			FVector EndVector(StartVector.X, StartVector.Y, StartVector.Z - CylinderHeight);
			DrawDebugCylinder(GetWorld(), StartVector, EndVector, CylinderRadius, 16, FColor::Red, true);
		}		
	}
}

float APlatformerDude::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	if (bCanTakeDamage)
	{
		bCanTakeDamage = false;
		DamageTime = GetWorld()->GetTimeSeconds();
		Health -= DamageAmount;
		UE_LOG(LogTemp, Warning, TEXT("Current Health: %i"), Health);
	}

	return DamageAmount;
}

float APlatformerDude::GetHealthPerc()
{
	return Health / MaxHealth;
}

int32 APlatformerDude::GetHealthAct()
{
	return Health;
}