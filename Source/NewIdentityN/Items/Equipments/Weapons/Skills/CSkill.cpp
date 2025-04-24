#include "Items/Equipments/Weapons/Skills/CSkill.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"

UCSkill::UCSkill()
{

}

void UCSkill::BeginPlay(ACCharacter* InOwner, ACAttachment* InAttachment, UCSkill* InSkill)
{
    Owner = InOwner;
    Attachment = InAttachment;
    Skill = InSkill;

    State = CHelpers::GetComponent<UCStateComponent>(Owner);
    Movement = CHelpers::GetComponent<UCMovementComponent>(Owner);

}

void UCSkill::Pressed()
{
    bInAction = true;

}

void UCSkill::Released()
{
    bInAction = false;

}
