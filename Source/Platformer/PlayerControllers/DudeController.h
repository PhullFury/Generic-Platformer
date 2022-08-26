// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DudeController.generated.h"

class UUserWidget;

UCLASS()
class PLATFORMER_API ADudeController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget> HUDBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget> PauseBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget> WinBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UUserWidget> LoseBP;
	UPROPERTY()
		UUserWidget* UWHUD;
	UPROPERTY()
		UUserWidget* UWPause;
	UPROPERTY()
		UUserWidget* UWWin;
	UPROPERTY()
		UUserWidget* UWLose;

public:
	UFUNCTION(BlueprintCallable)
		void SetPause(bool bIsGamePause);

	void HandleGameEndScreen(bool bDidPlayerWin);
};