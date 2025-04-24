#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter.h"
#include "CCharacter_Survivor.generated.h"

UCLASS()
class NEWIDENTITYN_API ACCharacter_Survivor : public ACCharacter
{
	GENERATED_BODY()
	
public:
	ACCharacter_Survivor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
