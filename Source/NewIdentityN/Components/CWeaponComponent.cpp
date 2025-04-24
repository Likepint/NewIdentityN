#include "Components/CWeaponComponent.h"
#include "Global.h"
#include "Characters/CCharacter.h"
#include "Components/CStateComponent.h"
#include "Items/Equipments/Weapons/CWeaponAsset.h"
#include "Items/Equipments/Weapons/CWeaponData.h"
#include "Items/Equipments/Weapons/CAttachment.h"
#include "Items/Equipments/Weapons/CEquipment.h"
#include "Items/Equipments/Weapons/CDoAction.h"
#include "Items/Equipments/Weapons/CSubAction.h"
#include "Items/Equipments/Weapons/Skills/CSkill.h"
#include "Items/Equipments/Weapons/AddOns/CObject_SpearFishing.h"
#include "Engine/OverlapResult.h"
#include "Characters/Survivors/CCharacter_Survivor.h"
#include "Characters/Hunters/CCharacter_Hunter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Net/UnrealNetwork.h"

UCWeaponComponent::UCWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

    CHelpers::GetAsset<UInputAction>(&IA_Action, TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Action.IA_Action'"));
    CHelpers::GetAsset<UInputAction>(&IA_Skill, TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Skill.IA_Skill'"));
    CHelpers::GetAsset<UInputAction>(&IA_Capture, TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Capture.IA_Capture'"));
    CHelpers::GetAsset<UInputAction>(&IA_Telport, TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Teleport.IA_Teleport'"));

    CHelpers::GetAsset<UCWeaponAsset>(&DataAssets[0], TEXT("/Script/NewIdentityN.CWeaponAsset'/Game/Items/Equipments/Weapons/Harpoon/DA_Harpoon.DA_Harpoon'"));

}

void UCWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    for (int32 i = 0; i < (int32)EWeaponType::MAX; i++)
    {
        if (!!DataAssets[i])
            DataAssets[i]->BeginPlay(OwnerCharacter, &Datas[i]);
    }

    SetHarpoonMode();

}

void UCWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!!GetDoAction())
        GetDoAction()->Tick(DeltaTime);

    if (!!GetSubAction())
        GetSubAction()->Tick(DeltaTime);

    if (Candidate)
        Candidate->SetActorLocation(GetOwner()->GetActorLocation() + GetOwner()->GetActorUpVector() * 200);

}

void UCWeaponComponent::OnBindEnhancedInput(UEnhancedInputComponent* InEnhancedInput)
{
    InEnhancedInput->BindAction(IA_Action, ETriggerEvent::Triggered, this, &UCWeaponComponent::OnSelectAction);
    InEnhancedInput->BindAction(IA_Action, ETriggerEvent::Completed, this, &UCWeaponComponent::OnInitAction);

    InEnhancedInput->BindAction(IA_Skill, ETriggerEvent::Started, this, &UCWeaponComponent::OnChargingSkill);
    InEnhancedInput->BindAction(IA_Skill, ETriggerEvent::Completed, this, &UCWeaponComponent::OnShootSkill);

    InEnhancedInput->BindAction(IA_Capture, ETriggerEvent::Completed, this, &UCWeaponComponent::OnCapture);

    InEnhancedInput->BindAction(IA_Telport, ETriggerEvent::Completed, this, &UCWeaponComponent::OnTeleport);

}

bool UCWeaponComponent::IsDefaultMode()
{
    return CHelpers::GetComponent<UCStateComponent>(OwnerCharacter)->IsDefaultMode();

}

ACAttachment* UCWeaponComponent::GetAttachment()
{
    CheckTrueResult(IsUnarmedMode(), nullptr);
    CheckFalseResult(!!Datas[(int32)Type], nullptr);

    return Datas[(int32)Type]->GetAttachment();

}

UCEquipment* UCWeaponComponent::GetEquipment()
{
    CheckTrueResult(IsUnarmedMode(), nullptr);
    CheckFalseResult(!!Datas[(int32)Type], nullptr);

    return Datas[(int32)Type]->GetEquipment();

}

UCDoAction* UCWeaponComponent::GetDoAction()
{
    CheckTrueResult(IsUnarmedMode(), nullptr);
    CheckFalseResult(!!Datas[(int32)Type], nullptr);

    return Datas[(int32)Type]->GetDoAction();

}

UCSkill* UCWeaponComponent::GetSkill()
{
    CheckTrueResult(IsUnarmedMode(), nullptr);
    CheckFalseResult(!!Datas[(int32)Type], nullptr);

    return Datas[(int32)Type]->GetSkill();
}

UCSubAction* UCWeaponComponent::GetSubAction()
{
    CheckTrueResult(IsUnarmedMode(), nullptr);
    CheckFalseResult(!!Datas[(int32)Type], nullptr);

    return Datas[(int32)Type]->GetSubAction();

}

void UCWeaponComponent::SetUnarmedMode()
{
    GetEquipment()->Unequip();

    ChangeType(EWeaponType::MAX);

}

void UCWeaponComponent::SetHarpoonMode()
{
    CheckFalse(IsDefaultMode());

    SetMode(EWeaponType::Harpoon);

}

void UCWeaponComponent::DoAction(const struct FInputActionValue& InVal)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        ServerRPC_DoAction();

        return;
    }

    if (!!GetDoAction())
        GetDoAction()->DoAction();

}

void UCWeaponComponent::ServerRPC_DoAction_Implementation()
{
    MulticastRPC_DoAction();

}

void UCWeaponComponent::MulticastRPC_DoAction_Implementation()
{
    if (!!GetDoAction())
        GetDoAction()->DoAction();

}

void UCWeaponComponent::SubAction_Pressed()
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        ServerRPC_SubAction_Pressed();

        return;
    }

    if (!!GetSubAction())
        GetSubAction()->Pressed();

}

void UCWeaponComponent::ServerRPC_SubAction_Pressed_Implementation()
{
    MulticastRPC_SubAction_Pressed();

}

void UCWeaponComponent::MulticastRPC_SubAction_Pressed_Implementation()
{
    if (!!GetSubAction())
        GetSubAction()->Pressed();

}

void UCWeaponComponent::SubAction_Released()
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        ServerRPC_SubAction_Released();

        return;
    }

    if (!!GetSubAction())
        GetSubAction()->Released();

}

void UCWeaponComponent::ServerRPC_SubAction_Released_Implementation()
{
    MulticastRPC_SubAction_Released();

}

void UCWeaponComponent::MulticastRPC_SubAction_Released_Implementation()
{
    if (!!GetSubAction())
        GetSubAction()->Released();

}

void UCWeaponComponent::OnChargingSkill(const FInputActionValue& InVal)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        ServerRPC_OnChargingSkill();

        return;
    }

    if (bCanSkill)
    {
        if (!!GetSkill())
            GetSkill()->Pressed();

        bCanSkill = false;

        bUsedSkill = true;
    }
    else
    {
        if (ACObject_SpearFishing* object = CHelpers::FindActor<ACObject_SpearFishing>(GetWorld()))
            object->Return(GetOwner()->GetActorLocation());
    }

}

void UCWeaponComponent::ServerRPC_OnChargingSkill_Implementation()
{
    MulticastRPC_OnChargingSkill();

}

void UCWeaponComponent::MulticastRPC_OnChargingSkill_Implementation()
{
    if (bCanSkill)
    {
        if (!!GetSkill())
            GetSkill()->Pressed();

        bCanSkill = false;

        bUsedSkill = true;
    }
    else
    {
        if (ACObject_SpearFishing* object = CHelpers::FindActor<ACObject_SpearFishing>(GetWorld()))
            object->Return(GetOwner()->GetActorLocation());
    }

}

void UCWeaponComponent::OnShootSkill(const FInputActionValue& InVal)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        ServerRPC_OnShootSkill();

        return;
    }

    if (!bCanSkill)
    {
        if (!!GetSkill())
            GetSkill()->Released();

        //GetAttachment()->SetActorHiddenInGame(bUsedSkill);
    }

}

void UCWeaponComponent::ServerRPC_OnShootSkill_Implementation()
{
    MulticastRPC_OnShootSkill();

}

void UCWeaponComponent::MulticastRPC_OnShootSkill_Implementation()
{
    if (!bCanSkill)
    {
        if (!!GetSkill())
            GetSkill()->Released();

        //GetAttachment()->SetActorHiddenInGame(bUsedSkill);
    }

}

void UCWeaponComponent::OnTeleport(const FInputActionValue& InVal)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        ServerRPC_OnTeleport();

        return;
    }

    //(X=1883.000000,Y=-819.000000,Z=155.000000)
    //GetOwner()->SetActorLocation();

    FTransform transform;
    transform.SetLocation(FVector(1700, -819, GetOwner()->GetActorLocation().Z));
    transform.SetRotation(FQuat(GetOwner()->GetActorRotation()));
    transform.SetScale3D(GetOwner()->GetActorScale3D());

    GetOwner()->SetActorTransform(transform);

}

void UCWeaponComponent::ServerRPC_OnTeleport_Implementation()
{
    MulticastRPC_OnTeleport();

}

void UCWeaponComponent::MulticastRPC_OnTeleport_Implementation()
{
    //(X=1883.000000,Y=-819.000000,Z=155.000000)
    //GetOwner()->SetActorLocation();

    FTransform transform;
    transform.SetLocation(FVector(1700, -819, GetOwner()->GetActorLocation().Z));
    transform.SetRotation(FQuat(GetOwner()->GetActorRotation()));
    transform.SetScale3D(GetOwner()->GetActorScale3D());

    GetOwner()->SetActorTransform(transform);

}

void UCWeaponComponent::OnCapture(const FInputActionValue& InVal)
{
    if (GetOwnerRole() < ROLE_Authority)
    {
        ServerRPC_OnCapture();

        return;
    }

    if (Candidate)
    {
        Candidate->SetActorLocation(GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 150);
        ACCharacter_Survivor* survivor = Cast<ACCharacter_Survivor>(Candidate);
        //survivor->ReleaseBallooned();
        Candidate = nullptr;

        return;
    }

    constexpr float radius = 50.0f;

    // 감시자 위치
    FVector location = GetOwner()->GetActorLocation();

    // 캡처 대상
    ACharacter* target = nullptr;

    // 구체 범위 내 오버랩된 액터 수집
    // #include "Engine/OverlapResult.h" 헤더 필요
    TArray<FOverlapResult> results;
    FCollisionQueryParams params;
    params.AddIgnoredActor(GetOwner());

    bool bHit = GetWorld()->OverlapMultiByObjectType(
        results,
        location,
        FQuat::Identity,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn),
        FCollisionShape::MakeSphere(radius),
        params
    );

    CheckFalse(bHit);

    // HP가 0인 생존자 탐색
    //for (auto& result : results)
    //{
    //    ACCharacter_Survivor* candidate = Cast<ACCharacter_Survivor>(result.GetActor());
    //    if (!candidate or candidate == GetOwner())
    //        continue;

    //    // TODO: 체력 확인
    //    if (candidate->bCrawl)
    //    {
    //        Candidate = candidate;

    //        candidate->CatchBallooned(Cast<ACCharacter_Hunter>(GetOwner()));

    //        break;
    //    }
    //}

}

void UCWeaponComponent::ServerRPC_OnCapture_Implementation()
{
    MulticastRPC_OnCapture();

}

void UCWeaponComponent::MulticastRPC_OnCapture_Implementation()
{


}

void UCWeaponComponent::OnSubAction(const FInputActionValue& InVal)
{
    SubAction_Pressed();

}

void UCWeaponComponent::OffSubAction(const FInputActionValue& InVal)
{
    SubAction_Released();

}

void UCWeaponComponent::OnSelectAction(const FInputActionValue& InVal)
{
    ChargeTime += GetWorld()->GetDeltaSeconds();

}

void UCWeaponComponent::OnInitAction(const FInputActionValue& InVal)
{
    if (ChargeTime >= 1)
    {
        ChargeTime = 0;

        OnSubAction(FInputActionValue());
        OffSubAction(FInputActionValue());
    }
    else DoAction(FInputActionValue());

}

void UCWeaponComponent::SetMode(EWeaponType InType)
{
    if (Type == InType)
    {
        SetUnarmedMode();

        return;
    }
    else if (IsUnarmedMode() == false)
    {
        GetEquipment()->Unequip();
    }

    if (!!Datas[(int32)InType])
    {
        Datas[(int32)InType]->GetEquipment()->Equip();

        ChangeType(InType);
    }

}

void UCWeaponComponent::ChangeType(EWeaponType InType)
{
    EWeaponType prevType = Type;
    Type = InType;

    if (OnWeaponTypeChange.IsBound())
        OnWeaponTypeChange.Broadcast(prevType, InType);

}

void UCWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UCWeaponComponent, bCanSkill);

    DOREPLIFETIME(UCWeaponComponent, bUsedSkill);

}
