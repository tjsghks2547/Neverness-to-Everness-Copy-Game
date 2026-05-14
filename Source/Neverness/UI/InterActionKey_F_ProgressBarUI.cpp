// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/InterActionKey_F_ProgressBarUI.h"
#include "Components/Image.h"

UInterActionKey_F_ProgressBarUI::UInterActionKey_F_ProgressBarUI(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> ProgressBarMaterialRef(TEXT("/Game/UI/InterActionGage/M_RoundBoxProgressBar_Inst.M_RoundBoxProgressBar_Inst"));

	if (ProgressBarMaterialRef.Succeeded())
	{
		ProgressBarMaterial = ProgressBarMaterialRef.Object;
	}
}

void UInterActionKey_F_ProgressBarUI::NativeConstruct()
{
	Super::NativeConstruct();

	Image_ProgressInterAction = Cast<UImage>(GetWidgetFromName(TEXT("PercentProgressBarImage")));
	ensureAlways(Image_ProgressInterAction);


	RoundProgressBarInst = UMaterialInstanceDynamic::Create(ProgressBarMaterial, this);
	if (RoundProgressBarInst == NULL)
	{
		UE_LOG(LogTemp, Error, TEXT("RoundProgressBarInst를 찾지 못했습니다."));
	}
	
	Image_ProgressInterAction->SetBrushFromMaterial(RoundProgressBarInst);
	


	// 초기값 퍼센트 0 설정
	CurrentPercent = 0.0f;
	RoundProgressBarInst->SetScalarParameterValue(TEXT("Percent"), CurrentPercent);
}

void UInterActionKey_F_ProgressBarUI::UpdatePercent_Progressbar(float _IncreasePercent)
{
	CurrentPercent += _IncreasePercent;
	const float ClampedPercent = FMath::Clamp(CurrentPercent, 0.f, 1.f);

	if (!RoundProgressBarInst)
	{
		return;
	}

	RoundProgressBarInst->SetScalarParameterValue(TEXT("Percent"), ClampedPercent);
}

void UInterActionKey_F_ProgressBarUI::SetPercent_Progressbar(float _InPercent)
{
	CurrentPercent = _InPercent;
	const float ClampedPercent = FMath::Clamp(_InPercent, 0.f, 1.f);

	RoundProgressBarInst->SetScalarParameterValue(TEXT("Percent"), ClampedPercent);

}
