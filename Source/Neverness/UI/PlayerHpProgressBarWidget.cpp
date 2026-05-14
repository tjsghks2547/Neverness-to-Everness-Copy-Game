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

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("ProgressBar_Widget")));


}

void UPlayerHpProgressBarWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	float DisplayTargetHp = CurrentHp;
	
	DisplayHp = FMath::FInterpTo(DisplayHp, DisplayTargetHp, InDeltaTime, 2.f);

	// 감소 값에 따른 누적 감소  
	HpProgressBar->SetPercent(DisplayHp / MaxHp);
	
	

	
}

void UPlayerHpProgressBarWidget::UpdateHpProgressBar(int32 _iCurrentHp)
{
	DisplayHp = CurrentHp;	
	CurrentHp = _iCurrentHp;

	// 그러면 감소 구역 구하기

}
