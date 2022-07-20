// Fill out your copyright notice in the Description page of Project Settings.


#include "DudeController.h"
#include "Blueprint/UserWidget.h"

void ADudeController::BeginPlay()
{
	Super::BeginPlay();

	if (HUDBP != nullptr)
	{
		HUD = CreateWidget(this, HUDBP);
		if (HUD != nullptr)
		{
			HUD->AddToViewport();
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No HUDBP attached"));
	}
}