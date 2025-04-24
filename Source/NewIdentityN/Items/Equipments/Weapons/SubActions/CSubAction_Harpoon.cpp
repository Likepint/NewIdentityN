#include "Items/Equipments/Weapons/SubActions/CSubAction_Harpoon.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Items/Equipments/Weapons/CAttachment.h"
#include "Items/Equipments/Weapons/CDoAction.h"

void UCSubAction_Harpoon::Pressed()
{
    CheckFalse(State->IsDefaultMode());
    CheckTrue(State->IsSubActionMode());

    Super::Pressed();

    State->SetActionMode();
    State->OnChargeActionMode();

    ActionData.DoAction(OwnerCharacter);

}

void UCSubAction_Harpoon::Begin_ChargeAction_Implementation()
{
    Super::Begin_ChargeAction_Implementation();

    Attachment->OnAttachmentBeginOverlap.Remove(DoAction, "OnAttachmentBeginOverlap");
    Attachment->OnAttachmentBeginOverlap.AddDynamic(this, &UCSubAction_Harpoon::OnAttachmentBeginOverlap);

    bMoving = true;

    Start = OwnerCharacter->GetActorLocation();
    End = Start + OwnerCharacter->GetActorForwardVector() * Distance;

    float radius = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();
    float height = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
    FRotator rotation = OwnerCharacter->GetActorRotation();

    TArray<AActor*> ignores;
    ignores.Add(OwnerCharacter);

    TArray<FHitResult> hitResults;
    TArray<TEnumAsByte<EObjectTypeQuery>> objects;
    objects.Add(EObjectTypeQuery::ObjectTypeQuery3);

    UKismetSystemLibrary::BoxTraceMultiForObjects(OwnerCharacter->GetWorld(), Start, End, FVector(0, radius, height), rotation, objects, false, ignores, DrawDebug, hitResults, true);
    for (const FHitResult& hitResult : hitResults)
    {
        ACCharacter* character = Cast<ACCharacter>(hitResult.GetActor());

        if (!!character)
        {
            character->GetCapsuleComponent()->SetCollisionProfileName("Sword_ChargeAction");

            Overlapped.Add(character);
        }
    }

    FHitResult lineHitResult;
    UKismetSystemLibrary::LineTraceSingle(OwnerCharacter->GetWorld(), Start, End, ETraceTypeQuery::TraceTypeQuery1, false, ignores, DrawDebug, lineHitResult, true);

    if (lineHitResult.bBlockingHit)
    {
        FVector direction = (End - Start).GetSafeNormal2D();
        End = lineHitResult.Location - (direction * radius * 2);

        if (DrawDebug == EDrawDebugTrace::ForDuration)
            DrawDebugSphere(OwnerCharacter->GetWorld(), End, radius * 2, 20, FColor::Magenta, true, 2);
    }

    if (DrawDebug == EDrawDebugTrace::ForDuration)
        DrawDebugDirectionalArrow(OwnerCharacter->GetWorld(), Start, End, 25, FColor::Green, true, 5, 0, 3);

}

void UCSubAction_Harpoon::End_ChargeAction_Implementation()
{
    Super::End_ChargeAction_Implementation();

    Attachment->OnAttachmentBeginOverlap.Remove(this, "OnAttachmentBeginOverlap");
    Attachment->OnAttachmentBeginOverlap.AddDynamic(DoAction, &UCDoAction::OnAttachmentBeginOverlap);

    bMoving = false;

    State->SetDefaultMode();
    State->OffChargeActionMode();

    Movement->Move();
    Movement->DisableFixedCamera();

    for (ACCharacter* character : Overlapped)
        character->GetCapsuleComponent()->SetCollisionProfileName("Pawn");

    Overlapped.Empty();
    Hitted.Empty();

}

void UCSubAction_Harpoon::Tick_Implementation(float InDeltaTime)
{
    Super::Tick_Implementation(InDeltaTime);
    CheckFalse(bMoving);

    FVector location = OwnerCharacter->GetActorLocation();
    float radius = OwnerCharacter->GetCapsuleComponent()->GetScaledCapsuleRadius();

    if (location.Equals(End, radius))
    {
        bMoving = false;
        Start = End = OwnerCharacter->GetActorLocation();

        return;
    }

    FVector direction = (End - Start).GetSafeNormal2D();
    OwnerCharacter->AddActorWorldOffset(direction * Speed, true);

}

void UCSubAction_Harpoon::OnAttachmentBeginOverlap(ACCharacter* InAttacker, AActor* InAttackCuaser, ACCharacter* InOther)
{
    CheckNull(InOther);

    for (ACCharacter* character : Hitted)
        CheckTrue(character == InOther);

    Hitted.AddUnique(InOther);

    HitData.SendDamage(OwnerCharacter, InAttackCuaser, InOther);

}
