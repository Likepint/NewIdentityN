#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CPlayerState.generated.h"

UENUM(BlueprintType)
enum class EPlayerRole : uint8
{
    None        UMETA(DisplayName = "None"),
    Survivor    UMETA(DisplayName = "Survivor"),
    Hunter      UMETA(DisplayName = "Hunter")
};

UCLASS()
class NEWIDENTITYN_API ACPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:
    // 선택된 Pawn 클래스
    UPROPERTY(Replicated, BlueprintReadOnly)
    TSubclassOf<APawn> SelectedPawnClass;

public:
    FORCEINLINE TSubclassOf<APawn> GetSelectedPawnClass() { return SelectedPawnClass; }

public:
    // 설정 함수
    void SetPlayerRoleAndClass(EPlayerRole InRole, TSubclassOf<APawn> InPawnClass);

protected:
    // 역할 정보
    UPROPERTY(Replicated, BlueprintReadOnly)
    EPlayerRole SelectedRole;

};
