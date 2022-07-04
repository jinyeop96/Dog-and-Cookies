// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class DOGKIE_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties  
	ADoor();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere)
	UBoxComponent* DoorHitBox; 

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool IsDoorOpen = false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*UFUNCTION()
	void OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	 AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	 bool bFromSweep, const FHitResult& SweepResult);*/

};
