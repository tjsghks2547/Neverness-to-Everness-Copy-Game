// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Character_NaNally.h"
#include "CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Component/StatComponent.h"
#include "UI/PlayerUIWidget.h"

// Sets default values
ACharacter_NaNally::ACharacter_NaNally()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 기본 설정. 
	// 컨트롤러의 회전 값을 받아서 설정하는 옵션 비활성화. (컨트롤러의 회전과 캐릭터의 회전의 연결을 끊는거 ) 
	bUseControllerRotationPitch = false; // Y 축 회전.
	bUseControllerRotationRoll = false;  // Z 축 회전.
	bUseControllerRotationYaw = false;  // X 축 회전.


	// 메시 컴포넌트 설정. 
	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.0f, 0.0f, -88.0f),
		FRotator(0.0f, -90.0f, 0.0f)
	);

	GetMesh()->SetRelativeScale3D(FVector(0.025f, 0.025f, 0.025f));

#pragma region Mesh, Animation Asset 설정 및 적용
	// 메시 애셋 지정 (검색 필요함).
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterMesh(TEXT("/Game/Character/NaNally/NaNally_TPose.NaNally_TPose"));

	// 로드 성공했으면 설정. 
	if (CharacterMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterMesh.Object);
	}

	// 애님 블루프린트 클래스 정보 지정
	static ConstructorHelpers::FClassFinder<UAnimInstance> CharacterAnim(TEXT("/Game/BluePrint/NaNally/ABP_NaNallyAnimInstance.ABP_NaNallyAnimInstance_C"));

	if (CharacterAnim.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnim.Class);
	}
#pragma endregion

#pragma region Character Movement 설정 
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 800.0f; 
#pragma endregion 

#pragma region Component 생성 및 설정

	// Scene Component
	m_pSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	m_pCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	m_pSpringArm->SetupAttachment(RootComponent);
	m_pCamera->SetupAttachment(m_pSpringArm);

	// 컨트롤러의 회전 값을 사용할 지 여부. 
	// // 카메라 지지대(드론)에게 "컨트롤러(영혼)가 바라보는 방향을 똑같이 따라가라!" 라고 명령함
	m_pSpringArm->bUsePawnControlRotation = true;

	m_pSpringArm->TargetArmLength = 600.0f; 


	// Actor Component
	m_pStatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));



#pragma endregion 

#pragma region 입력 관련 설정
	static ConstructorHelpers::FObjectFinder<UInputAction> ShoulderMoveActionRef(TEXT("/Game/Input/Action/IA_Shoulder_Walk.IA_Shoulder_Walk"));
	if(ShoulderMoveActionRef.Object != NULL)
	{
		m_ShoulderMoveAction = ShoulderMoveActionRef.Object; 
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ShoulderLookActionRef(TEXT("/Game/Input/Action/IA_Shoulder_Look.IA_Shoulder_Look"));
	if(ShoulderLookActionRef.Object != NULL)
	{
		m_ShoulderLookAction = ShoulderLookActionRef.Object; 
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> TestActionRef(TEXT("/Game/Input/Action/IA_Test.IA_Test"));
	if (TestActionRef.Object != NULL)
	{
		m_TestAction = TestActionRef.Object;
	}

#pragma endregion 





}

// Called when the game starts or when spawned
void ACharacter_NaNally::BeginPlay()
{
	Super::BeginPlay();
	
	SetCharacterViewControl(ECharacterControlViewType::Shoulder);
}


void ACharacter_NaNally::SetupPlayerUiWidget(UPlayerUIWidget* _InPlayerUiWidget)
{
	// 설정할 플레이어의 체력 및 최대 체력
	
	m_pStatComponent->SetUp_stat_Hp(100, 100);

	if(_InPlayerUiWidget)
	{
		// 초기값 초기화
		_InPlayerUiWidget->SetUp_Ui_Hp(m_pStatComponent->GetCurrentHp(), m_pStatComponent->GetMaxHp());


		// Ui widget의 default 값 초기화 하기.
		m_pStatComponent->Delegate_OnHpChanged.AddUObject(_InPlayerUiWidget, &UPlayerUIWidget::UpdateHp);
		m_pStatComponent->Delegate_OnHpChanged.AddUObject(_InPlayerUiWidget, &UPlayerUIWidget::UpdateProgressBarHp);
	}




}


// Called every frame
void ACharacter_NaNally::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input 
// Player Controller에서 Possess가 되는 순간 호출 
void ACharacter_NaNally::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 바인딩 - 향상된 입력 시스템 컴포넌트를 활용해서 설정.
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if(EnhancedInputComponent)
	{
		// 입력 바인딩 -> 이벤트와 실행 함수를 연결하는 과정 
		EnhancedInputComponent->BindAction(
			m_ShoulderMoveAction,
			ETriggerEvent::Triggered,
			this,
			&ACharacter_NaNally::ShoulderMove
		);

		EnhancedInputComponent->BindAction(
			m_ShoulderLookAction,
			ETriggerEvent::Triggered,
			this,
			&ACharacter_NaNally::ShoulderLook
		);

		EnhancedInputComponent->BindAction(
			m_TestAction,
			ETriggerEvent::Started,
			this,
			&ACharacter_NaNally::TestAction
		);
	}
}

void ACharacter_NaNally::ShoulderMove(const FInputActionValue& Value)
{
	// 입력 값 읽어오기 ( 입력에 지정된 타입으로 변환 ).
	FVector2D Movement = Value.Get<FVector2D>();

	// 이동할 방향 만들기
	// 카메라가 바라보는 방향 (컨트롤러의 방향과 같음)을 기준으로 방향 만들기
	// GetControlRotation()은 항상 월드의 0도를 기준으로 (절대적인 정북쪽)으로 계산된 현재의 절대 회전 각도를 반환
	FRotator Rotation = GetControlRotation(); 

	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	// 앞 방향
	FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // x축이 언리얼 기준으로 앞방향 ( Look Vector )

	// 오른쪽 방향 
	FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // y축이 언리얼 기준으로 여

	// 무브먼트 컴포넌트에 입력 전달하기
	AddMovementInput(ForwardVector, Movement.X);
	AddMovementInput(RightVector, Movement.Y);


}

void ACharacter_NaNally::ShoulderLook(const FInputActionValue& Value)
{
	// 입력 값 
	FVector2D RotationValue = Value.Get<FVector2D>(); 

	AddControllerYawInput(RotationValue.X);
	AddControllerPitchInput(RotationValue.Y);

}

void ACharacter_NaNally::TestAction()
{
	m_pStatComponent->Apply_Damage(50);

	m_pStatComponent->Delegate_OnHpChanged.Broadcast(m_pStatComponent->GetCurrentHp());
	
}


