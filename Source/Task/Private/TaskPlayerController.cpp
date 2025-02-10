#include "TaskPlayerController.h"
#include "EnhancedInputSubsystems.h"

ATaskPlayerController::ATaskPlayerController()
	: InputMappingContext(nullptr),
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr)
{
}

void ATaskPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// ���� PlayerController�� ����� Local Player ��ü ��������
	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		//Local Player���� EnhancedInputLocalplayerSubsystem�� ȹ��
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				// Subsystem�� ���� �Ҵ��� IMC�� Ȱ��ȭ
				// �켱������ 0�� ���� ���� �켱����
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}


