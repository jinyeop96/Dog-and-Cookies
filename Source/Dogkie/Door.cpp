// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "DogkieCharacter.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")); 

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door -> SetupAttachment(RootComponent);

	DoorHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Hit Box"));
	DoorHitBox->SetupAttachment(Door); 


}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	/*if (DoorHitBox)
	{
		DoorHitBox -> OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnHitboxOverlapBegin);
	}*/
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/*void ADoor::OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this )
	{
		// Door opens only if it overlaps with player's character
		ADogkieCharacter* PlayerCharacter = Cast<ADogkieCharacter>(OtherActor);
		if ( PlayerCharacter && ! IsDoorOpen  )
		{
			/*IsDoorOpen = true;
			SetActorRotation( GetActorRotation() +  FRotator(0, 90, 0));#1#
		}
	}
}*/


