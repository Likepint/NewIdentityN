﻿#include "Items/Equipments/Weapons/CEquipment.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CMovementComponent.h"
#include "Components/CStateComponent.h"

void UCEquipment::BeginPlay(ACCharacter* InOwner, const FEquipmentData& InData)
{
    OwnerCharacter = InOwner;
    Data = InData;

    Movement = CHelpers::GetComponent<UCMovementComponent>(InOwner);
    State = CHelpers::GetComponent<UCStateComponent>(InOwner);

}

void UCEquipment::Equip_Implementation()
{
    State->SetEquipMode();

    if (OnEquipmentEquip.IsBound())
        OnEquipmentEquip.Broadcast();


    if (Data.bCanMove == false)
        Movement->Stop();

    if (Data.bUseControlRotation)
        Movement->EnableControlRotation();

    if (!!Data.Montage)
    {
        OwnerCharacter->PlayAnimMontage(Data.Montage, Data.PlayRate);
    }
    else
    {
        Begin_Equip();
        End_Equip();
    }

}

void UCEquipment::Begin_Equip_Implementation()
{
    bBeginEquip = true;

    if (OnEquipmentBeginEquip.IsBound())
        OnEquipmentBeginEquip.Broadcast();

}

void UCEquipment::End_Equip_Implementation()
{
    bBeginEquip = false;
    bEquipped = true;

    Movement->Move();
    State->SetDefaultMode();

}

void UCEquipment::Unequip_Implementation()
{
    bEquipped = false;
    Movement->DisableControlRotation();

    if (OnEquipmentUnequip.IsBound())
        OnEquipmentUnequip.Broadcast();

}
