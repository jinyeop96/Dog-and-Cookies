// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DogkieCharacter.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PressurePad.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressurePadActivated);

UCLASS()
class DOGKIE_API APressurePad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePad();
	
	UPROPERTY(BlueprintAssignable)
	FOnPressurePadActivated PressurePadHitBoxDelegate;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* PressurePadMesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* PressurePadHitBox;

	// References to the player and the material 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInterface* Material;

	ADogkieCharacter* Player;
	UMaterialInstanceDynamic* MatInstance;


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
