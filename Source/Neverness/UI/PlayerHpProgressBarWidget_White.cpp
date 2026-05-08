// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHpProgressBarWidget_White.h"
#include "Components/ProgressBar.h"


UPlayerHpProgressBarWidget_White::UPlayerHpProgressBarWidget_White(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerHpProgressBarWidget_White::NativeConstruct()
{
	Super::NativeConstruct();

	m_pProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Widget")));

}

void UPlayerHpProgressBarWidget_White::Update_HpProgressHpBarWhite(int32 _iCurrentHp)
{
	m_iCurrentHp = _iCurrentHp;
	float fCurrentHp = m_iCurrentHp;
	float fCurrentMaxHp = m_iMaxHp;


	float fRatio = fCurrentHp / fCurrentMaxHp;

	m_pProgressBar->SetPercent(fRatio);
}

