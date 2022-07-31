// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerActor.generated.h"

class ATriggerVolume;
class UStaticMeshComponent;
class APlatformerDude;

UCLASS()
class PLATFORMER_API ATriggerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	UPROPERTY(VisibleAnywhere, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		ATriggerVolume* TriggerArea;
	UPROPERTY(EditAnywhere, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		bool bDoesDamage = true;
	UPROPERTY()
		AActor* PlayerActor;
	UPROPERTY()
		APlatformerDude* Player;

	void ManageTrigger();

	bool bIsPlayerInvincible;
};