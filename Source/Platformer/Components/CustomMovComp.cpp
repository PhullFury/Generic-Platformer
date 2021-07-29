// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMovComp.h"

// Sets default values for this component's properties
UCustomMovComp::UCustomMovComp()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

// Called when the game starts
void UCustomMovComp::BeginPlay()
{
	Super::BeginPlay();

	OwnerLocation = GetOwner()->GetActorLocation();
	CurrentX = OwnerLocation.X;
	CurrentY = OwnerLocation.Y;
	CurrentZ = OwnerLocation.Z;
	bCanMove = true;
	bIsTurn = true;
}

// Called every frame
void UCustomMovComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetWorld()->GetTimeSeconds() - TimeSinceStop >= StopTime)
	{
		bCanMove = true;
	}
	Movement(DeltaTime);
}

void UCustomMovComp::Movement(float DeltaTime)
{
	if (bCanMove)
	{
		if (bPositiveMove)
		{
			if (bIsTurn)
			{
				PositiveMovement(DeltaTime);
			}
			else if (!bIsTurn)
			{
				NegativeMovement(DeltaTime);
			}
		}
		else if (!bPositiveMove)
		{
			if (bIsTurn)
			{
				NegativeMovement(DeltaTime);
			}
			else if (!bIsTurn)
			{
				PositiveMovement(DeltaTime);
			}
		}
	}
}

void UCustomMovComp::PositiveMovement(float DeltaTime)
{
	FVector NewOwnerLocation = GetOwner()->GetActorLocation();
	if (bMoveX)
	{
		float EndX = OwnerLocation.X + MoveDist;
		CurrentX = FMath::FInterpTo(CurrentX, EndX, DeltaTime, MoveSpeed);
		if (CurrentX >= EndX - MinDist)
		{
			CurrentX = EndX;
			HandleMoveEnd();
		}
		NewOwnerLocation.X = CurrentX;
	}
	else if (bMoveY)
	{
		float EndY = OwnerLocation.Y + MoveDist;
		CurrentY = FMath::FInterpTo(CurrentY, EndY, DeltaTime, MoveSpeed);
		if (CurrentY >= EndY - MinDist)
		{
			CurrentY = EndY;
			HandleMoveEnd();
		}
		NewOwnerLocation.Y = CurrentY;
	}
	else if (bMoveZ)
	{
		float EndZ = OwnerLocation.Z + MoveDist;
		CurrentZ = FMath::FInterpTo(CurrentZ, EndZ, DeltaTime, MoveSpeed);
		if (CurrentZ >= EndZ - MinDist)
		{
			CurrentZ = EndZ;
			HandleMoveEnd();
		}
		NewOwnerLocation.Z = CurrentZ;
	}
	GetOwner()->SetActorLocation(NewOwnerLocation);
}

void UCustomMovComp::NegativeMovement(float DeltaTime)
{
	FVector NewOwnerLocation = GetOwner()->GetActorLocation();
	if (bMoveX)
	{
		float EndX = OwnerLocation.X - MoveDist;
		CurrentX = FMath::FInterpTo(CurrentX, EndX, DeltaTime, MoveSpeed);
		if (CurrentX <= EndX + MinDist)
		{
			CurrentX = EndX;
			HandleMoveEnd();
		}
		NewOwnerLocation.X = CurrentX;
	}
	else if (bMoveY)
	{
		float EndY = OwnerLocation.Y - MoveDist;
		CurrentY = FMath::FInterpTo(CurrentY, EndY, DeltaTime, MoveSpeed);
		if (CurrentY <= EndY + MinDist)
		{
			CurrentY = EndY;
			HandleMoveEnd();
		}
		NewOwnerLocation.Y = CurrentY;
	}
	else if (bMoveZ)
	{
		float EndZ = OwnerLocation.Z - MoveDist;
		CurrentZ = FMath::FInterpTo(CurrentZ, EndZ, DeltaTime, MoveSpeed);
		if (CurrentZ <= EndZ + MinDist)
		{
			CurrentZ = EndZ;
			HandleMoveEnd();
		}
		NewOwnerLocation.Z = CurrentZ;
	}
	GetOwner()->SetActorLocation(NewOwnerLocation);
}

void UCustomMovComp::HandleMoveEnd()
{
	TimeSinceStop = GetWorld()->GetTimeSeconds();
	OwnerLocation = GetOwner()->GetActorLocation();
	bCanMove = false;
	if (bIsTurn)
	{
		bIsTurn = false;
	}
	else if (!bIsTurn)
	{
		bIsTurn = true;
	}
}