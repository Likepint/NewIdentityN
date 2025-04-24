#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/DamageEvents.h"
#include "CWeaponStructures.generated.h"

USTRUCT()
struct FEquipmentData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    class UAnimMontage* Montage;

    UPROPERTY(EditAnywhere)
    float PlayRate = 1;

    UPROPERTY(EditAnywhere)
    bool bCanMove = true;

    UPROPERTY(EditAnywhere)
    bool bUseControlRotation = true;
};

USTRUCT()
struct FDoActionData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    class UAnimMontage* Montage;

    UPROPERTY(EditAnywhere)
    float PlayRate = 1;

    UPROPERTY(EditAnywhere)
    bool bCanMove = true;

    UPROPERTY(EditAnywhere)
    bool bFixedCamera;

    UPROPERTY(EditAnywhere)
    class UFXSystemAsset* Effect;

    UPROPERTY(EditAnywhere)
    FVector EffectLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere)
    FVector EffectScale = FVector::OneVector;

public:
    void DoAction(class ACCharacter* InOwner);
    void PlayEffect(UWorld* InWorld, const FVector& InLocation);
    void PlayEffect(UWorld* InWorld, const FVector& InLocation, const FRotator& InRotation);
};

USTRUCT()
struct FHitData
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    class UAnimMontage* Montage;

    UPROPERTY(EditAnywhere)
    float PlayRate = 1;

    UPROPERTY(EditAnywhere)
    float Power;

    UPROPERTY(EditAnywhere)
    float Launch = 100;

    UPROPERTY(EditAnywhere)
    float StopTime;

    UPROPERTY(EditAnywhere)
    class USoundWave* Sound;

    UPROPERTY(EditAnywhere)
    class UFXSystemAsset* Effect;

    UPROPERTY(EditAnywhere)
    FVector EffectLocation = FVector::ZeroVector;

    UPROPERTY(EditAnywhere)
    FVector EffectScale = FVector::OneVector;

public:
    void SendDamage(class ACCharacter* InAttacker, AActor* InAttackCauser, class ACCharacter* InOther);
    void PlayMontage(class ACCharacter* InOwner);
    void PlayHitStop(UWorld* InWorld);
    void PlaySoundWave(class ACCharacter* InOwner);
    void PlayEffect(UWorld* InWorld, const FVector& InLocation);
    void PlayEffect(UWorld* InWorld, const FVector& InLocation, const FRotator& InRotation);
};

USTRUCT()
struct FActionDamageEvent
    : public FDamageEvent
{
    GENERATED_BODY()

public:
    FHitData* HitData;
};

UCLASS()
class NEWIDENTITYN_API UCWeaponStructures : public UObject
{
	GENERATED_BODY()
	
};
