// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/IHFountain.h"
#include "GameFramework/RotatingMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Tag/IHGameplayTag.h"

// Sets default values
AIHFountain::AIHFountain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	

	

	// Scene Component
	m_Body_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));


	// Actor Component 
	m_ASC = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("ASC"));
	m_RotatingMovement = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotateMovement"));
	m_ActionPeriod = 3.0f; 

	
	// 리소스 
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyRef(TEXT("/Game/Environment/Props/SM_Plains_Castle_Fountain_01.SM_Plains_Castle_Fountain_01"));
	
	if (BodyRef.Object != NULL)
	{
		m_Body_Mesh->SetStaticMesh(BodyRef.Object);
	}




}

UAbilitySystemComponent* AIHFountain::GetAbilitySystemComponent() const
{
	return m_ASC;
}




void AIHFountain::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	m_RotatingMovement->bAutoActivate = false; 
	m_RotatingMovement->Deactivate(); 

	// OwnerActor = ASC를 논리적으로 소유한 주체 (해당 주체가 죽어도 유지됨)
	// AvatarActor = Character의 Skeletal Mesh같이 비주얼 역할만 수행해주는 액터  

	// ASC 입장에서 "나를 소유한게 누구고, 실제로 몸을 가진게 누군지"를 알아야 어빌리티 발동 및 이펙트 적용 및 애니메이션 재생등을 함.
	m_ASC->InitAbilityActorInfo(this, this);	


	for(auto& Ability_iter : m_vecStartAbilities)
	{
		FGameplayAbilitySpec Ability(Ability_iter);
		m_ASC->GiveAbility(Ability);

	}
}

// Called when the game starts or when spawned
void AIHFountain::BeginPlay()
{
	Super::BeginPlay();


	GetWorld()->GetTimerManager().SetTimer(m_ActionTimer, this, &AIHFountain::TimerAction, m_ActionPeriod, true, 3.0f);
	
}

// Called every frame
void AIHFountain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIHFountain::TimerAction()
{
	FGameplayTagContainer TargetTag(TAG_ACTOR_ROTATE);

	// 어빌리티가 발동이 되면은 ISROTATING 태그가 심어짐
	if (!m_ASC->HasMatchingGameplayTag(TAG_ACTOR_ISROTATING))
	{
		m_ASC->TryActivateAbilitiesByTag(TargetTag);
	}

	else
	{
		m_ASC->CancelAbilities(&TargetTag);
	}




}





