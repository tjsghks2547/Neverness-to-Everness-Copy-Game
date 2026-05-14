// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

// float 매개변수 1개를 받는 함수들만 등록할 수 있다.라는 의미 
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate/*Delegate 이름*/, int32 /* CurrentHp (현재 Hp)*/)
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnStaminaChangedDelegate /* Delegate 이름*/, float /* fCurrentStamina ( 현재 Stamina) */, float /*fMaxStamina ( Max Stamina)*/)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEVERNESS_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE int32 GetMaxHp()          { return MaxHp; }
	FORCEINLINE int32 GetCurrentHp()      { return CurrentHp;}
	FORCEINLINE float GetMaxStamina()     { return MaxStamina; }
	FORCEINLINE float GetCurrentStamina() { return CurrentStamina; }


	void Apply_Damage(int32 _iDamageSize);
	void Apply_Stamina(float _fStaminaConsumption);

public:
	// hp 변동 관련 업데이트 
	FORCEINLINE void Update_Stat_Hp(int32 _iCurrentHp)
	{
		CurrentHp = _iCurrentHp; 
	};
	
	FORCEINLINE void SetUp_stat_Hp(int32 _iCurrentHp, int32 _iMaxHp)
	{
		CurrentHp = _iCurrentHp;
		MaxHp = _iMaxHp; 
	};

	// Stamina 변동 관련 업데이트
	FORCEINLINE void Update_Stat_Stamina(float _fCurrentStamina)
	{
		CurrentStamina = _fCurrentStamina;
	};

	FORCEINLINE void SetUp_stat_Stamina(float _fCurrentStamina, float _fMaxStamina)
	{
		CurrentStamina = _fCurrentStamina;
		MaxStamina = _fMaxStamina;
	};


	
	// Hp가 변동될 때마다 발행할 델리게이트.
	FOnHpChangedDelegate		Delegate_OnHpChanged; 
	FOnStaminaChangedDelegate   Delegate_OnStaminaChanged;

private:
	UPROPERTY(EditAnywhere, Category = Stat)
	int32 MaxHp = 0;

	UPROPERTY(EditAnywhere, Category = Stat)
	int32 CurrentHp = 0;

	UPROPERTY(EditAnywhere, Category = Stat)
	float MaxStamina = 0.0f; 

	UPROPERTY(EditAnywhere, Category = Stat)
	float CurrentStamina = 0.0f; 
	

	
		
};
