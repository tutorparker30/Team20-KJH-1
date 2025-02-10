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

// ������Ʈ ����
protected:
	
	// ��Ʈ ������Ʈ ��Ÿ���� Scene Component ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ArchedWall|Components")
	USceneComponent* SceneRoot;
	// Static Mesh Component ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ArchedWall|Components")
	UStaticMeshComponent* StaticMeshComp;

	// ��ǥ ��ġ ����
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ArchedWall|PropertiesX")
	FVector TargetLocation;


	// �̵� ����
	// ���� �̵� �ӵ�
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "ArchedWall|PropertiesX")
	float MoveSpeedForward;
	
	// �¿� �̵� ����
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "ArchedWall|PropertiesY")
	float MoveRange;
	// �¿� �̵� �ӵ�
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "ArchedWall|PropertiesY")
	float MoveSpeedSide;

	

	// �̵� ���� Y��ǥ
	float StartLocationY;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
private:

	// �Ÿ� ���� ����
	float DistanceThreshold;
	

	// ��ǥ ���޽� ����
	void CheckAndDelete();
};
