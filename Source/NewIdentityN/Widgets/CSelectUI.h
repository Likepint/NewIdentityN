#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CSelectUI.generated.h"

UCLASS()
class NEWIDENTITYN_API UCSelectUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Survivor;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UButton* Button_Hunter;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void SelectedSurvivor();

	UFUNCTION()
	void SelectedHunter();
	
};
