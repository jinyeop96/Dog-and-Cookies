// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class DOGKIE_API ABomb : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Bomb;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float MaximumLifetime;

	UPROPERTY(EditAnywhere)
	float CurrentLifeTime;

	AActor* Parent;

	FVector Direction;
	
	float sweepSize = 300.0f;

	UPROPERTY(EditAnywhere, Category = "Niagara System")
	UNiagaraSystem* NS_BombExplosion;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	void OnBombHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	 UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	 const FHitResult& SweepResult);

	// Implement Interactable methods
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interact")
	void Interact();
	virtual void Interact_Implementation() override;

};
