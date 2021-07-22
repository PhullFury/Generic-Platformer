// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class PLATFORMER_API APickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickupBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:	
	UPROPERTY(VisibleAnywhere, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		bool bShowDebug = false;
	UPROPERTY(EditAnywhere, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		float Radius = 10.f;
	UPROPERTY(EditAnywhere, Category = "Basic", meta = (AllowPrivateAccess = "true"))
		float RadiusMulti = 2.f;

	void Pickup();
};