#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CNewIdentityNGM.generated.h"

UCLASS()
class NEWIDENTITYN_API ACNewIdentityNGM : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Class")
    TSubclassOf<class APawn> SurvivorClass;

    UPROPERTY(EditDefaultsOnly, Category = "Class")
    TSubclassOf<class APawn> HunterClass;

public:
    FORCEINLINE TSubclassOf<APawn> GetSurvivorClass() const { return SurvivorClass; }
    FORCEINLINE TSubclassOf<APawn> GetHunterClass() const { return HunterClass; }

public:
    ACNewIdentityNGM();

public:
    APawn* SpawnCharacter(class ACPlayerController* Controller);

};
