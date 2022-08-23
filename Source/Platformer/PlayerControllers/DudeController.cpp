// Fill out your copyright notice in the Description page of Project Settings.


#include "DudeController.h"
#include "Blueprint/UserWidget.h"

void ADudeController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDBP != nullptr)
	{
		UWHUD = CreateWidget(this, HUDBP);
		if (UWHUD != nullptr)
		{
			UWHUD->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No HUDBP attached"));
	}
}

void ADudeController::SetPause(bool bIsGamePause)
{
	if (bIsGamePause)
	{
		if (PauseBP != nullptr)
		{
			UWPause = CreateWidget(this, PauseBP);
			if (UWPause != nullptr)
			{
				UWPause->AddToViewport();
			}
			UWHUD->RemoveFromViewport();
		}
	}
	else if (!bIsGamePause)
	{
		UWPause->RemoveFromViewport();
		UWHUD->AddToViewport();
	}
}