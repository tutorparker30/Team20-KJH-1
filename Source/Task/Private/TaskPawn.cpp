
#include "TaskPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "TaskPawnController.h"

// Sets default values
ATaskPawn::ATaskPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	RootComponent = CapsuleComp;
	CapsuleComp->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComp->SetSimulatePhysics(false);

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(CapsuleComp);
	MeshComp->SetSimulatePhysics(false);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(CapsuleComp);
	SpringArmComp->TargetArmLength = 300.f;
	// Pawn과 별개
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CamreaComp"));
	CameraComp-> SetupAttachment(SpringArmComp);

	// 입력 값 초기화
	MovementInput = FVector2D::ZeroVector;
	LookInput = FVector2D::ZeroVector;
	Velocity = FVector::ZeroVector;
}


void ATaskPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 카메라 현재 회전 값에서 Yaw 추출
	const FRotator CameraRotation = CameraComp->GetComponentRotation();
	const FRotator YawOnlyRotation(0.0f, CameraRotation.Yaw, 0.0f);
	// 카메라 기준으로 Forward, Right 벡터 계산
	const FVector CameraForward = FRotationMatrix(YawOnlyRotation).GetUnitAxis(EAxis::X);
	const FVector CameraRight = FRotationMatrix(YawOnlyRotation).GetUnitAxis(EAxis::Y);
	// 입력값에 따른 이동 방향 결정
	const FVector InputDirection = (CameraForward * MovementInput.X) + (CameraRight * MovementInput.Y);
	// 목표 이동 속도 계산
	const FVector DesiredVelocity = InputDirection.GetSafeNormal() * MaxWalkSpeed;
	// 현재 속도에 보간 적용하여 가감속 표현
	Velocity = FMath::VInterpTo(Velocity, DesiredVelocity, DeltaTime, VelocityInterpSpeed);
	// 월드 좌표계에서 이동 처리(충돌 체크 포함)
	AddActorWorldOffset(Velocity * DeltaTime, true);
	// Pawn 자체 회전 처리 (마우스 좌우 입력)
	if (!FMath::IsNearlyZero(LookInput.X))
	{
		const float YawRotation = LookInput.X * TurnRate * DeltaTime;
		AddActorLocalRotation(FRotator(0.0f, YawRotation, 0.0f));
	}

	// 스프링암 회전 처리 (마우스 상하 입력)
	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		// 현재 스프링압의 로컬 회전값 가져오기
		FRotator CurrentArmRotation = SpringArmComp->GetRelativeRotation();
		// 마우스 입력에 따라 Pitch  조정
		float NewPitch = CurrentArmRotation.Pitch - (LookInput.Y * LookUpRate * DeltaTime);
		// Pitch 값을 최소/최대 값으로 제한
		NewPitch = FMath::Clamp(NewPitch, MinPitch, MaxPitch);
		CurrentArmRotation.Pitch = NewPitch;
		SpringArmComp->SetRelativeRotation(CurrentArmRotation);
	}	
}

// 입력 바인딩
void ATaskPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ATaskPawnController* MyController = Cast<ATaskPawnController>(GetController()))
		{
			if (MyController->MoveAction)
			{
				EnhancedInput->BindAction(
					MyController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ATaskPawn::Move
				);

				EnhancedInput->BindAction(
					MyController->MoveAction,
					ETriggerEvent::Completed,
					this,
					&ATaskPawn::StopMove
				);
			}

			if (MyController->LookAction)
			{
				
				EnhancedInput->BindAction(
					MyController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ATaskPawn::Look
				);
				
				EnhancedInput->BindAction(
					MyController->LookAction,
					ETriggerEvent::Completed,
					this,
					&ATaskPawn::StopLook
				);
			}
		}
	}

}

void ATaskPawn::Move(const FInputActionValue& Value)
{
	MovementInput = Value.Get<FVector2D>();
}

void ATaskPawn::StopMove(const FInputActionValue& Value)
{
	MovementInput = FVector2D::ZeroVector;
}

void ATaskPawn::Look(const FInputActionValue& Value)
{
	LookInput = Value.Get<FVector2D>();
}

void ATaskPawn::StopLook(const FInputActionValue& Value)
{
	LookInput = FVector2D::ZeroVector;
}



