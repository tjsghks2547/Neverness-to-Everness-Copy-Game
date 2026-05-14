// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Item/TreasureBox.h"
#include "Components/BoxComponent.h"
#include "Character/Character_NaNally.h"
#include "Components/SlateWrapperTypes.h"
#include "Types/InterActionType.h"


// Sets default values
ATreasureBox::ATreasureBox()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 메시 컴포넌트 설정 ( 크기 설정 )
	GetMesh()->SetRelativeScale3D(FVector(0.01f, 0.01f, 0.01f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));


	// 메시 에셋 지정 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BoxMeshRef(TEXT("/Game/Character/Item/TreaseBox/Treasurebox.Treasurebox"));
	if (BoxMeshRef.Object != NULL)
	{
		GetMesh()->SetSkeletalMesh(BoxMeshRef.Object);
	};

	// 애니 블루프린트 클래스 저장
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceRef(TEXT("/Game/BluePrint/Character/Item/TreasureBox/ABP_TreasureBox.ABP_TreasureBox_C"));
	if(AnimInstanceRef.Class != NULL)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceRef.Class);
	}

	
	// Scene 컴포넌트 설정
	BoxColliderComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box_Collider"));
	ensureAlways(BoxColliderComponent);

	// 루트에 붙이기
	BoxColliderComponent->SetupAttachment(RootComponent);

	//// 콜리전 설정
	//m_pBoxColliderComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//m_pBoxColliderComponent->SetGenerateOverlapEvents(true);

	BoxColliderComponent->OnComponentBeginOverlap.AddDynamic(this, &ATreasureBox::OnOverlapBegin);
	BoxColliderComponent->OnComponentEndOverlap.AddDynamic(this, &ATreasureBox::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ATreasureBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATreasureBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	// 현재 겹치고 있는 Actor 목록 가져오기
	//m_pBoxColliderComponent->GetOverlappingActors(OverlappingActors);
	//
	//for(AActor* Actor : OverlappingActors)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("겹치는 중: %s"), *Actor->GetName());

	//	if(Actor->ActorHasTag(TEXT("Player")))
	//	{
	//		ACharacter_NaNally* pPlayer = Cast<ACharacter_NaNally>(Actor);

	//		if(pPlayer != NULL)
	//		{
	//			pPlayer->Render_InterActionUi();
	//		}
	//	}
	//}
	
	
	
	
	// 여기서 UI on/off하면 될듯 
	



}

// Called to bind functionality to input
void ATreasureBox::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATreasureBox::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag(TEXT("Player")))
	{
		ACharacter_NaNally* pPlayer = Cast<ACharacter_NaNally>(OtherActor);

		if(pPlayer != NULL)
		{  
			pPlayer->Render_InterActionUi(EInterActionType::Item, ESlateVisibility::Visible);
			pPlayer->Set_Current_OverlapTypes(EInterActionType::Item);
		}
	}
}

void ATreasureBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(TEXT("Player")))
	{
		ACharacter_NaNally* pPlayer = Cast<ACharacter_NaNally>(OtherActor);

		if (pPlayer != NULL)
		{
			pPlayer->Render_InterActionUi(EInterActionType::Item, ESlateVisibility::Collapsed);
			pPlayer->Set_Current_OverlapTypes(EInterActionType::None);
			pPlayer->Ui_Key_State_Reset();
		}
	}
}

