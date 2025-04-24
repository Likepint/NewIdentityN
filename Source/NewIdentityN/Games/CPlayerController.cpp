#include "Games/CPlayerController.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"
#include "Games/CPlayerState.h"
#include "Games/CNewIdentityNGM.h"
#include "Net/UnrealNetwork.h"

void ACPlayerController::SetLobbyUIRef(UUserWidget* InWidget)
{
    LobbyUI = InWidget;

}

void ACPlayerController::ServerRequestSpawn_Implementation(EPlayerRole InRole)
{
    if (ACPlayerState* ps = GetPlayerState<ACPlayerState>())
    {
        TSubclassOf<APawn> selected = nullptr;

        // 역할에 따라 클래스 결정
        if (ACNewIdentityNGM* GM = GetWorld()->GetAuthGameMode<ACNewIdentityNGM>())
        {
            switch (InRole)
            {
            case EPlayerRole::Survivor:
                selected = GM->GetSurvivorClass();
                break;

            case EPlayerRole::Hunter:
                selected = GM->GetHunterClass();
                break;
            }
        }

        if (selected)
        {
            ps->SetPlayerRoleAndClass(InRole, selected);

            if (ACNewIdentityNGM* GM = GetWorld()->GetAuthGameMode<ACNewIdentityNGM>())
            {
                if (APawn* pawn = GM->SpawnCharacter(this))
                    ClientRemoveLobbyUI();
            }
        }
    }

}

void ACPlayerController::ClientRemoveLobbyUI_Implementation()
{
    if (LobbyUI)
    {
        LobbyUI->RemoveFromParent();
        LobbyUI = nullptr;

        bShowMouseCursor = false;

        this->SetInputMode(FInputModeGameOnly());
    }

}

void ACPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ACPlayerController, SelectedRole);

}
