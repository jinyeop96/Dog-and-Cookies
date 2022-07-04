// Fill out your copyright notice in the Description page of Project Settings.


#include "StationaryEnemyAIController.h"

#include "Enemy.h"

void AStationaryEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// Assign an enemy object
	PossessedEnemy = Cast<AEnemy>(InPawn);
	UE_LOG(LogTemp, Warning, TEXT("AStationaryEnemyAIController possesses an enemy object at %s"), *PossessedEnemy->GetActorLocation().ToString());
	
}

void AStationaryEnemyAIController::OnUnPossess()
{
	Super::OnUnPossess();
	PossessedEnemy = nullptr;
}


void AStationaryEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsValid(PossessedEnemy))
	{
		Timer += DeltaSeconds;
		
		FRotator CurrentRotation = PossessedEnemy -> GetActorRotation();

		// Rotate possessed enemy to the right
		if (RotateRight)
		{
			PossessedEnemy -> SetActorRotation(CurrentRotation + FRotator(0, PossessedEnemy->RotationSpeed * DeltaSeconds, 0));
		} else // Rotate possessed enemy to the left
		{
			PossessedEnemy -> SetActorRotation(CurrentRotation + FRotator(0, -PossessedEnemy->RotationSpeed * DeltaSeconds, 0));
		}
		
		// Start rotate the other way in every 5 seconds
		if (Timer > TimerLimit)
		{
			Timer = 0;
			RotateRight = !RotateRight;

			UE_LOG(LogTemp, Warning, TEXT("AStationaryEnemyAIController's enemy object started rotating to the other direction"));
		}

		
	}
}
