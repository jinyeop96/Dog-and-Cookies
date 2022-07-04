// Fill out your copyright notice in the Description page of Project Settings.


#include "DestinationPad.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ADestinationPad::ADestinationPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	DestinationPadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Destination Pad Component"));
	DestinationPadMesh->SetupAttachment(RootComponent);

	DestinationPadHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Destination Pad HitBox"));
	DestinationPadHitBox->SetupAttachment(DestinationPadMesh);

}

// Called when the game starts or when spawned
void ADestinationPad::BeginPlay()
{
	Super::BeginPlay();

	if (DestinationPadHitBox)
	{
		DestinationPadHitBox->OnComponentBeginOverlap.AddDynamic(this, &ADestinationPad::OnHitboxOverlapBegin);
	}

	// Get reference to player character
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

// Called every frame
void ADestinationPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestinationPad::OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		// Check all required conditions are met
		if( IsValid(PlayerCharacter))
		{
			if (PlayerCharacter -> Cookies < 5)
			{
				return;
			}

			if (FVector::Distance(PlayerCharacter->GetActorLocation(), PlayerCharacter -> PossessedPet->GetActorLocation()) > 1000)
			{
				return;
			}

			// Quit the game
			//GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
			if ( GetWorld()->GetMapName() == "UEDPIE_0_MainMap1")
			{
				IsFirstMap = false;
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/FirstPerson/Maps/MainMap2"), TRAVEL_Absolute);
			} else
			{
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("/Game/FirstPerson/Maps/WinMenu"), TRAVEL_Absolute);
			}
		}
	}

}

