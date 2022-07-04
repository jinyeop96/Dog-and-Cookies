// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NiagaraSystem.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class DOGKIE_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Bullet;

	UPROPERTY(EditAnywhere)
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	float MaximumLifetime;

	UPROPERTY(EditAnywhere)
	float CurrentLifeTime;

	AActor* Parent;

	FVector Direction;
	
	UPROPERTY(EditAnywhere, Category = "Niagara System")
	UNiagaraSystem* NS_BulletHit;

	UPROPERTY(EditAnywhere, Category="Sound")
	USoundBase* SB_Explosion;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OnBulletHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	 UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
	 const FHitResult& SweepResult);

};
