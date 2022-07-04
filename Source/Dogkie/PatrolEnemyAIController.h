// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Enemy.h"
#include "PatrolEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DOGKIE_API APatrolEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemy* PossessedEnemy;
	

	virtual void Tick(float DeltaSeconds) override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	float TimerLimit = 5;
	float Timer = 0;
};
