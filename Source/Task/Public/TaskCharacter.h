
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TaskCharacter.generated.h"

// 스프링 암 관련 클래스 헤더
class USpringArmComponent;
//카메라 관련 클래스 전방 선언
class UCameraComponent;
//Enhanced Input에서 액션 값을 받을 때 사용한느 구조체
struct FInputActionValue;

UCLASS()
class TASK_API ATaskCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ATaskCharacter();

protected:
	
	//스프링 암 컴포넌트
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	//카메라 컴포넌트
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Movement")
	float NormalSpeed;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeedMultiplier;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Movement")
	float SprintSpeed;

	// 입력 바인딩 처리 함수
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
