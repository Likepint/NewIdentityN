#pragma once

#include "CoreMinimal.h"
#include "Characters/Hunters/CCharacter_Hunter.h"
#include "CHunter_Naiad.generated.h"

UCLASS()
class NEWIDENTITYN_API ACHunter_Naiad : public ACCharacter_Hunter
{
	GENERATED_BODY()
	
public:
	ACHunter_Naiad();

	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
