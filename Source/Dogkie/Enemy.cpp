// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Bomb.h"
#include "Bullet.h"
#include "Cookie.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Every Actor contains a root component.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Enemy Body"));
	EnemyBody -> SetupAttachment(RootComponent);

	EnemyCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Enemy Capsule Component"));
	EnemyCapsuleComponent -> SetupAttachment(EnemyBody);
	

	// Default variable for Bullet class
	static ConstructorHelpers::FObjectFinder<UBlueprint> BulletBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_Bullet.BP_Bullet'"));
	if (BulletBlueprint.Object)
	{
		BulletClass = BulletBlueprint.Object->GeneratedClass;
	}

	// Default variable for Bullet class
	static ConstructorHelpers::FObjectFinder<UBlueprint> BombBlueprint(TEXT("Blueprint'/Game/Blueprints/BP_Bomb.BP_Bomb'"));
	if (BombBlueprint.Object)
	{
		
		BombClass = BombBlueprint.Object->GeneratedClass;
	}

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyCapsuleComponent)
	{
		EnemyCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnCapsuleOverlapBegin);
	}

	// Get reference to the player's character
	if (! PlayerCharacter )
	{
		// Get reference to player's character
		TArray<AActor*> ActorsToFind;

		if(UWorld* World = GetWorld())
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), ActorsToFind);
		}

		for(auto Actor: ActorsToFind)
		{
			if (Cast<ADogkieCharacter>(Actor))
			{
				PlayerCharacter = Cast<ADogkieCharacter>(Actor);
				break;
			}
			
		}
	}

	// Get reference to the player's pet
	if( !PlayerPet)
	{
		// Get reference to the pet
		TArray<AActor*> ActorsToFind;

		if(UWorld* World = GetWorld())
		{
			UGameplayStatics::GetAllActorsOfClass(GetWorld(), APet::StaticClass(), ActorsToFind);
		}

		if (ActorsToFind.Num()>0)
		{
			PlayerPet = Cast<APet>(ActorsToFind[0]);
		}
	}
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Increment timer in each tick calls
	Timer += DeltaTime;

	// Check for timer limit
	if (Timer < TimerLimit)
	{
		return;
	}
	Timer = 0;

	// Check distance between player or pet for firing a bullet or a bomb
	if (IsValid(PlayerCharacter) && IsValid(PlayerPet))
	{
		FVector PlayerLocation = PlayerCharacter -> GetActorLocation();
		FVector PetLocation = PlayerPet -> GetActorLocation();
		FVector CurrentLocation = GetActorLocation();
		FVector TargetLocation;
		
		// If player is within the set distance, set the target to be the player
		if (FVector::Distance(PlayerLocation, CurrentLocation) < 1000)
		{
			TargetLocation = PlayerLocation;
		} else if(FVector::Distance(PetLocation, CurrentLocation) < 1000) // If pet is within the set distance, set the target to be the pet
		{
			TargetLocation = PetLocation;
		} else
		{
			return;
		}
		

		// check for angle whether the target is in front of this 
		FVector VectorBetweenTargetAndThis = TargetLocation - CurrentLocation;
		FVector CurrentForward = GetActorForwardVector();

		// Calculate the angle 
		float DotProduct = FVector::DotProduct(CurrentForward, VectorBetweenTargetAndThis)/(CurrentForward.Size() * VectorBetweenTargetAndThis.Size());
		float AcosAngle = FMath::Acos(DotProduct);
		float Angle = FMath::RadiansToDegrees(AcosAngle);
		
		if( Angle < 45)
		{
			// If in front, set projectile's offset
			FVector Offset = FVector(70, 0, 130);
			Offset = GetActorRotation().RotateVector(Offset);
			FVector StartPosition = Offset + CurrentLocation;

			// Spawn the appropriate projectile to the target
			if (FiringBullet)
			{
				FireBullet(StartPosition);	
			} else
			{
				FireBomb(StartPosition);
			}
		}
	}
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::OnCapsuleOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && !Cast<ACookie>(OtherActor))
	{
		HasOverlapped = true;
	}
}

void AEnemy::FireBullet(FVector StartPosition)
{
	ABullet* SpawnedBullet = (ABullet*) GetWorld() ->SpawnActor(BulletClass, &StartPosition);
	SpawnedBullet -> SetActorRotation(GetActorRotation());
	SpawnedBullet ->Direction = SpawnedBullet -> GetActorForwardVector();
	SpawnedBullet->Parent = this;
	
}

void AEnemy::FireBomb(FVector StartPosition)
{
	ABomb* SpawnedBomb = (ABomb*) GetWorld() ->SpawnActor(BombClass, &StartPosition);
	SpawnedBomb -> SetActorRotation(GetActorRotation());
	SpawnedBomb ->Direction = SpawnedBomb -> GetActorForwardVector();
	SpawnedBomb->Parent = this;
}






