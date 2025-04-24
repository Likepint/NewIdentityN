#include "Components/CActorComponent.h"
#include "Global.h"
#include "Characters/CCharacter.h"

UCActorComponent::UCActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCActorComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACCharacter>(GetOwner());

}

void UCActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}
