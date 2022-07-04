// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "StationaryEnemyAIController.generated.h"

class AEnemy;
/**
 * 
 */
UCLASS()
class DOGKIE_API AStationaryEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemy* PossessedEnemy;
	
	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	
	float TimerLimit = 5;
	float Timer = 0;
	bool RotateRight = true;
};
