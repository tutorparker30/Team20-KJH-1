
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
	// Pawn�� ����
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CamreaComp"));
	CameraComp-> SetupAttachment(SpringArmComp);

	// �Է� �� �ʱ�ȭ
	MovementInput = FVector2D::ZeroVector;
	LookInput = FVector2D::ZeroVector;
	Velocity = FVector::ZeroVector;
}


void ATaskPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ī�޶� ���� ȸ�� ������ Yaw ����
	const FRotator CameraRotation = CameraComp->GetComponentRotation();
	const FRotator YawOnlyRotation(0.0f, CameraRotation.Yaw, 0.0f);
	// ī�޶� �������� Forward, Right ���� ���
	const FVector CameraForward = FRotationMatrix(YawOnlyRotation).GetUnitAxis(EAxis::X);
	const FVector CameraRight = FRotationMatrix(YawOnlyRotation).GetUnitAxis(EAxis::Y);
	// �Է°��� ���� �̵� ���� ����
	const FVector InputDirection = (CameraForward * MovementInput.X) + (CameraRight * MovementInput.Y);
	// ��ǥ �̵� �ӵ� ���
	const FVector DesiredVelocity = InputDirection.GetSafeNormal() * MaxWalkSpeed;
	// ���� �ӵ��� ���� �����Ͽ� ������ ǥ��
	Velocity = FMath::VInterpTo(Velocity, DesiredVelocity, DeltaTime, VelocityInterpSpeed);
	// ���� ��ǥ�迡�� �̵� ó��(�浹 üũ ����)
	AddActorWorldOffset(Velocity * DeltaTime, true);
	// Pawn ��ü ȸ�� ó�� (���콺 �¿� �Է�)
	if (!FMath::IsNearlyZero(LookInput.X))
	{
		const float YawRotation = LookInput.X * TurnRate * DeltaTime;
		AddActorLocalRotation(FRotator(0.0f, YawRotation, 0.0f));
	}

	// �������� ȸ�� ó�� (���콺 ���� �Է�)
	if (!FMath::IsNearlyZero(LookInput.Y))
	{
		// ���� ���������� ���� ȸ���� ��������
		FRotator CurrentArmRotation = SpringArmComp->GetRelativeRotation();
		// ���콺 �Է¿� ���� Pitch  ����
		float NewPitch = CurrentArmRotation.Pitch - (LookInput.Y * LookUpRate * DeltaTime);
		// Pitch ���� �ּ�/�ִ� ������ ����
		NewPitch = FMath::Clamp(NewPitch, MinPitch, MaxPitch);
		CurrentArmRotation.Pitch = NewPitch;
		SpringArmComp->SetRelativeRotation(CurrentArmRotation);
	}	
}

// �Է� ���ε�
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



