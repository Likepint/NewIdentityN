#include "Items/Equipments/Weapons/CWeaponStructures.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Animation/AnimMontage.h"

void FDoActionData::DoAction(ACCharacter* InOwner)
{
    UCMovementComponent* movement = CHelpers::GetComponent<UCMovementComponent>(InOwner);

    if (!!movement)
    {
        if (bFixedCamera)
            movement->EnableFixedCamera();

        if (bCanMove == false)
            movement->Stop();
    }

    if (!!Montage)
        InOwner->PlayAnimMontage(Montage, PlayRate);

}

void FDoActionData::PlayEffect(UWorld* InWorld, const FVector& InLocation)
{
    CheckNull(Effect);

    FTransform transform;
    transform.SetLocation(EffectLocation);
    transform.SetScale3D(EffectScale);
    transform.AddToTranslation(InLocation);

    CHelpers::PlayEffect(InWorld, Effect, transform);

}

void FDoActionData::PlayEffect(UWorld* InWorld, const FVector& InLocation, const FRotator& InRotation)
{
    CheckNull(Effect);

    FTransform transform;
    transform.SetLocation(InLocation + InRotation.RotateVector(EffectLocation));
    transform.SetScale3D(EffectScale);

    CHelpers::PlayEffect(InWorld, Effect, transform);

}

void FHitData::SendDamage(ACCharacter* InAttacker, AActor* InAttackCauser, ACCharacter* InOther)
{
    FActionDamageEvent e;
    e.HitData = this;

    InOther->TakeDamage(Power, e, InAttacker->GetController(), InAttackCauser);

}

void FHitData::PlayMontage(ACCharacter* InOwner)
{
    if (!!Montage)
        InOwner->PlayAnimMontage(Montage, PlayRate);

}

void FHitData::PlayHitStop(UWorld* InWorld)
{
    CheckTrue(FMath::IsNearlyZero(StopTime));


    TArray<ACCharacter*> characters;
    for (AActor* actor : InWorld->GetCurrentLevel()->Actors)
    {
        ACCharacter* character = Cast<ACCharacter>(actor);

        if (!!character)
        {
            character->CustomTimeDilation = 1e-3f;

            characters.Add(character);
        }
    }


    FTimerDelegate timerDelegate;
    timerDelegate.BindLambda([=]()
                             {
                                 for (ACCharacter* character : characters)
                                     character->CustomTimeDilation = 1;
                             });

    FTimerHandle timerHandle;
    InWorld->GetTimerManager().SetTimer(timerHandle, timerDelegate, StopTime, false);

}

void FHitData::PlaySoundWave(ACCharacter* InOwner)
{
    CheckNull(Sound);

    UWorld* world = InOwner->GetWorld();
    FVector location = InOwner->GetActorLocation();

    UGameplayStatics::SpawnSoundAtLocation(world, Sound, location);

}

void FHitData::PlayEffect(UWorld* InWorld, const FVector& InLocation)
{
    CheckNull(Effect);

    FTransform transform;
    transform.SetLocation(EffectLocation);
    transform.SetScale3D(EffectScale);
    transform.AddToTranslation(InLocation);

    CHelpers::PlayEffect(InWorld, Effect, transform);

}

void FHitData::PlayEffect(UWorld* InWorld, const FVector& InLocation, const FRotator& InRotation)
{
    CheckNull(Effect);

    FTransform transform;
    transform.SetLocation(InLocation + InRotation.RotateVector(EffectLocation));
    transform.SetScale3D(EffectScale);

    CHelpers::PlayEffect(InWorld, Effect, transform);

}
