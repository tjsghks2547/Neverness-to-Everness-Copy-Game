// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "IH_NaNally_AnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class NEVERNESS_API UIH_NaNally_AnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	// 생성자
	UIH_NaNally_AnimInstance(); 

protected: 
	// 애니메이션 초기화될 때 호출되는 함수. 
	virtual void NativeInitializeAnimation() override; 

	// 애니메이션을 업데이트 할 때마다(Tick 마다) 실행되는 함수. 
	virtual void NativeUpdateAnimation(float DeltaSeconds) override; 


protected:
	// 오너를 저장해두고 재활용.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Character")
	TObjectPtr<class ACharacter> Owner; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Character")
	TObjectPtr<class UCharacterMovementComponent> Movement;

	// Idle - Move 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = "Character")
	FVector Velocity; 

	// 이동 빠르기 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float GroundSpeed; 

	// 이동하는지 멈춰있는지 확인하는 변수.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	bool bIsIdle;

	// 이동 여부를 판단할 때 사용할 문턱 값.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float MovingThreshold; 

	// 이동 여부를 판단할 때 사용할 문턱 값.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	bool bIsFalling; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	bool bIsJumping; 

	// 점프 여부를 판단할 때 사용할 문턱 값.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	float JumpingThreshold;

};
