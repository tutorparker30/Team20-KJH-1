#include "TaskPawnGameMode.h"
#include "TaskPawn.h"
#include "TaskPawnController.h"


ATaskPawnGameMode::ATaskPawnGameMode()
{
	// 기본 캐릭터로 지정
	DefaultPawnClass = ATaskPawn::StaticClass();
	// 플레이어 컨드롤러 적용
	PlayerControllerClass = ATaskPawnController::StaticClass();
}
