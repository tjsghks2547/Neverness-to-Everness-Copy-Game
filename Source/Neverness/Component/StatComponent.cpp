// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/StatComponent.h"

// Sets default values for this component's properties
UStatComponent::UStatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_iMaxHp = 0;
	m_iCurrentHp = 0; 

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
}

void UStatComponent::Apply_Damage(int32 _iDamageSize)
{
	m_iCurrentHp -= _iDamageSize;

	if(m_iCurrentHp <= 0 )
	{
		m_iCurrentHp = 0;
	}

}

