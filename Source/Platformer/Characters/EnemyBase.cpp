// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEnemyBase::OnHit);

	Player = Cast<ACharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerActor = Cast<AActor>(Player);
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyBase::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("I am taking damage"));

	return DamageAmount;
}

void AEnemyBase::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == PlayerActor)
	{
		UGameplayStatics::ApplyDamage(OtherActor, BumpDamage, GetController(), this, DamageType);
	}
}