// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

// 열거형 ( 현재 입력 컨트롤을 관리하기 위함).
UENUM()
enum class ECharacterControlViewType : uint8
{
	Shoulder,
	Quarter,
};


UCLASS()
class NEVERNESS_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	void SetCharacterViewControl(ECharacterControlViewType NewCharacterControlViewType);

};
