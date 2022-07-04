// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DogkieCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "InformationWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DOGKIE_API UInformationWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	ADogkieCharacter* PlayerCharacter;
	APet* PlayerPet;

	void NativeConstruct () override;
	void NativeTick (const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* PetHealthBar;
	
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentPetHealthLabel;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* CurrentCookies;
	
};
