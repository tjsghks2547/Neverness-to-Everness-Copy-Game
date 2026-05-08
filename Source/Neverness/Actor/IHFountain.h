// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AbilitySystemInterface.h"
#include "IHFountain.generated.h"

UCLASS()
class NEVERNESS_API AIHFountain : 
	public AActor,
	public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIHFountain();

	// IAbilitySystemInterface을(를) 통해 상속됨
	UAbilitySystemComponent* GetAbilitySystemComponent() const override;



protected:
	// Called when the game starts or when spawned

	// BeginPlay() 함수 이전에 호출되는 함수로
	// 액터가 작동하기 위한 컴포넌트 세팅이 완료됐을 때 호출하는 함수 
	virtual void PostInitializeComponents() override;  
	virtual void BeginPlay() override;
	
	virtual void TimerAction(); 


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	// Scene Component
protected:
	UPROPERTY(EditAnywhere, Category = Mesh)
	TObjectPtr<class UStaticMeshComponent> m_Body_Mesh;



	// Actor Component
protected:
	UPROPERTY(VisibleAnywhere, Category = Movement)
	TObjectPtr<class URotatingMovementComponent> m_RotatingMovement;

	UPROPERTY(EditAnywhere, Category = GAS)
	TObjectPtr<class UAbilitySystemComponent> m_ASC; // 어빌리티 시스템 컴포넌트

	UPROPERTY(EditAnywhere, Category = GAS)
	TArray<TSubclassOf<class UGameplayAbility>> m_vecStartAbilities;

	// 클래스 변수.
protected:
	UPROPERTY(EditAnywhere, Category = Timer)
	float m_ActionPeriod;


	FTimerHandle m_ActionTimer; 


};
