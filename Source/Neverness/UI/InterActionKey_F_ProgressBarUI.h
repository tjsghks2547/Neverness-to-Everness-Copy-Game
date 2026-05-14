// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InterActionKey_F_ProgressBarUI.generated.h"

/**
 * 
 */

UCLASS()
class NEVERNESS_API UInterActionKey_F_ProgressBarUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UInterActionKey_F_ProgressBarUI(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdatePercent_Progressbar(float _IncreasePercent);
	void SetPercent_Progressbar(float _InPercent);

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UImage> Image_ProgressInterAction; 

	// 기본으로 넣을 머터리얼 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TObjectPtr<class UMaterialInterface> ProgressBarMaterial;

private:
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> RoundProgressBarInst;
	

	UPROPERTY()
	float CurrentPercent;
};
