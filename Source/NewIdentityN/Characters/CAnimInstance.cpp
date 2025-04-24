#include "Characters/CAnimInstance.h"
#include "Global.h"

void UCAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    OwnerCharacter = Cast<ACharacter>(GetOwningActor());
    CheckNull(OwnerCharacter);

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    CheckNull(OwnerCharacter);
    Speed = OwnerCharacter->GetVelocity().Size2D();

}
