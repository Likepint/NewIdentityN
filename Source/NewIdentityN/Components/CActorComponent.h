#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CActorComponent.generated.h"

UCLASS( ClassGroup=(Custom) )
class NEWIDENTITYN_API UCActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCActorComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY()
	class ACCharacter* OwnerCharacter;

protected:
	virtual void Init() {};

};
