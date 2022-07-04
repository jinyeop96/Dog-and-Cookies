// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Pet.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPetDestroyed);

UCLASS()
class DOGKIE_API APet : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APet();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PetBody;

	UPROPERTY(EditAnywhere)
	UBoxComponent* PetHitBox;

	UPROPERTY(EditAnywhere)
	float MovementSpeed = 200;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 30;

	UPROPERTY(EditAnywhere)
	float RotationAmount = 2.0;

	UPROPERTY(BlueprintAssignable)
	FPetDestroyed PetDestroyedDelegate;
	
	bool HasBeenCalled = false;
	bool HasOverlapped = false;	
	
	float Health = 50;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsInDanger = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInterface* Material;

	UMaterialInstanceDynamic* MatInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DecrementHealth(float Amount);
	void IncrementHealth(float Amount);

	UFUNCTION()
	void OnHitBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	 UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
