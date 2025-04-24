#include "Games/CPlayerState.h"
#include "Net/UnrealNetwork.h"

void ACPlayerState::SetPlayerRoleAndClass(EPlayerRole InRole, TSubclassOf<APawn> InPawnClass)
{
    if (HasAuthority())
    {
        SelectedRole = InRole;
        SelectedPawnClass = InPawnClass;
    }

}

void ACPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(ACPlayerState, SelectedRole);
    DOREPLIFETIME(ACPlayerState, SelectedPawnClass);

}