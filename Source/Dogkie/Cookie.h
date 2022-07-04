// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Cookie.generated.h"

UCLASS()
class DOGKIE_API ACookie : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACookie();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Cookie;

	UPROPERTY(EditAnywhere)
	UBoxComponent* CookieHitBox;
	
	bool IsPoisoned = false;
	float Timer = 0;
	int TimerLimit = 0;
	int TimerMin = 10;
	int TimerMax = 80;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
	UMaterialInterface* Material;

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
