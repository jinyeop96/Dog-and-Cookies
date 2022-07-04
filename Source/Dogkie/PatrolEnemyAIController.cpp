// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolEnemyAIController.h"

void APatrolEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// Assign an enemy object
	PossessedEnemy = Cast<AEnemy>(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("APatrolEnemyAIController possesses an enemy object at %s"), *PossessedEnemy->GetActorLocation().ToString());
	
}

void APatrolEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	PossessedEnemy = nullptr;
}


void APatrolEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsValid(PossessedEnemy))
	{
		// Set the Timer
		Timer += DeltaSeconds;
		
		// Get an unit vector  
		FVector Movement = FVector(1, 0, 0);
		Movement.Normalize();

		// Rotate the unit vector to get direction that the possessed enemy looking at
		FRotator CurrentRotation = PossessedEnemy -> GetActorRotation();
		FVector Direction = CurrentRotation.RotateVector(Movement);

		// Move forward
		FVector CurrentLocation = PossessedEnemy-> GetActorLocation();
		CurrentLocation += (Direction * PossessedEnemy -> MovementSpeed * DeltaSeconds);
		
		PossessedEnemy -> SetActorLocation(CurrentLocation);
		
		// If it overlaps with something, it should turn around
		if (PossessedEnemy -> HasOverlapped)
		{
			CurrentLocation -= (Direction * PossessedEnemy -> MovementSpeed * DeltaSeconds*2);
			PossessedEnemy -> SetActorLocation(CurrentLocation);

			// Turn around
			PossessedEnemy -> SetActorRotation(CurrentRotation + FRotator(0, 180, 0));
			PossessedEnemy -> HasOverlapped = false;
		} else if (Timer > TimerLimit )
		{
			Timer = 0;
			
			// Turn around
			PossessedEnemy -> SetActorRotation(CurrentRotation + FRotator(0, 180, 0));
		}
		
		
		
	}
}
