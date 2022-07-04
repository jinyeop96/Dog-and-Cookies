// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DogkieCharacter.h"
#include "Pet.h"
#include "PetAIController.generated.h"

/**
 * 
 */
UCLASS()
class DOGKIE_API APetAIController : public AAIController
{
	GENERATED_BODY()

public:
	APet* PossessedPet;
	ACharacter* Owner;

	

	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

	FTimerHandle HealthDecrementTimerHandle;


private:
	float TimerLimit = 3;
	float Timer = 0;
	float RotateRight = true;

	void CheckDistanceBetweenOwner(FVector PetLocation, FVector OwnerLocation, FRotator PetRotation);

	void OnTimedHealthDecrement();
};
