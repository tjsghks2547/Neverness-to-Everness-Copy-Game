// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHpProgressBarWidget.h"
#include "Components/ProgressBar.h"

UPlayerHpProgressBarWidget::UPlayerHpProgressBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UPlayerHpProgressBarWidget::NativeConstruct()
{
	Super::NativeConstruct(); 

	m_pHpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Widget")));


}

void UPlayerHpProgressBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	float DisplayTargetHp = m_iCurrentHp;
	
	m_fDisplayHp = FMath::FInterpTo(m_fDisplayHp, DisplayTargetHp, InDeltaTime, 2.f);

	// 감소 값에 따른 누적 감소  
	m_pHpProgressBar->SetPercent(m_fDisplayHp / m_iMaxHp);
	
	

	
}

void UPlayerHpProgressBarWidget::UpdateHpProgressBar(int32 _iCurrentHp)
{
	m_fDisplayHp = m_iCurrentHp;	
	m_iCurrentHp = _iCurrentHp;

	// 그러면 감소 구역 구하기

}
