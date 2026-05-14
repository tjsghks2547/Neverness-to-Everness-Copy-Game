// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStaminaProgressBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEVERNESS_API UPlayerStaminaProgressBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPlayerStaminaProgressBarWidget(const FObjectInitializer& ObjectInitializer);


protected:
	virtual void NativeConstruct() override;


public:
	FORCEINLINE void Set_Up_Stamina(float _fCurrentStamina, float _fMaxStamina)
	{
		CurrentStamina = _fCurrentStamina; 
		MaxStamina = _fMaxStamina; 
	};


	void UpdateProgressBar(float _fCurrentStamina, float _fMaxStamina);
	bool Get_HasPlayedStaminaAnimation() { return HasPlayedStaminaRenderOpacity; }
	void Set_HasPlayedStaminaAnimation(bool _bPlayed) { HasPlayedStaminaRenderOpacity = _bPlayed; }
	void PlayUiAnimation(); 
	void ResetRenderOpacity(); 

private:
	TObjectPtr<class UProgressBar> StaminaProgressBar;
	TObjectPtr<class UTextBlock> CurrentStaminaText;
	
	UPROPERTY()
	float CurrentStamina;
	UPROPERTY()
	float MaxStamina;


#pragma region Stamina UI Animation 관련
	/* BindWidgetAnim (Blueprint 애니메이션과 자동 연결 )*/
	/* Transient 직렬화 제외, 런타임에만 유효한 포인터임을 명시*/
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> Render_Opacity_StaminaProgressBar; 
	
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> Render_Opactiy_StaminaText;
	
	UPROPERTY()
	bool HasPlayedStaminaRenderOpacity = false;
#pragma endregion 




};
