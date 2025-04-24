#include "Components/CStateComponent.h"
#include "Global.h"

UCStateComponent::UCStateComponent()
{
    PrimaryComponentTick.bCanEverTick = true;

}

void UCStateComponent::BeginPlay()
{
    Super::BeginPlay();
    CheckNull(OwnerCharacter);

}

void UCStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCStateComponent::SetDefaultMode()
{
    ChangeType(EStateType::Default);

}

void UCStateComponent::SetEquipMode()
{
    ChangeType(EStateType::Equip);

}

void UCStateComponent::SetActionMode()
{
    ChangeType(EStateType::Action);

}

void UCStateComponent::SetDamagedMode()
{
    ChangeType(EStateType::Damaged);

}

void UCStateComponent::OnChargeActionMode()
{
    bInSubActionMode = true;

}

void UCStateComponent::OffChargeActionMode()
{
    bInSubActionMode = false;

}

void UCStateComponent::ChangeType(EStateType InType)
{
    EStateType prevType = Type;
    Type = InType;

    if (OnStateTypeChanged.IsBound())
        OnStateTypeChanged.Broadcast(prevType, Type);

}
