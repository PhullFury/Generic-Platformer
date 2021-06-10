// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerDude.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
APlatformerDude::APlatformerDude()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->JumpZVelocity = JumpSpeed;
}

// Called when the game starts or when spawned
void APlatformerDude::BeginPlay()
{
	Super::BeginPlay();

	GetCharacterMovement()->MaxWalkSpeed = CharacterSpeed;
	bIsSprinting = false;
	CurrentSpeedModifier = 1;
}

// Called every frame
void APlatformerDude::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetSpeed(DeltaTime);
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
	if (bIsSprinting)
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
	}
}