// Fill out your copyright notice in the Description page of Project Settings.


#include "Pet.h"

#include "Cookie.h"

// Sets default values
APet::APet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PetBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pet Body"));
	PetBody -> SetupAttachment(RootComponent);

	PetHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Pet Hit Box"));
	PetHitBox -> SetupAttachment(PetBody);
}

// Called when the game starts or when spawned
void APet::BeginPlay()
{
	Super::BeginPlay();

	if (PetHitBox)
	{
		if (PetHitBox)
		{
			PetHitBox->OnComponentBeginOverlap.AddDynamic(this, &APet::OnHitBoxOverlapBegin);
		}
	}

	if(Material)
	{
		MatInstance = UMaterialInstanceDynamic::Create(Material, this);
		PetBody->SetMaterial(0, MatInstance);
	}
	
}

// Called every frame
void APet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APet::DecrementHealth(float Amount)
{
	Health -= Amount;

	// If pet loses all health, end the game
	if (Health <= 0)
	{
		GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
	}

	// If the health is below or equal to 40 out of 100, start emitting effects
	if (Health <= 40)
	{
		MatInstance->SetScalarParameterValue("Emissive", 1);

	}
}

void APet::IncrementHealth(float Amount)
{
	Health += Amount;

	if (Health > 100)
	{
		Health = 100;
	}

	// If the health is above 40 out of 100, stop emitting effects
	if (Health > 40)
	{
		MatInstance->SetScalarParameterValue("Emissive", 0);
	}
}

void APet::OnHitBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && !Cast<ACookie>(OtherActor))
	{
		HasOverlapped = true;
	}
}







