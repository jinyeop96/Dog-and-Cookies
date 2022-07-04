// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DogkieCharacter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "DestinationPad.generated.h"

UCLASS()
class DOGKIE_API ADestinationPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestinationPad();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DestinationPadMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* DestinationPadHitBox;

	ADogkieCharacter* PlayerCharacter;

	bool IsFirstMap = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	 AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	 bool bFromSweep, const FHitResult& SweepResult);
};
