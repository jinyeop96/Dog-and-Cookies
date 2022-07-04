// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

#include "DogkieCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

	Bullet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet"));
	Bullet -> OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnBulletHit);
	RootComponent = Bullet;

	Parent = nullptr;
	MovementSpeed = 1500; 
	MaximumLifetime = 10;
	CurrentLifeTime = 0;

	// Get reference to the NS_StoneScattering particle
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> NiagaraSystemClass(TEXT("/Game/ParticleEffects/NS_StoneScattering.NS_StoneScattering"));
	if (NiagaraSystemClass.Succeeded())
	{
		NS_BulletHit = NiagaraSystemClass.Object;
	}

	// Get reference to the Bang Sound Cue
	static ConstructorHelpers::FObjectFinder<USoundBase> SoundBaseClass(TEXT("/Game/Sound/SC_Bang.SC_Bang"));
	if (SoundBaseClass.Succeeded())
	{
		SB_Explosion = SoundBaseClass.Object;
	}
	


}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
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
		Destroy();
	}

}

void ABullet::OnBulletHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		if( IsValid(SB_Explosion))
		{
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), SB_Explosion, GetActorLocation());
		}
		
		// Spawn Stone Scattering effect
		if( NS_BulletHit -> IsValid())
		{
			// Spawn particle effects where it hits
			UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NS_BulletHit, GetActorLocation(), GetActorRotation());
			UE_LOG(LogTemp, Warning, TEXT("NS_BulletHit spawned : %s"), *FString(NS_BulletHit->GetName()));	
		}
		
		Destroy();

		UE_LOG(LogTemp, Warning, TEXT("Other actor : %s"), *FString(OtherActor->GetName()));
		// If bullet hits player's character, end the game
		if(Cast<ADogkieCharacter>(OtherActor))
		{
			UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/FirstPerson/Maps/LoseMenu"), TRAVEL_Absolute);	
		}
	}
}


