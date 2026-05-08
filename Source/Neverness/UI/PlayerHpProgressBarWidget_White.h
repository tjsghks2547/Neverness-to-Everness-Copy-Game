// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHpProgressBarWidget_White.generated.h"

/**
 * 
 */
UCLASS()
class NEVERNESS_API UPlayerHpProgressBarWidget_White : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerHpProgressBarWidget_White(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	FORCEINLINE void Setup_HpWhiteProgressBar(int32 _iCurrentHp, int32 _iMaxHp)
	{
		m_iCurrentHp = _iCurrentHp; 
		m_iMaxHp = _iMaxHp; 
	};


	void Update_HpProgressHpBarWhite(int32 _iCurrentHp);



private:
	UPROPERTY()
	TObjectPtr<class UProgressBar> m_pProgressBar;

	UPROPERTY()
	int32 m_iCurrentHp;
	UPROPERTY()
	int32 m_iMaxHp; 


};
