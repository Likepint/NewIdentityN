#include "Characters/CCharacter.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Games/CPlayerController.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CStateComponent.h"
#include "Components/CMovementComponent.h"
#include "Components/CWeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ForceNetUpdate();
	Restart();

	Init();

}

void ACCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void ACCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//if (IsLocallyControlled())
	//{
	//	if (ACPlayerController* controller = Cast<ACPlayerController>(GetController()))
	//	{
	//		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
	//		{
	//			subsystem->ClearAllMappings();
	//			subsystem->AddMappingContext(MappingContext, 0);
	//		}
	//	}
	//}

}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (ACPlayerController* controller = Cast<ACPlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(controller->GetLocalPlayer()))
		{
			subsystem->ClearAllMappings();
			subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	
	Movement->DisableControlRotation();

}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("[Input] Bound for: %s (Local: %d)"), *GetName(), IsLocallyControlled());

		// Movement
		Movement->OnBindEnhancedInput(EnhancedInput);
	}

}

void ACCharacter::Init()
{
	// SpringArm
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", RootComponent);
	SpringArm->SetRelativeLocation(FVector(0, 0, 90));
	SpringArm->TargetArmLength = 220;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = true;

	// Camera
	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	Camera->SetRelativeLocation(FVector(~120 + 1, 0, 0));
	Camera->bUsePawnControlRotation = false;

	// Mapping Context
	CHelpers::GetAsset<UInputMappingContext>(&MappingContext, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Inputs/IMC_Default.IMC_Default'"));

	// StateComponent
	CHelpers::CreateActorComponent<UCStateComponent>(this, &State, "State");

	// MovementComponent
	CHelpers::CreateActorComponent<UCMovementComponent>(this, &Movement, "Movement");

	// WeaponComponent
	CHelpers::CreateActorComponent<UCWeaponComponent>(this, &Weapon, "Weapon");

}
