﻿#include "Items/Equipments/Weapons/CWeaponAsset.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Items/Equipments/Weapons/CWeaponData.h"
#include "Items/Equipments/Weapons/CAttachment.h"
#include "Items/Equipments/Weapons/CEquipment.h"
#include "Items/Equipments/Weapons/CDoAction.h"
#include "Items/Equipments/Weapons/CSubAction.h"
#include "Items/Equipments/Weapons/Skills/CSkill.h"

UCWeaponAsset::UCWeaponAsset()
{
    AttachmentClass = ACAttachment::StaticClass();
    EquipmentClass = UCEquipment::StaticClass();
    DoActionClass = UCDoAction::StaticClass();

}

void UCWeaponAsset::BeginPlay(ACCharacter* InOwner, UCWeaponData** OutWeaponData)
{
    ACAttachment* attachment = nullptr;
    if (!!AttachmentClass)
    {
        FActorSpawnParameters params;
        params.Owner = InOwner;

        attachment = InOwner->GetWorld()->SpawnActor<ACAttachment>(AttachmentClass, params);
    }

    UCEquipment* equipment = nullptr;
    if (!!EquipmentClass)
    {
        equipment = NewObject<UCEquipment>(this, EquipmentClass);
        equipment->BeginPlay(InOwner, EquipmentData);

        if (!!attachment)
        {
            equipment->OnEquipmentBeginEquip.AddDynamic(attachment, &ACAttachment::OnBeginEquip);
            equipment->OnEquipmentUnequip.AddDynamic(attachment, &ACAttachment::OnUnequip);
        }
    }

    UCDoAction* doAction = nullptr;
    if (!!DoActionClass)
    {
        doAction = NewObject<UCDoAction>(this, DoActionClass);
        doAction->BeginPlay(attachment, equipment, InOwner, DoActionDatas, HitDatas);

        if (!!attachment)
        {
            attachment->OnAttachmentBeginCollision.AddDynamic(doAction, &UCDoAction::OnAttachmentBeginCollision);
            attachment->OnAttachmentEndCollision.AddDynamic(doAction, &UCDoAction::OnAttachmentEndCollision);

            attachment->OnAttachmentBeginOverlap.AddDynamic(doAction, &UCDoAction::OnAttachmentBeginOverlap);
            attachment->OnAttachmentEndOverlap.AddDynamic(doAction, &UCDoAction::OnAttachmentEndOverlap);
        }

        if (!!equipment)
        {
            equipment->OnEquipmentBeginEquip.AddDynamic(doAction, &UCDoAction::OnBeginEquip);
            equipment->OnEquipmentUnequip.AddDynamic(doAction, &UCDoAction::OnUnequip);
        }
    }

    UCSubAction* subAction = nullptr;
    if (!!SubActionClass)
    {
        subAction = NewObject<UCSubAction>(this, SubActionClass);
        subAction->BeginPlay(InOwner, attachment, doAction);
    }

    UCSkill* skill = nullptr;
    if (!!SkillClass)
    {
        skill = NewObject<UCSkill>(this, SkillClass);
        skill->BeginPlay(InOwner, attachment, skill);
    }

    *OutWeaponData = NewObject<UCWeaponData>();
    (*OutWeaponData)->Attachment = attachment;
    (*OutWeaponData)->Equipment = equipment;
    (*OutWeaponData)->DoAction = doAction;
    (*OutWeaponData)->SubAction = subAction;
    (*OutWeaponData)->Skill = skill;

}
