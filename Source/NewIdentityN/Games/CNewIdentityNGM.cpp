#include "Games/CNewIdentityNGM.h"
#include "Global.h"
#include "Games/CPlayerController.h"
#include "Games/CPlayerState.h"
#include "GameFramework/PlayerStart.h"
#include "EngineUtils.h"

ACNewIdentityNGM::ACNewIdentityNGM()
{
	bStartPlayersAsSpectators = true;

	ConstructorHelpers::FClassFinder<ACPlayerController> controller(TEXT("/Script/Engine.Blueprint'/Game/Characters/BP_CPlayerController.BP_CPlayerController_C'"));
	if (controller.Succeeded())
		PlayerControllerClass = controller.Class;

}

APawn* ACNewIdentityNGM::SpawnCharacter(ACPlayerController* Controller)
{
    CheckNullResult(Controller, nullptr);

    ACPlayerState* ps = Controller->GetPlayerState<ACPlayerState>();
    CheckNullResult(ps, nullptr);
    CheckNullResult(ps->GetSelectedPawnClass(), nullptr);

    // 플레이어 시작 위치 선택
    TArray<APlayerStart*> starts;
    for (TActorIterator<APlayerStart> it(GetWorld()); it; ++it)
        starts.Add(*it);
    CheckTrueResult(starts.Num() == 0, nullptr);

    const int32 Index = FMath::RandRange(0, starts.Num() - 1);
    APlayerStart* SelectedStart = starts[Index];
    FTransform SpawnTransform = SelectedStart->GetActorTransform();

    APawn* Pawn = GetWorld()->SpawnActor<APawn>(ps->GetSelectedPawnClass(), SpawnTransform);
    CheckNullResult(Pawn, nullptr);

    Controller->Possess(Pawn);
    SelectedStart->Destroy();

    return Pawn;

}
