#pragma once

#include "CoreMinimal.h"
#include "Items/Equipments/Weapons/CDoAction.h"
#include "CDoAction_Combo.generated.h"

UCLASS()
class NEWIDENTITYN_API UCDoAction_Combo : public UCDoAction
{
	GENERATED_BODY()
	
public:
    FORCEINLINE void EnableCombo() { bEnable = true; }
    FORCEINLINE void DisableCombo() { bEnable = false; }

public:
    void DoAction() override;
    void Begin_DoAction() override;
    void End_DoAction() override;

public:
    void OnAttachmentBeginOverlap(class ACCharacter* InAttacker, AActor* InAttackCuaser, class ACCharacter* InOther) override;
    void OnAttachmentEndCollision() override;

private:
    int32 Index;

    bool bEnable;
    bool bExist;

private:
    TArray<class ACCharacter*> Hitted;

};
