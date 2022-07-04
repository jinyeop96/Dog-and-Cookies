// Fill out your copyright notice in the Description page of Project Settings.


#include "PetAIController.h"

#include "Kismet/GameplayStatics.h"

void APetAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedPet = Cast<APet>(InPawn);
	GetWorld()->GetTimerManager().SetTimer(HealthDecrementTimerHandle, this, &APetAIController::OnTimedHealthDecrement, 3, true);
}

void APetAIController::OnUnPossess()
{
	Super::OnUnPossess();
	PossessedPet = nullptr;
}


void APetAIController::Tick(float DeltaSeconds)
{
	if (! Owner )
	{
		// Get reference to player's character
		TArray<AActor*> ActorsToFind;

		if(UWorld* World = GetWorld())
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsToFind);
		}

		for(auto Actor: ActorsToFind)
		{
			if (Cast<ADogkieCharacter>(Actor))
			{
				Owner = Cast<ADogkieCharacter>(Actor);
			}
			
		}
	}

	FVector OwnerLocation =  Owner -> GetActorLocation();
	FVector PetLocation = PossessedPet -> GetActorLocation();
	FRotator PetRotation =  PossessedPet ->GetActorRotation();

	if (IsValid(PossessedPet) && PossessedPet -> HasOverlapped)
	{
		PossessedPet -> SetActorRotation(PetRotation + FRotator(0, 180, 0));
		PossessedPet -> HasOverlapped = false;
		PossessedPet -> HasBeenCalled = false;
		return;
	}

	// Follow the owner when it has been called 
	if (IsValid(PossessedPet) && PossessedPet->HasBeenCalled )
	{
		Timer = 0;
		
		// Get direction
		FVector Direction = OwnerLocation -PetLocation;
		Direction.Normalize();

		// Rotate the pet
		FRotator Rotation = Direction.Rotation() + FRotator(0, -90, 0);
		Rotation.Roll = 0;
		Rotation.Pitch = 0;
		PossessedPet -> SetActorRotation(Rotation);
		
		// Move forward and set new location
		PetLocation += (Direction * PossessedPet -> MovementSpeed * DeltaSeconds);
		PetLocation.Z = 0;	// Preventing the pet flies over the air
		PossessedPet -> SetActorLocation(PetLocation);

		// If pet reaches the owner within a set distance
		CheckDistanceBetweenOwner(PetLocation, OwnerLocation, PetRotation);
		
	} else if( IsValid(PossessedPet) && !(PossessedPet->HasBeenCalled)) // Pet wanders around randomly
	{
		// If owner is around, stop wandering
		if (  FVector::Distance(PetLocation, OwnerLocation) < 300 )
		{
			return ;
		}
		
		Timer += DeltaSeconds;
		
		if (Timer > TimerLimit)
		{
			Timer = 0;

			// Set different turning timing for the next time
			TimerLimit = FMath::RandRange(1, 5);

			// Turn left or right
			RotateRight = !RotateRight;
		}
		
		// Get unit vector and rotate in proper direction
		FVector Movement = FVector(1, 0, 0);
		Movement.Normalize();
		FVector Direction = (PetRotation + FRotator(0, 90, 0)).RotateVector(Movement);

		// Set the new location
		PetLocation += (Direction * (PossessedPet -> MovementSpeed)/2 * DeltaSeconds);
		PossessedPet ->SetActorLocation(PetLocation);

		// If pet reaches the owner within a set distance
		CheckDistanceBetweenOwner(PetLocation, OwnerLocation, PetRotation);

		// Rotate the pet in proper direction
		FRotator RotationAmount;
		if (RotateRight)
		{
			RotationAmount = FRotator(0,  PossessedPet -> RotationAmount * PossessedPet->RotationSpeed * DeltaSeconds, 0);
		} else
		{
			RotationAmount = FRotator(0, -PossessedPet -> RotationAmount * PossessedPet->RotationSpeed * DeltaSeconds, 0);
		}
		
		PossessedPet->AddActorLocalRotation(RotationAmount);
	}

	
}

void APetAIController::CheckDistanceBetweenOwner(FVector PetLocation, FVector OwnerLocation, FRotator PetRotation)
{
	if (FVector::Distance(PetLocation, OwnerLocation) < 170 )
	{
		// Following process completed
		PossessedPet -> HasBeenCalled = false;
		
		PetRotation += FRotator(0, FMath::RandRange(80, 260),0);
		PetRotation.Pitch = 0;
		PetRotation.Roll = 0;
		PossessedPet ->SetActorRotation(PetRotation);
	} 
}

void APetAIController::OnTimedHealthDecrement()
{
	PossessedPet -> DecrementHealth(1);
}


