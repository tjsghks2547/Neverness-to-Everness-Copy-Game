// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerUIWidget.generated.h"

enum class EInterActionType : uint8;

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

	/* HP 관련 */
	void UpdateHp(int32 _iCurrentHp); 
	void UpdateProgressBarHp(int32 _iCurrentHp);	
	void SetUp_Ui_Hp(int32 _iCurrentHp, int32 _iMaxHp);
	/* ----------------- */

	/* Stamina 관련 */
	void SetUp_Ui_Stamina(float _fCurrentStamina, float _fMaxStamina);
	void UpdateProgressBarStamina(float _fCurrentStamina, float _fMaxStamina);
	/* ----------------- */

	/* 대화 UI 관련 */
	void Set_DialogRenderOnOff(EInterActionType _eInterActionKeyType, ESlateVisibility _eSlateVisiblilty);
	void F_KeyStateUpdate(float _InIncreaseAmount);
	void Set_F_KeyState(float _InPercent);


protected:
#pragma region Hp UI 
	TObjectPtr<class UPlayerHpProgressBarWidget> WidgetHpProgressBar;
	TObjectPtr<class UPlayerHpProgressBarWidget_White> WidgetHpWhiteProgressBar;
	TObjectPtr<class UTextBlock> CurrentHpText;
	TObjectPtr<class UTextBlock> MaxHpText;
#pragma endregion 

#pragma region Stamina UI
	TObjectPtr<class UPlayerStaminaProgressBarWidget> WidgetStaminProgressBar; 
#pragma endregion 


#pragma region InterAction UI
	TObjectPtr<class UPlayerInterActionDialogWidget> PlayerInterActionDialogWidget;
	TObjectPtr<class UInterActionKey_F_ProgressBarUI> InterActionKeyFWidget;
#pragma endregion 



};
