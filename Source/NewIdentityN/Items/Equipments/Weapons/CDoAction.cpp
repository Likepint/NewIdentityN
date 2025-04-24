#include "Items/Equipments/Weapons/CDoAction.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Items/Equipments/Weapons/CAttachment.h"
#include "Items/Equipments/Weapons/CEquipment.h"

UCDoAction::UCDoAction()
{

}

void UCDoAction::BeginPlay(ACAttachment* InAttachment, UCEquipment* InEquipment, ACCharacter* InOwner, const TArray<FDoActionData>& InDoActionDatas, const TArray<FHitData>& InHitDatas)
{
    OwnerCharacter = InOwner;
    World = OwnerCharacter->GetWorld();

    State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
    Movement = CHelpers::GetComponent<UCMovementComponent>(OwnerCharacter);

    DoActionDatas = InDoActionDatas;
    HitDatas = InHitDatas;

}

void UCDoAction::DoAction()
{
    bInAction = true;

    State->SetActionMode();

}

void UCDoAction::Begin_DoAction()
{
    bBeginAction = true;

}

void UCDoAction::End_DoAction()
{
    bInAction = false;
    bBeginAction = false;

    State->SetDefaultMode();

    Movement->Move();
    Movement->DisableFixedCamera();

}
