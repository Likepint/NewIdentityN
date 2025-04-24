#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Items/Equipments/Weapons/CWeaponStructures.h"
#include "CWeaponAsset.generated.h"

UCLASS()
class NEWIDENTITYN_API UCWeaponAsset : public UDataAsset
{
	GENERATED_BODY()
	
private:
    UPROPERTY(EditAnywhere)
    TSubclassOf<class ACAttachment> AttachmentClass;

    UPROPERTY(EditAnywhere)
    FEquipmentData EquipmentData;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class UCEquipment> EquipmentClass;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class UCDoAction> DoActionClass;

    UPROPERTY(EditAnywhere)
    TArray<FDoActionData> DoActionDatas;

    UPROPERTY(EditAnywhere)
    TArray<FHitData> HitDatas;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class UCSubAction> SubActionClass;

    UPROPERTY(EditAnywhere)
    TSubclassOf<class UCSkill> SkillClass;

public:
    UCWeaponAsset();

    void BeginPlay(class ACCharacter* InOwner, class UCWeaponData** OutWeaponData);

};
