// Fill out your copyright notice in the Description page of Project Settings.


#include "Cookie.h"

#include "DogkieCharacter.h"

// Sets default values
ACookie::ACookie()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	Cookie = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cookie"));
	Cookie -> SetupAttachment(RootComponent);

	CookieHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Cookie Hit Box"));
	CookieHitBox -> SetupAttachment(Cookie);
}

// Called when the game starts or when spawned
void ACookie::BeginPlay()
{
	Super::BeginPlay();

	if (CookieHitBox)
	{
		CookieHitBox -> OnComponentBeginOverlap.AddDynamic(this, &ACookie::OnHitboxOverlapBegin);
	}

	// set random TimerLimit
	TimerLimit = FMath::RandRange(TimerMin, TimerMax);
}

// Called every frame
void ACookie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check the timer in each tick and set this to poisoned cookie and change the colour
	Timer += DeltaTime;
	if (Timer > TimerLimit && !IsPoisoned)
	{
		IsPoisoned = true;
		if(Material)
		{
			MatInstance = UMaterialInstanceDynamic::Create(Material, this);
			Cookie->SetMaterial(0, MatInstance);
		}
	}

	
}

void ACookie::OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		ADogkieCharacter* PlayerCharacter = Cast<ADogkieCharacter>(OtherActor);
		APet* Pet = Cast<APet>(OtherActor);

		UE_LOG(LogTemp, Warning, TEXT("Cookie hit box overlapped"));  
		if (PlayerCharacter && !IsPoisoned)	// Player is only allowed to pick up not poisoned cookie
		{
			Destroy();
			PlayerCharacter -> Cookies++;
		} else if (Pet)
		{
			// If the cookie is poisoned, pet health decremented
			Destroy();
			if (IsPoisoned)
			{
				Pet->DecrementHealth(40);
			} else
			{
				Pet->IncrementHealth(20);
			}
			
		}
	}
}


