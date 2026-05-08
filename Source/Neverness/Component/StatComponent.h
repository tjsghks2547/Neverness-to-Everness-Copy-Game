// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

// float 매개변수 1개를 받는 함수들만 등록할 수 있다.라는 의미 
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHpChangedDelegate/*Delegate 이름*/, int32 /* CurrentHp (현재 Hp)*/)


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

	FORCEINLINE int32 GetMaxHp()     { return m_iMaxHp; }
	FORCEINLINE int32 GetCurrentHp() { return m_iCurrentHp;}

	void Apply_Damage(int32 _iDamageSize);

public:
	// hp 변동 관련 업데이트 
	FORCEINLINE void Update_Stat_Hp(int32 _iCurrentHp)
	{
		m_iCurrentHp = _iCurrentHp; 
	};
	
	FORCEINLINE void SetUp_stat_Hp(int32 _iCurrentHp, int32 _iMaxHp)
	{
		m_iCurrentHp = _iCurrentHp;
		m_iMaxHp = _iMaxHp; 
	};

	
	// Hp가 변동될 때마다 발행할 델리게이트.
	FOnHpChangedDelegate Delegate_OnHpChanged; 
	

private:
	UPROPERTY(EditAnywhere, Category = Stat)
	int32 m_iMaxHp = 0;

	UPROPERTY(EditAnywhere, Category = Stat)
	int32 m_iCurrentHp = 0;

	
		
};
