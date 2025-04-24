#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CFactoryArms.generated.h"

UCLASS()
class NEWIDENTITYN_API ACFactoryArms : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> SelectUIClass;
	
protected:
	virtual void BeginPlay() override;

private:
	class UUserWidget* SelectUI;

};
