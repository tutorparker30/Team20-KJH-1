#include "TaskGameMode.h"
#include "TaskCharacter.h"
#include "TaskPlayerController.h"


ATaskGameMode::ATaskGameMode()
{
	// 기본 캐릭터로 지정
	DefaultPawnClass = ATaskCharacter::StaticClass();
	// 플레이어 컨드롤러 적용
	PlayerControllerClass = ATaskPlayerController::StaticClass();
}
