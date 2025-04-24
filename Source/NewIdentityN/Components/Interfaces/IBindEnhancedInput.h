#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBindEnhancedInput.generated.h"

UINTERFACE(MinimalAPI)
class UIBindEnhancedInput : public UInterface
{
	GENERATED_BODY()
};

class NEWIDENTITYN_API IIBindEnhancedInput
{
	GENERATED_BODY()

public:
	// EnhancedInputComponent 전달 받아 바인딩
	virtual void OnBindEnhancedInput(class UEnhancedInputComponent* InEnhancedInputComponent) = 0;

};
