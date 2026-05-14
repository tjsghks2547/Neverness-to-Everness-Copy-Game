// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.h"
#include "InputActionValue.h"
#include "Interface/PlayerUiWidget_Interface.h"
#include "Character_NaNally.generated.h"

enum class EInterActionType : uint8;

UCLASS()
class NEVERNESS_API ACharacter_NaNally : 
	public ACharacterBase,
	public IPlayerUiWidget_Interface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacter_NaNally();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	// IPlayerUiWidget_Interface을(를) 통해 상속됨
	void SetupPlayerUiWidget(UPlayerUIWidget* _InPlayerUiWidget) override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	// 박스와 충돌할때 발생시키는 함수 
	void Render_InterActionUi(EInterActionType _Tag, ESlateVisibility _eSlateVisibility);
	FORCEINLINE void Set_Current_OverlapTypes(EInterActionType _Tag)
	{
		InterActionType = _Tag;
	};

	void Ui_Key_State_Reset();
protected:
	// 움직임 관련 함수 
	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);
	void TestUiAction();

	

protected:
	// 컴포넌트 구성 
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class USpringArmComponent> SpringArm; 

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	TObjectPtr<class UStatComponent> StatComponent;

	UPROPERTY(VisibleAnywhere, Category = UI)
	TObjectPtr<class UUi_InterAction_Component> UiComponent;


protected:
	// 입력 관련 구성
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<class UInputAction> ShoulderMoveAction; 

	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<class UInputAction> ShoulderLookAction;

	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<class UInputAction> TestAction;

	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<class UInputAction> TestStaminaAction;

protected:

	UPROPERTY(VisibleAnywhere, Category = OverlapType, BlueprintReadOnly)
	EInterActionType InterActionType;
};
