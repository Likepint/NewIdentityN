﻿#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CSubAction.generated.h"

UCLASS()
class NEWIDENTITYN_API UCSubAction : public UObject
{
	GENERATED_BODY()

public:
    FORCEINLINE bool GetInAction() { return bInAction; }

public:
    UCSubAction();

public:
    virtual void BeginPlay(class ACCharacter* InOwner, class ACAttachment* InAttachment, class UCDoAction* InDoAction);

public:
    virtual void Pressed();
    virtual void Released();

public:
    UFUNCTION(BlueprintNativeEvent)
    void Begin_ChargeAction();
    virtual void Begin_ChargeAction_Implementation() {}

    UFUNCTION(BlueprintNativeEvent)
    void End_ChargeAction();
    virtual void End_ChargeAction_Implementation() {}

    UFUNCTION(BlueprintNativeEvent)
    void Tick(float InDeltaTime);
    virtual void Tick_Implementation(float InDeltaTime) {}

protected:
    bool bInAction;

    class ACCharacter* OwnerCharacter;
    class ACAttachment* Attachment;
    class UCDoAction* DoAction;

    class UCStateComponent* State;
    class UCMovementComponent* Movement;
	
};
