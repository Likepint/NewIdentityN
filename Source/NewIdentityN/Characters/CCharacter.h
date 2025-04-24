#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

UCLASS()
class NEWIDENTITYN_API ACCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

protected:
	UPROPERTY(VisibleAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* MappingContext;
	
protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCStateComponent* State;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCMovementComponent* Movement;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	class UCWeaponComponent* Weapon;

public:
	ACCharacter();

	virtual void PostInitializeComponents() override;

	virtual void PossessedBy(AController* NewController) override;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	virtual void Init();

};
