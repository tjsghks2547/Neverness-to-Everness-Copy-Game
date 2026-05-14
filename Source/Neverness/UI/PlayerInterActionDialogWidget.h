// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerInterActionDialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class NEVERNESS_API UPlayerInterActionDialogWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPlayerInterActionDialogWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

};
