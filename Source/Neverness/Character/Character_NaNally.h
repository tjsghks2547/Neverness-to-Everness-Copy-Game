// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.h"
#include "InputActionValue.h"
#include "Interface/PlayerUiWidget_Interface.h"
#include "Character_NaNally.generated.h"

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

protected:
	// 움직임 관련 함수 
	void ShoulderMove(const FInputActionValue& Value);
	void ShoulderLook(const FInputActionValue& Value);
	void TestAction();
protected:
	// 컴포넌트 구성 
	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class USpringArmComponent> m_pSpringArm; 

	UPROPERTY(VisibleAnywhere, Category = Camera)
	TObjectPtr<class UCameraComponent> m_pCamera;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	TObjectPtr<class UStatComponent> m_pStatComponent;


protected:
	// 입력 관련 구성
	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<class UInputAction> m_ShoulderMoveAction; 

	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<class UInputAction> m_ShoulderLookAction;

	UPROPERTY(VisibleAnywhere, Category = Input, BlueprintReadOnly)
	TObjectPtr<class UInputAction> m_TestAction;


};
