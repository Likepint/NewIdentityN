#pragma once

#include "CoreMinimal.h"
#include "Items/Equipments/Weapons/CSubAction.h"
#include "Items/Equipments/Weapons/CWeaponStructures.h"
#include "Kismet/KismetSystemLibrary.h"
#include "CSubAction_Harpoon.generated.h"

UCLASS()
class NEWIDENTITYN_API UCSubAction_Harpoon : public UCSubAction
{
	GENERATED_BODY()
	
private:
    UPROPERTY(EditDefaultsOnly, Category = "Trace")
    float Distance = 1000;

    UPROPERTY(EditDefaultsOnly, Category = "Trace")
    float Speed = 200;

    UPROPERTY(EditDefaultsOnly, Category = "Trace")
    TEnumAsByte<EDrawDebugTrace::Type> DrawDebug;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Action")
    FDoActionData ActionData;

    UPROPERTY(EditDefaultsOnly, Category = "Action")
    FHitData HitData;

public:
    void Pressed() override;
    void Begin_ChargeAction_Implementation() override;
    void End_ChargeAction_Implementation() override;
    void Tick_Implementation(float InDeltaTime) override;

private:
    UFUNCTION()
    void OnAttachmentBeginOverlap(class ACCharacter* InAttacker, AActor* InAttackCuaser, class ACCharacter* InOther);

private:
    bool bMoving;

    FVector Start;
    FVector End;

    TArray<class ACCharacter*> Overlapped;
    TArray<class ACCharacter*> Hitted;

};
