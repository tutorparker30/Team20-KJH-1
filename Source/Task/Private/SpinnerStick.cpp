#include "SpinnerStick.h"


ASpinnerStick::ASpinnerStick()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Shapes/Shape_Pipe.Shape_Pipe"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}

	PrimaryActorTick.bAllowTickBatching = true;
}

// Called when the game starts or when spawned
void ASpinnerStick::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpinnerStick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(SpinSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, SpinSpeed * DeltaTime, 0.0f));
	}

}

