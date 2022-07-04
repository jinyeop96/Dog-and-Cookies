// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"

#include "Cookie.h"
#include "Cube.h"
#include "DogkieCharacter.h"
#include "Enemy.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Bomb = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bomb"));
	Bomb -> OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnBombHit);
	RootComponent = Bomb;

	Parent = nullptr;
	MovementSpeed = 750; 
	MaximumLifetime = 2;
	CurrentLifeTime = 0;

	// Get reference to the NS_StoneScattering particle
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemClass(TEXT("/Game/ParticleEffects/NS_BombExplosion.NS_BombExplosion"));
	if (NiagaraSystemClass.Succeeded())
	{
		NS_BombExplosion = NiagaraSystemClass.Object;
	}

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(this))
	{
		FVector CurrentLocation  = GetActorLocation();
		FVector Forward = Direction;
		FVector Movement = (Forward * MovementSpeed * DeltaTime);
		FVector NewLocation = CurrentLocation + Movement;
		SetActorLocation(NewLocation);

		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Pitch = 270;
		SetActorRotation(CurrentRotation);

		CurrentLifeTime += DeltaTime;
		if (CurrentLifeTime >= MaximumLifetime)
		{
			Interact_Implementation();
		}
	}
}

void ABomb::OnBombHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if( IsValid(this) && OtherActor && OtherActor != this && OtherActor != Parent)
	{
		Interact_Implementation();
	}
}

void ABomb::Interact_Implementation()
{
	TArray<FHitResult> OutHits;
	FVector CurrentLocation = GetActorLocation();
	FCollisionShape ExplosionSphere = FCollisionShape::MakeSphere(sweepSize);

	// InWorld, Center, Radius, Segments(몇각형인지_클수록 원에 가까움), Color, bPersistentLines, LifeTime, DepthPriority, Thickness
	//DrawDebugSphere(GetWorld(), CurrentLocation, ExplosionSphere.GetSphereRadius(), 50, FColor::Red, false, 1.0f, 0,0);
	

	// Spawn Bomb explosion effect
	if( NS_BombExplosion -> IsValid())
	{
		// Spawn particle effects where it hits
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_BombExplosion, GetActorLocation());
	}
	
	if(GetWorld()->SweepMultiByChannel(OutHits, CurrentLocation,CurrentLocation, FQuat::Identity, ECC_WorldStatic, ExplosionSphere)){
		UE_LOG(LogTemp, Warning, TEXT("Bomb name : %s"), *FString(this -> GetName()));
		for(auto& Hit : OutHits){
			
			// Destroys the following actors
			if (Hit.GetActor())
			{
				if ( Cast<ACookie>(Hit.GetActor()) ||  Cast<AEnemy>(Hit.GetActor()))
				{
					Hit.GetActor() -> Destroy();
				
				}

				// If player character or pet is hit, quit the game
				if (Cast<APet>(Hit.GetActor()) || Cast<ADogkieCharacter>(Hit.GetActor()))
				{
					UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/FirstPerson/Maps/LoseMenu"), TRAVEL_Absolute);
				}

				// Add impulse to cubes
				if (Cast<ACube>(Hit.GetActor()))
				{
					ACube* Cube = Cast<ACube>(Hit.GetActor());
					
					UStaticMeshComponent* Mesh = Cast<UStaticMeshComponent>(Cube ->GetRootComponent());
					UE_LOG(LogTemp, Warning, TEXT("Mesh : %s"), *FString(Mesh->GetName()));

					Mesh-> AddRadialImpulse(CurrentLocation, 20000, 2000.0f, ERadialImpulseFalloff::RIF_Linear, true);
				}
			}
			

			

			

			
		}
	}
	
	Destroy();
}

