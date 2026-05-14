// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StatComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	MaxHp = 0;
	CurrentHp = 0; 

	// ...
}


// Called when the game starts
void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	/* 스테미나 관련*/
	CurrentStamina = FMath::FInterpTo(CurrentStamina, MaxStamina, DeltaTime, 1.5f);
	
	

}

void UStatComponent::Apply_Damage(int32 _iDamageSize)
{
	CurrentHp -= _iDamageSize;

	if(CurrentHp <= 0 )
	{
		CurrentHp = 0;
	}

}

void UStatComponent::Apply_Stamina(float _fStaminaConsumption)
{
	CurrentStamina -= _fStaminaConsumption;

	if (CurrentStamina <= 0)
	{
		CurrentStamina = 0;
	}

}

