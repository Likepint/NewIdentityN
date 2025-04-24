#include "Items/Equipments/Weapons/CSubAction.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"

UCSubAction::UCSubAction()
{

}

void UCSubAction::BeginPlay(ACCharacter* InOwnerCharacter, ACAttachment* InAttachment, UCDoAction* InDoAction)
{
    OwnerCharacter = InOwnerCharacter;
    Attachment = InAttachment;
    DoAction = InDoAction;

    State = CHelpers::GetComponent<UCStateComponent>(OwnerCharacter);
    Movement = CHelpers::GetComponent<UCMovementComponent>(OwnerCharacter);

}

void UCSubAction::Pressed()
{
    bInAction = true;

}

void UCSubAction::Released()
{
    bInAction = false;

}
