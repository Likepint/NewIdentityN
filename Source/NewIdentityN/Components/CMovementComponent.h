#pragma once

#include "CoreMinimal.h"
#include "Components/CActorComponent.h"
#include "Components/Interfaces/IBindEnhancedInput.h"
#include "CMovementComponent.generated.h"

UENUM()
enum class ESpeedType : uint8
{
	Crawl = 0, Crouch, Normal, Skill, MAX
};

UCLASS()
class NEWIDENTITYN_API UCMovementComponent
	: public UCActorComponent
	, public IIBindEnhancedInput
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Movement;

	UPROPERTY(VisibleAnywhere, Category = "EnhancedInput")
	class UInputAction* IA_Look;

public:
	FORCEINLINE bool CanMove() { return bMovable; }

	FORCEINLINE float GetCrawlSpeed() { return Speed[(int32)ESpeedType::Crawl]; }
	FORCEINLINE float GetCrouchSpeed() { return Speed[(int32)ESpeedType::Crouch]; }
	FORCEINLINE float GetNormalSpeed() { return Speed[(int32)ESpeedType::Normal]; }
	FORCEINLINE float GetSkillSpeed() { return Speed[(int32)ESpeedType::Skill]; }

	FORCEINLINE bool GetFixedCamera() { return bFixedCamera; }
	FORCEINLINE void EnableFixedCamera() { bFixedCamera = true; }
	FORCEINLINE void DisableFixedCamera() { bFixedCamera = false; }
		
public:
	UCMovementComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	virtual void OnBindEnhancedInput(class UEnhancedInputComponent* InEnhancedInputComponent) override;

private:
	virtual void Init() override;

private:
	void OnMovement(const struct FInputActionValue& InVal);
	void OnLook(const struct FInputActionValue& InVal);

public:
	void SetSpeed(ESpeedType InSpeed);

	void SetCrawlSpeed();
	void SetCrawlSpeed(float InSpeed);

	void SetCrouchSpeed();
	void SetCrouchSpeed(float InSpeed);

	void SetNormalSpeed();
	void SetNormalSpeed(float InSpeed);

	void SetSkillSpeed();
	void SetSkillSpeed(float InSpeed);

	void EnableControlRotation();
	void DisableControlRotation();

	void Move();
	void Stop();

private:
	UPROPERTY()
	float Speed[(int32)ESpeedType::MAX];

private:
	UPROPERTY(EditAnywhere, Category = "CameraSpeed")
	float HorizontalLook = 0.5;

	UPROPERTY(EditAnywhere, Category = "CameraSpeed")
	float VerticalLook = 0.5;

private:
	bool bMovable = true;
	bool bFixedCamera;

};
