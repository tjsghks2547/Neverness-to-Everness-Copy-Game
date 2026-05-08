// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerUIWidget.h"
#include "PlayerHpProgressBarWidget.h"
#include "PlayerHpProgressBarWidget_White.h"
#include "Components/TextBlock.h"
#include "Interface/PlayerUiWidget_Interface.h"


UPlayerUIWidget::UPlayerUIWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	m_iCurrentHp = 0.0f;
	m_iMaxHp = 0.0f; 
}

void UPlayerUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// BluePrint에서 생성해준 Asset들은 생성자 이후에 찾기

#pragma region Blueprint 에서 생성해준 widget
	m_pWidgetHpProgressBar = Cast<UPlayerHpProgressBarWidget>(GetWidgetFromName(TEXT("WBP_HpProgressBar")));
	ensureAlways(m_pWidgetHpProgressBar);

	m_pWidgetHpWhiteProgressBar = Cast<UPlayerHpProgressBarWidget_White>(GetWidgetFromName(TEXT("WBP_HpWhiteProgressBar")));
	ensureAlways(m_pWidgetHpWhiteProgressBar);


	m_pCurrentHpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Current_HP_Text")));
	ensureAlways(m_pCurrentHpText);

	m_pMaxHpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Max_Hp_Text")));
	ensureAlways(m_pMaxHpText);
#pragma endregion 


	// player에 해당 UiWidget 등록하기 
	IPlayerUiWidget_Interface* pUiWidget_interface = Cast<IPlayerUiWidget_Interface>(GetOwningPlayerPawn());

	if(pUiWidget_interface != NULL)
	{
		pUiWidget_interface->SetupPlayerUiWidget(this);
	}


}

void UPlayerUIWidget::UpdateHp(int32 _iCurrentHp)
{
	m_iCurrentHp = _iCurrentHp;
	// 일단 TEXT 부터 
	m_pCurrentHpText->SetText(FText::AsNumber(m_iCurrentHp));
	
}

void UPlayerUIWidget::UpdateProgressBarHp(int32 _iCurrentHp)
{
	m_pWidgetHpProgressBar->UpdateHpProgressBar(_iCurrentHp);
	m_pWidgetHpWhiteProgressBar->Update_HpProgressHpBarWhite(_iCurrentHp);
}



void UPlayerUIWidget::SetUp_Ui_Hp(int32 _iCurrentHp, int32 _iMaxHp)
{
	m_iCurrentHp = _iCurrentHp;
	m_iMaxHp = _iMaxHp;

	m_pWidgetHpProgressBar->Setup_Hp(_iCurrentHp, _iMaxHp);
	m_pWidgetHpWhiteProgressBar->Setup_HpWhiteProgressBar(_iCurrentHp, _iMaxHp);
}
