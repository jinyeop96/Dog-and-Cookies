// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DogkieCharacter.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class DOGKIE_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* EnemyBody;

	UPROPERTY(EditAnywhere)
	UCapsuleComponent* EnemyCapsuleComponent;

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 250;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 20;

	bool HasOverlapped = false;

	bool FiringBullet = true;
	
	float TimerLimit = 3;
	float Timer = 0;

	UPROPERTY(EditAnywhere, Category= Projectile)
	TSubclassOf<class ABullet> BulletClass;

	UPROPERTY(EditAnywhere, Category= Projectile)
	TSubclassOf<class ABomb> BombClass;

	ADogkieCharacter* PlayerCharacter = nullptr;
	APet* PlayerPet = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	 UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void FireBullet(FVector StartPosition);

	void FireBomb(FVector StartPosition);
};