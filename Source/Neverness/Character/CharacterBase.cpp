// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "EnhancedInputSubsystems.h"
#include "Player/IHPlayerController.h"

// Sets default values
ACharacterBase::ACharacterBase()
{

}

void ACharacterBase::SetCharacterViewControl(ECharacterControlViewType NewCharacterControlViewType)
{
	AIHPlayerController* PlayerController = Cast<AIHPlayerController>(GetController());

	if(PlayerController)
	{
		// 향상된 입력 시스템의 서브 시스템 가져오기 
		UEnhancedInputLocalPlayerSubsystem* InputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());

		// 향상된 입력 서브 시스템 얻어온 후에 사용할 매핑 컨텍스트 설정.
		if(InputSystem != NULL)
		{
			InputSystem->ClearAllMappings();

			// 새로운 입력 매핑 컨텍스트 추가.
			InputSystem->AddMappingContext(PlayerController->GetInputMappingContext(), 0);
		}
	}
	

}


