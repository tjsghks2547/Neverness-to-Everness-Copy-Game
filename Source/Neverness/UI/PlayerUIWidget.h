// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEVERNESS_API UPlayerUIWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPlayerUIWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override; 

public:
	// 캐릭터에서 호출함 함수.
	void UpdateHp(int32 _iCurrentHp); 
	void UpdateProgressBarHp(int32 _iCurrentHp);	
	void SetUp_Ui_Hp(int32 _iCurrentHp, int32 _iMaxHp);
	

protected:
	TObjectPtr<class UPlayerHpProgressBarWidget> m_pWidgetHpProgressBar;
	TObjectPtr<class UPlayerHpProgressBarWidget_White> m_pWidgetHpWhiteProgressBar;
	TObjectPtr<class UTextBlock> m_pCurrentHpText;
	TObjectPtr<class UTextBlock> m_pMaxHpText;

private:
	int32 m_iCurrentHp;
	int32 m_iMaxHp; 

	
};
