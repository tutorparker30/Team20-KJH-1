
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TaskCharacter.generated.h"

// ������ �� ���� Ŭ���� ���
class USpringArmComponent;
//ī�޶� ���� Ŭ���� ���� ����
class UCameraComponent;
//Enhanced Input���� �׼� ���� ���� �� ����Ѵ� ����ü
struct FInputActionValue;

UCLASS()
class TASK_API ATaskCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ATaskCharacter();

protected:
	
	//������ �� ������Ʈ
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	//ī�޶� ������Ʈ
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Movement")
	float NormalSpeed;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeedMultiplier;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;

	// �Է� ���ε� ó�� �Լ�
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void StartJump(const FInputActionValue& value);
	UFUNCTION()
	void StopJump(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& value);


	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;



};
