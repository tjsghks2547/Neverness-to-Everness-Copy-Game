// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "IHPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NEVERNESS_API AIHPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AIHPlayerController();

public:
	FORCEINLINE TObjectPtr<class UInputMappingContext> GetInputMappingContext() { return m_InputMappingContext; }

protected:
	virtual void BeginPlay() override; 

protected:
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<class UInputMappingContext> m_InputMappingContext;


	// 클래스 정보. 클래스 정보를 바탕으로 실제 UI몸체 생성
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UPlayerUIWidget> PlayerUiWidgetClass; 

	// 실제 생성된 UI 객체 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = UI)
	TObjectPtr<class UPlayerUIWidget> m_pPlayerUiWidget;


};
