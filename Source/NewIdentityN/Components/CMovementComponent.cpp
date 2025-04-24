#include "Components/CMovementComponent.h"
#include "Global.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Characters/CCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UCMovementComponent::UCMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Init();

}

void UCMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	DisableControlRotation();

}

void UCMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UCMovementComponent::OnBindEnhancedInput(UEnhancedInputComponent* InEnhancedInputComponent)
{
	// Movement
	InEnhancedInputComponent->BindAction(IA_Movement, ETriggerEvent::Triggered, this, &UCMovementComponent::OnMovement);
	
	// Look
	InEnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &UCMovementComponent::OnLook);

}

void UCMovementComponent::Init()
{
	Super::Init();

	// Movement
	CHelpers::GetAsset<UInputAction>(&IA_Movement, TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Movement.IA_Movement'"));

	// Look
	CHelpers::GetAsset<UInputAction>(&IA_Look, TEXT("/Script/EnhancedInput.InputAction'/Game/Inputs/IA_Look.IA_Look'"));

}

void UCMovementComponent::OnMovement(const FInputActionValue& InVal)
{
	CheckFalse(bMovable);

	UE_LOG(LogTemp, Warning, TEXT(">> Move Input Received: %s"), *InVal.ToString());

	// 캐릭터의 정면 방향을 가져오기 위해 컨트롤러의 회전 값을 구해서 Z축만을 사용
	FRotator rot = FRotator(0, OwnerCharacter->GetControlRotation().Yaw, 0);

	// Forward
	OwnerCharacter->AddMovementInput(FQuat(rot).GetForwardVector(), InVal.Get<FVector2D>().X);

	// Right
	OwnerCharacter->AddMovementInput(FQuat(rot).GetRightVector(), InVal.Get<FVector2D>().Y);

}

void UCMovementComponent::OnLook(const FInputActionValue& InVal)
{
	CheckTrue(bFixedCamera);

	// Horizontal
	OwnerCharacter->AddControllerYawInput(InVal.Get<FVector2D>().X * HorizontalLook);

	// Vertical
	OwnerCharacter->AddControllerPitchInput(InVal.Get<FVector2D>().Y * VerticalLook);

}

void UCMovementComponent::SetSpeed(ESpeedType InSpeed)
{
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed[(int32)InSpeed];

}

void UCMovementComponent::SetCrawlSpeed()
{
	SetSpeed(ESpeedType::Crawl);

}

void UCMovementComponent::SetCrawlSpeed(float InSpeed)
{
	Speed[0] = InSpeed;

}

void UCMovementComponent::SetCrouchSpeed()
{
	SetSpeed(ESpeedType::Crouch);

}

void UCMovementComponent::SetCrouchSpeed(float InSpeed)
{
	Speed[1] = InSpeed;

}

void UCMovementComponent::SetNormalSpeed()
{
	SetSpeed(ESpeedType::Normal);

}

void UCMovementComponent::SetNormalSpeed(float InSpeed)
{
	Speed[2] = InSpeed;

}

void UCMovementComponent::SetSkillSpeed()
{
	SetSpeed(ESpeedType::Skill);

}

void UCMovementComponent::SetSkillSpeed(float InSpeed)
{
	Speed[3] = InSpeed;

}

void UCMovementComponent::EnableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = true;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = false;

}

void UCMovementComponent::DisableControlRotation()
{
	OwnerCharacter->bUseControllerRotationYaw = false;
	OwnerCharacter->GetCharacterMovement()->bOrientRotationToMovement = true;

}

void UCMovementComponent::Move()
{
	bMovable = true;

}

void UCMovementComponent::Stop()
{
	bMovable = false;

}
