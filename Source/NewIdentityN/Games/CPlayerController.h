#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

UCLASS()
class NEWIDENTITYN_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
    UPROPERTY()
    class UUserWidget* LobbyUI;

public:
    UFUNCTION(BlueprintCallable)
    void SetLobbyUIRef(UUserWidget* InWidget);

    UFUNCTION(Server, Reliable)
    void ServerRequestSpawn(EPlayerRole InRole);
    void ServerRequestSpawn_Implementation(EPlayerRole InRole);

    UFUNCTION(Client, Reliable)
    void ClientRemoveLobbyUI();
    void ClientRemoveLobbyUI_Implementation();

public:
    UPROPERTY(Replicated)
    EPlayerRole SelectedRole;
	
};
