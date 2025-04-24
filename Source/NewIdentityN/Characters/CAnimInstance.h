#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class NEWIDENTITYN_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    UPROPERTY(VisibleAnywhere)
    class ACharacter* OwnerCharacter = nullptr;

protected:
    UPROPERTY(BlueprintReadOnly)
    float Speed;

};
