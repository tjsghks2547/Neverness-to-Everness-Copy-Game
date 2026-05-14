// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ui_InterAction_Component.generated.h"

enum class EInterActionType : uint8;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnDialogUiRenderDelegate/* 델리게이트 이름*/, EInterActionType/*해당 UI Key타입 */, ESlateVisibility /* 렌더링 속성 */)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInterActionFKeyStateChanged /* 델리게이트 이름*/, float /*해당 Key 증가량 타입*/ )
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInterActionFKey_SetStateChanged /* 델리게이트 이름*/, float /*해당 Key 증가량 타입*/)


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class NEVERNESS_API UUi_InterAction_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUi_InterAction_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



public:
	FOnDialogUiRenderDelegate Delegate_OnDialogRender; 
	FOnInterActionFKeyStateChanged Delegate_OnInterActionFKeyStateChanged;
	FOnInterActionFKey_SetStateChanged Delegate_OnInterActionFKey_SetStateChanged;
		
};
