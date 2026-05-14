// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerUIWidget.h"
#include "PlayerHpProgressBarWidget.h"
#include "PlayerHpProgressBarWidget_White.h"
#include "Components/TextBlock.h"
#include "Interface/PlayerUiWidget_Interface.h"
#include "PlayerStaminaProgressBarWidget.h"
#include "Components/Image.h"
#include "Animation/WidgetAnimation.h"
#include "PlayerInterActionDialogWidget.h"
#include "InterActionKey_F_ProgressBarUI.h"
#include "Types/InterActionType.h"


UPlayerUIWidget::UPlayerUIWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{

}

void UPlayerUIWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// BluePrint에서 생성해준 Asset들은 생성자 이후에 찾기

#pragma region Blueprint 에서 생성해준 widget
	WidgetHpProgressBar = Cast<UPlayerHpProgressBarWidget>(GetWidgetFromName(TEXT("WBP_HpProgressBar")));
	ensureAlways(WidgetHpProgressBar);

	WidgetHpWhiteProgressBar = Cast<UPlayerHpProgressBarWidget_White>(GetWidgetFromName(TEXT("WBP_HpWhiteProgressBar")));
	ensureAlways(WidgetHpWhiteProgressBar);


	CurrentHpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Current_HP_Text")));
	ensureAlways(CurrentHpText);

	MaxHpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Max_Hp_Text")));
	ensureAlways(MaxHpText);

	/* Stamina 관련 */
	WidgetStaminProgressBar = Cast<UPlayerStaminaProgressBarWidget>(GetWidgetFromName(TEXT("WBP_StaminaBar")));
	ensureAlways(WidgetHpProgressBar);
	/* ----------------- */


	/* InterAction 관련 */
	PlayerInterActionDialogWidget = Cast<UPlayerInterActionDialogWidget>(GetWidgetFromName(TEXT("WBP_InterAction")));
	ensureAlways(PlayerInterActionDialogWidget);

	InterActionKeyFWidget = Cast<UInterActionKey_F_ProgressBarUI>(GetWidgetFromName(TEXT("WBP_RoundBoxInterAction_ProgressBar")));
	ensureAlways(InterActionKeyFWidget);

	/* ----------------- */

#pragma endregion 


	// player에 해당 UiWidget 등록하기 
	IPlayerUiWidget_Interface* pUiWidget_interface = Cast<IPlayerUiWidget_Interface>(GetOwningPlayerPawn());

	if(pUiWidget_interface != NULL)
	{
		pUiWidget_interface->SetupPlayerUiWidget(this);
	}


#pragma region UI 렌더링 초기 설정
	PlayerInterActionDialogWidget->SetVisibility(ESlateVisibility::Collapsed);
	InterActionKeyFWidget->SetVisibility(ESlateVisibility::Collapsed);
#pragma endregion 

}



void UPlayerUIWidget::UpdateHp(int32 _iCurrentHp)
{
	// 일단 TEXT 부터 
	CurrentHpText->SetText(FText::AsNumber(_iCurrentHp));
}

void UPlayerUIWidget::UpdateProgressBarHp(int32 _iCurrentHp)
{
	WidgetHpProgressBar->UpdateHpProgressBar(_iCurrentHp);
	WidgetHpWhiteProgressBar->Update_HpProgressHpBarWhite(_iCurrentHp);
}



void UPlayerUIWidget::SetUp_Ui_Hp(int32 _iCurrentHp, int32 _iMaxHp)
{
	WidgetHpProgressBar->Setup_Hp(_iCurrentHp, _iMaxHp);
	WidgetHpWhiteProgressBar->Setup_HpWhiteProgressBar(_iCurrentHp, _iMaxHp);
}

void UPlayerUIWidget::SetUp_Ui_Stamina(float _fCurrentStamina, float _fMaxStamina)
{
	WidgetStaminProgressBar->Set_Up_Stamina(_fCurrentStamina, _fMaxStamina);
}

void UPlayerUIWidget::UpdateProgressBarStamina(float _fCurrentStamina, float _fMaxStamina)
{
	
	/* Stamina Rendering Opacity Animation Check */

	if(_fCurrentStamina >= 98.0f)
	{
		if(WidgetStaminProgressBar->Get_HasPlayedStaminaAnimation() == false)
		{
			WidgetStaminProgressBar->PlayUiAnimation();
			WidgetStaminProgressBar->Set_HasPlayedStaminaAnimation(true);
		}
	}

	else
	{
		WidgetStaminProgressBar->Set_HasPlayedStaminaAnimation(false);
		WidgetStaminProgressBar->ResetRenderOpacity();
	}

	/* ------------------------------------------- */

	WidgetStaminProgressBar->UpdateProgressBar(_fCurrentStamina, _fMaxStamina);
}

void UPlayerUIWidget::Set_DialogRenderOnOff(EInterActionType _eInterActionKeyType, ESlateVisibility _eSlateVisiblilty)
{
	PlayerInterActionDialogWidget->SetVisibility(_eSlateVisiblilty);
	
	switch (_eInterActionKeyType)
	{
	case EInterActionType::None:
		break;
	case EInterActionType::Dialog:
		break;
	case EInterActionType::Chest:
		break;
	case EInterActionType::Item:
		InterActionKeyFWidget->SetVisibility(_eSlateVisiblilty);
		break;
	default:
		break;
	}

}

void UPlayerUIWidget::F_KeyStateUpdate(float _InIncreaseAmount)
{
	InterActionKeyFWidget->UpdatePercent_Progressbar(_InIncreaseAmount);
}

void UPlayerUIWidget::Set_F_KeyState(float _InPercent)
{
	InterActionKeyFWidget->SetPercent_Progressbar(_InPercent);
}



