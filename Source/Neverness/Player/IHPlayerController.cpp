// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/IHPlayerController.h"
#include "InputMappingContext.h"
#include "UI/PlayerUIWidget.h"


AIHPlayerController::AIHPlayerController()
{
	// InputMapping Context 관련

#pragma region IMC Mapping Context
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Game/Input/IMC_Default.IMC_Default"));

	if(InputMappingContextRef.Object != NULL)
	{
		m_InputMappingContext = InputMappingContextRef.Object; 
	}
#pragma endregion 

#pragma region UI_Widget
	static ConstructorHelpers::FClassFinder<UPlayerUIWidget> PlayerWidgetRef(TEXT("/Game/UI/WBP_MainUI.WBP_MainUI_C"));
	
	if(PlayerWidgetRef.Succeeded())
	{
		PlayerUiWidgetClass = PlayerWidgetRef.Class;
	}


#pragma endregion 
	

}

void AIHPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 입력 모드 설정.
	// 게임 시작되면 뷰포트로 바로 입력 되도록.
	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);

	
	// 위젯 생성
	//PlayerUiWidget이 바로 TSubclassOf<UPlayerUIWidget> 타입이어야 합니다.
	//왜냐하면 CreateWidget은 새 위젯 객체를 생성하는 함수입니다.
	//객체를 만들려면 “무슨 클래스로 만들지”를 알아야 합니다.

	m_pPlayerUiWidget = CreateWidget<UPlayerUIWidget>(this, PlayerUiWidgetClass);
	
	// 위젯 화면에 추가 
	if(m_pPlayerUiWidget != NULL)
	{
		m_pPlayerUiWidget->AddToViewport();
	}



}
