// Fill out your copyright notice in the Description page of Project Settings.


#include "BombAIController.h"

void ABombAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// Assign an enemy object
	PossessedEnemy = Cast<AEnemy>(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("ABombAIController possesses an enemy object at %s"), *PossessedEnemy->GetActorLocation().ToString());

	if (PossessedEnemy)
	{
		PossessedEnemy -> FiringBullet = false;
	}
}

void ABombAIController::OnUnPossess()
{
	Super::OnUnPossess();
	PossessedEnemy = nullptr;
}

void ABombAIController::Tick(float DeltaSeconds)
{
	if (IsValid(PossessedEnemy))
	{
		
		// Possessed enemy rotates for every TimerLimit seconds.
		// Initially, TimerLimit is set 3, so the enemy rotates in random direction in every 3 seconds
		Timer += DeltaSeconds;

		if (Timer > TimerLimit)
		{
			Timer = 0;
		
			// This will determine the rotation randomly
			int Rotation = FMath::RandRange(0, 359);

			// Set the possessed enemy rotation in Yaw
			PossessedEnemy -> SetActorRotation(FRotator(0, Rotation, 0));
		}
	
		FRotator CurrentRotation = PossessedEnemy -> GetActorRotation();
		FVector Direction = FVector(1, 0, 0);
		Direction.Normalize();

		FVector MovementDirection = CurrentRotation.RotateVector(Direction);

		FVector CurrentLocation = PossessedEnemy -> GetActorLocation();
		CurrentLocation += (MovementDirection*PossessedEnemy->MovementSpeed*DeltaSeconds);

		PossessedEnemy -> SetActorLocation(CurrentLocation);

		if (PossessedEnemy -> HasOverlapped)
		{
			CurrentLocation -= (MovementDirection*PossessedEnemy->MovementSpeed*DeltaSeconds*2);
			PossessedEnemy -> SetActorLocation(CurrentLocation);
			PossessedEnemy -> SetActorRotation(CurrentRotation + FRotator(0, 150, 0));
			PossessedEnemy -> HasOverlapped = false;
			Timer = 0;
		
		}
		
	}
}

