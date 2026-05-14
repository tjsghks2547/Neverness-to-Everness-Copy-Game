// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStaminaProgressBarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

UPlayerStaminaProgressBarWidget::UPlayerStaminaProgressBarWidget(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
}

void UPlayerStaminaProgressBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	StaminaProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Stamina")));

	if(StaminaProgressBar == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("StaminaProgressBar를 찾지 못했습니다."));
	}

	CurrentStaminaText = Cast<UTextBlock>(GetWidgetFromName(TEXT("Current_Stamina_Text")));

	if(CurrentStaminaText == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("Current_Stamina_Text를 찾지 못했습니다."));
	}

}


void UPlayerStaminaProgressBarWidget::UpdateProgressBar(float _fCurrentStamina, float _fMaxStamina)	
{
	int DisPlayText = _fCurrentStamina;

	CurrentStamina = _fCurrentStamina;
	MaxStamina = _fMaxStamina;
	
	
	StaminaProgressBar->SetPercent(CurrentStamina / MaxStamina);
	CurrentStaminaText->SetText(FText::AsNumber(DisPlayText));
}

void UPlayerStaminaProgressBarWidget::PlayUiAnimation()
{
	PlayAnimation(Render_Opacity_StaminaProgressBar);
	PlayAnimation(Render_Opactiy_StaminaText);
}

void UPlayerStaminaProgressBarWidget::ResetRenderOpacity()
{
	StaminaProgressBar->SetRenderOpacity(1.f);
	CurrentStaminaText->SetRenderOpacity(1.f);
}

