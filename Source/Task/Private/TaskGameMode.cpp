#include "TaskGameMode.h"
#include "TaskCharacter.h"
#include "TaskPlayerController.h"


ATaskGameMode::ATaskGameMode()
{
	// �⺻ ĳ���ͷ� ����
	DefaultPawnClass = ATaskCharacter::StaticClass();
	// �÷��̾� ����ѷ� ����
	PlayerControllerClass = ATaskPlayerController::StaticClass();
}
