#include "Characters/CCharacter.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

ACCharacter::ACCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Init();

}

void ACCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACCharacter::Init()
{
	CHelpers::CreateComponent<USpringArmComponent>(this, &SpringArm, "SpringArm", RootComponent);
	SpringArm->TargetArmLength = 220;
	SpringArm->bEnableCameraLag = true;

	CHelpers::CreateComponent<UCameraComponent>(this, &Camera, "Camera", SpringArm);
	Camera->SetRelativeLocation(FVector(0, 0, 100));

}
