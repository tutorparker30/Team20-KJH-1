#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArchedWall.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogTask, Warning, All);

UCLASS()
class TASK_API AArchedWall : public AActor
{
	GENERATED_BODY()
	
public:	

	AArchedWall();

// 컴포넌트 관련
protected:
	
	// 루트 컴포넌트 나타내는 Scene Component 포인터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ArchedWall|Components")
	USceneComponent* SceneRoot;
	// Static Mesh Component 포인터
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ArchedWall|Components")
	UStaticMeshComponent* StaticMeshComp;

	// 목표 위치 지정
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ArchedWall|PropertiesX")
	FVector TargetLocation;


	// 이동 관련
	// 전방 이동 속도
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "ArchedWall|PropertiesX")
	float MoveSpeedForward;
	
	// 좌우 이동 범위
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "ArchedWall|PropertiesY")
	float MoveRange;
	// 좌우 이동 속도
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "ArchedWall|PropertiesY")
	float MoveSpeedSide;

	

	// 이동 시작 Y좌표
	float StartLocationY;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:

	// 거리 오차 범위
	float DistanceThreshold;
	

	// 목표 도달시 삭제
	void CheckAndDelete();
};
