// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHpProgressBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEVERNESS_API UPlayerHpProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerHpProgressBarWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override; 
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	FORCEINLINE void Set_HpProgressBar(class UProgressBar* pProgressBar) { m_pHpProgressBar = pProgressBar; }
	void UpdateHpProgressBar(int32 _iCurrentHp);
	void Setup_Hp(int32 _iCurrentHp, int32 _iMaxHp)
	{
		m_iCurrentHp = _iCurrentHp;
		m_fDisplayHp = _iCurrentHp;
		m_iMaxHp = _iMaxHp;
	};

protected:
	// Hp 게이지를 보여주기 위해 사용할 프로그래스 바
	UPROPERTY()
	TObjectPtr<class UProgressBar> m_pHpProgressBar;		
	 

	// 최대 체력 값 설정( 게이지 계산을 위해 )
	UPROPERTY()
	int32 m_iMaxHp;

	UPROPERTY()
	int32 m_iCurrentHp;

	// 줄어드는 현 체력 
	UPROPERTY()
	float m_fDisplayHp;
};
