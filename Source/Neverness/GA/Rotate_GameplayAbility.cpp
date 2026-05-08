// Fill out your copyright notice in the Description page of Project Settings.


#include "GA/Rotate_GameplayAbility.h"
#include "Tag/IHGameplayTag.h"
#include "GameFramework/RotatingMovementComponent.h"

URotate_GameplayAbility::URotate_GameplayAbility()
{
	AbilityTags.AddTag(TAG_ACTOR_ROTATE); // 이 어빌리티를 식별하는 태그 (이름표)
	ActivationOwnedTags.AddTag(TAG_ACTOR_ISROTATING); // 어빌리티 실행 중일 때 ASC에 부여되는 태그 (상태표시) 

}

void URotate_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* AvaterActor = ActorInfo->AvatarActor.Get(); 

	if(AvaterActor != NULL)
	{
		URotatingMovementComponent* pRotatingMovement = Cast<URotatingMovementComponent>(AvaterActor->GetComponentByClass(URotatingMovementComponent::StaticClass()));

		if(pRotatingMovement != NULL)
		{
			pRotatingMovement->Activate(true);
		}
	}

}

void URotate_GameplayAbility::CancelAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateCancelAbility)
{
	Super::CancelAbility(Handle, ActorInfo, ActivationInfo, bReplicateCancelAbility);

	AActor* AvaterActor = ActorInfo->AvatarActor.Get();

	if (AvaterActor != NULL)
	{
		URotatingMovementComponent* pRotatingMovement = Cast<URotatingMovementComponent>(AvaterActor->GetComponentByClass(URotatingMovementComponent::StaticClass()));

		if (pRotatingMovement != NULL)
		{
			pRotatingMovement->Deactivate();
		}
	}

}
