#include "TaskPawnGameMode.h"
#include "TaskPawn.h"
#include "TaskPawnController.h"


ATaskPawnGameMode::ATaskPawnGameMode()
{
	// �⺻ ĳ���ͷ� ����
	DefaultPawnClass = ATaskPawn::StaticClass();
	// �÷��̾� ����ѷ� ����
	PlayerControllerClass = ATaskPawnController::StaticClass();
}
