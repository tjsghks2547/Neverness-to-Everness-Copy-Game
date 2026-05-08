// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/IHwanModeBase.h"
#include "Character/Character_NaNally.h"
#include "Player/IHPlayerController.h"


AIHwanModeBase::AIHwanModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> PawnClassRef(TEXT("/Game/BluePrint/NaNally/BP_NaNally.BP_NaNally_C"));
	if(PawnClassRef.Class != NULL)
	{
		DefaultPawnClass = PawnClassRef.Class;
	}

	// 기본 컨트롤러 클래스 설정
	PlayerControllerClass = AIHPlayerController::StaticClass();


}



