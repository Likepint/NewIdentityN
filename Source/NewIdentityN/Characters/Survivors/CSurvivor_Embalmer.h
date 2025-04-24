#pragma once

#include "CoreMinimal.h"
#include "Characters/Survivors/CCharacter_Survivor.h"
#include "CSurvivor_Embalmer.generated.h"

UCLASS()
class NEWIDENTITYN_API ACSurvivor_Embalmer : public ACCharacter_Survivor
{
	GENERATED_BODY()
	
public:
	ACSurvivor_Embalmer();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
