#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpinnerStick.generated.h"

UCLASS()
class TASK_API ASpinnerStick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpinnerStick();

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpinnerStick|Components")
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SpinnerStick|Components")
	UStaticMeshComponent* StaticMeshComp;

	//회전 속도
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpinnerStick|Properteis")
	float SpinSpeed;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
