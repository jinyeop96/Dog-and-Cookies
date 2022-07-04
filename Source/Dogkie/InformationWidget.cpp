// Fill out your copyright notice in the Description page of Project Settings.


#include "InformationWidget.h"

#include "Kismet/GameplayStatics.h"

void UInformationWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
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

	// Get reference to player's character
	ActorsToFind.Empty();

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

void UInformationWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	
	// Display pet health
	if(IsValid(PlayerPet))
	{
   		PetHealthBar->SetPercent(PlayerPet->Health/100);
   		FNumberFormattingOptions Opts;
   		Opts.SetMaximumFractionalDigits(0);
   		CurrentPetHealthLabel->SetText(FText::AsNumber(PlayerPet->Health, &Opts));
	}

	// Display player's collected cookies
	if (IsValid(PlayerCharacter))
	{
		FNumberFormattingOptions Opts;
		Opts.SetMaximumFractionalDigits(0);
		CurrentCookies->SetText(FText::AsNumber(PlayerCharacter->Cookies, &Opts));
	}
}

