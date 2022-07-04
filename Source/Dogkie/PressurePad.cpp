// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePad.h"

// Sets default values
APressurePad::APressurePad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	PressurePadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	PressurePadMesh->SetupAttachment(RootComponent);

	PressurePadHitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Hitbox Component"));
	PressurePadHitBox->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APressurePad::BeginPlay()
{
	Super::BeginPlay();

	if (PressurePadHitBox)
	{
		PressurePadHitBox->OnComponentBeginOverlap.AddDynamic(this, &APressurePad::OnHitboxOverlapBegin);
	}

	Player = Cast<ADogkieCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if(Material)
    {
     MatInstance = UMaterialInstanceDynamic::Create(Material, this);
     PressurePadMesh->SetMaterial(0, MatInstance);
    }

	
}

// Called every frame
void APressurePad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get distance between this and the player and emits diverse effects
	if( Player && MatInstance)
	{
		float DistanceToPlayer = FVector::Distance(Player->GetActorLocation(),GetActorLocation());

		MatInstance->SetVectorParameterValue("Colour", FLinearColor(0,1 - DistanceToPlayer/1000, 0));
		MatInstance->SetScalarParameterValue("Emissive", 1-DistanceToPlayer/400);
		float ClampedDistance = FMath::Clamp(DistanceToPlayer/1000,0,1);
		MatInstance->SetScalarParameterValue("Vibration", 1-ClampedDistance);
	}

}

void APressurePad::OnHitboxOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor && OtherActor != this)
	{
		PressurePadHitBoxDelegate.Broadcast();
		UE_LOG(LogTemp, Warning, TEXT("Pressure pad stepped on"))
	}

}

