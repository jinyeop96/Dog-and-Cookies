// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ChasingEmenyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DOGKIE_API AChasingEmenyAIController : public AAIController
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AI)
	float SightRadius = 500;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AI)
	float SightAge = 3.5;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AI)
	float LoseSightRadius = SightRadius + 30;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AI)
	float FieldOfView = 45;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=AI)
	UAISenseConfig_Sight* SightConfiguration;

	UNavigationSystemV1* NavigationSystem;
	APawn* TargetPlayer;

	UPROPERTY(EditDefaultsOnly, Category = Blackboard)
	UBlackboardData* AIBlackboard;

	UPROPERTY(EditDefaultsOnly, Category = Blackboard)
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditDefaultsOnly, Category = Blackboard)
	UBlackboardComponent* BlackboardComponent;


public:
	AChasingEmenyAIController();

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual FRotator GetControlRotation() const override;
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	UFUNCTION()
	void OnSensesUpdated(AActor* UpdatedActor, FAIStimulus Stimulus);

	void GenerateNewRandomLocation();
	
};
