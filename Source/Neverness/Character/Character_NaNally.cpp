// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Character_NaNally.h"
#include "CharacterBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "Component/StatComponent.h"
#include "UI/PlayerUIWidget.h"
#include "Component/Ui_InterAction_Component.h"
#include "Types/InterActionType.h"
#include "Components/CapsuleComponent.h"



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
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);

	// 컨트롤러의 회전 값을 사용할 지 여부. 
	// // 카메라 지지대(드론)에게 "컨트롤러(영혼)가 바라보는 방향을 똑같이 따라가라!" 라고 명령함
	SpringArm->bUsePawnControlRotation = true;

	SpringArm->TargetArmLength = 600.0f; 


	// Actor Component
	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
	UiComponent = CreateDefaultSubobject<UUi_InterAction_Component>(TEXT("UiComponent"));


#pragma endregion 

#pragma region 입력 관련 설정
	static ConstructorHelpers::FObjectFinder<UInputAction> ShoulderMoveActionRef(TEXT("/Game/Input/Action/IA_Shoulder_Walk.IA_Shoulder_Walk"));
	if(ShoulderMoveActionRef.Object != NULL)
	{
		ShoulderMoveAction = ShoulderMoveActionRef.Object; 
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> ShoulderLookActionRef(TEXT("/Game/Input/Action/IA_Shoulder_Look.IA_Shoulder_Look"));
	if(ShoulderLookActionRef.Object != NULL)
	{
		ShoulderLookAction = ShoulderLookActionRef.Object; 
	}
	
	static ConstructorHelpers::FObjectFinder<UInputAction> TestActionRef(TEXT("/Game/Input/Action/IA_Test_Hp.IA_Test_Hp"));
	if (TestActionRef.Object != NULL)
	{
		TestAction = TestActionRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> TestStaminaActionRef(TEXT("/Game/Input/Action/IA_Test_Stamina.IA_Test_Stamina"));
	if (TestStaminaActionRef.Object != NULL)
	{
		TestStaminaAction = TestStaminaActionRef.Object;
	}

#pragma endregion 



#pragma region 맴버변수 기본값 설정
	InterActionType = EInterActionType::None;
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
	
	StatComponent->SetUp_stat_Hp(100, 100);
	StatComponent->SetUp_stat_Stamina(100, 100);

	if(_InPlayerUiWidget)
	{
#pragma region HP와 Stamina 관련 
		// 초기값 초기화
		_InPlayerUiWidget->SetUp_Ui_Hp(StatComponent->GetCurrentHp(), StatComponent->GetMaxHp());
		_InPlayerUiWidget->SetUp_Ui_Stamina(StatComponent->GetCurrentStamina(), StatComponent->GetMaxStamina());

		// Ui widget의 default 값 초기화 하기.
		// Hp 관련 델리게이트 이벤트
		StatComponent->Delegate_OnHpChanged.AddUObject(_InPlayerUiWidget, &UPlayerUIWidget::UpdateHp);
		StatComponent->Delegate_OnHpChanged.AddUObject(_InPlayerUiWidget, &UPlayerUIWidget::UpdateProgressBarHp);

		// Stamina 관련 델리게이트 이벤트
		StatComponent->Delegate_OnStaminaChanged.AddUObject(_InPlayerUiWidget, &UPlayerUIWidget::UpdateProgressBarStamina);
#pragma endregion 
			

#pragma region InterAction 관련 
		UiComponent->Delegate_OnDialogRender.AddUObject(_InPlayerUiWidget, &UPlayerUIWidget::Set_DialogRenderOnOff);
		UiComponent->Delegate_OnInterActionFKeyStateChanged.AddUObject(_InPlayerUiWidget, &UPlayerUIWidget::F_KeyStateUpdate);
		UiComponent->Delegate_OnInterActionFKey_SetStateChanged.AddUObject(_InPlayerUiWidget, &UPlayerUIWidget::Set_F_KeyState);	
#pragma endregion 
	}

}








// Called every frame
void ACharacter_NaNally::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StatComponent->Delegate_OnStaminaChanged.Broadcast(StatComponent->GetCurrentStamina(), StatComponent->GetMaxStamina());
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
			ShoulderMoveAction,
			ETriggerEvent::Triggered,
			this,
			&ACharacter_NaNally::ShoulderMove
		);

		EnhancedInputComponent->BindAction(
			ShoulderLookAction,
			ETriggerEvent::Triggered,
			this,
			&ACharacter_NaNally::ShoulderLook
		);

		EnhancedInputComponent->BindAction(
			TestAction,
			ETriggerEvent::Triggered,
			this,
			&ACharacter_NaNally::TestUiAction
		);
	}
}

void ACharacter_NaNally::Render_InterActionUi(EInterActionType _Tag, ESlateVisibility _eSlateVisibility)
{
	UiComponent->Delegate_OnDialogRender.Broadcast(_Tag,_eSlateVisibility);

	switch (_Tag)
	{
	case EInterActionType::Item:
		//UiComponent->
		break;

	default:
		break; 
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

	AddControllerYawInput(RotationValue.X * 0.2f);
	AddControllerPitchInput(RotationValue.Y * 0.2f);

}

void ACharacter_NaNally::TestUiAction()
{
	/* hp 관련 테스트 코드 */
	//m_pStatComponent->Apply_Damage(50);
	//m_pStatComponent->Delegate_OnHpChanged.Broadcast(m_pStatComponent->GetCurrentHp());
	
	/* Stamina 관련 테스트 코드 */
	//StatComponent->Apply_Stamina(50);
	//m_pStatComponent->Delegate_OnStaminaChanged.Broadcast(m_pStatComponent->GetCurrentStamina(), m_pStatComponent->GetMaxStamina());

	const float DeltaTime = GetWorld()->GetDeltaSeconds();

	/*F키 상호작용 테스트 코드*/
	switch (InterActionType)
	{
	case EInterActionType::None:
		break;
	case EInterActionType::Dialog:
		break;
	case EInterActionType::Chest:
		break;
	case EInterActionType::Item:
		UiComponent->Delegate_OnInterActionFKeyStateChanged.Broadcast(DeltaTime);
		break;
	default:
		break;
	}
	
}

void ACharacter_NaNally::Ui_Key_State_Reset()
{
	UiComponent->Delegate_OnInterActionFKey_SetStateChanged.Broadcast(0.0f);
}


