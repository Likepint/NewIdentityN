#include "Characters/Hunters/CCharacter_Hunter.h"
#include "Global.h"
#include "Components/SphereComponent.h"
#include "Characters/CAnimInstance.h"
#include "Components/CMovementComponent.h"

ACCharacter_Hunter::ACCharacter_Hunter()
{
	PrimaryActorTick.bCanEverTick = true;

    // Capsule
    GetCapsuleComponent()->SetRelativeScale3D(FVector(1.3));

    // Mesh
    GetMesh()->SetRelativeLocation(FVector(0, 0, ~110 + 1));
    GetMesh()->SetRelativeRotation(FQuat(FRotator(0, 270, 0)));
    GetMesh()->SetRelativeScale3D(FVector(3));

	CHelpers::CreateComponent<USphereComponent>(this, &Fear, "Fear", RootComponent);
	Fear->OnComponentBeginOverlap.AddDynamic(this, &ACCharacter_Hunter::OnComponentBeginOverlap);

    CHelpers::GetAsset<UDataTable>(&CharacteristicsTable, TEXT("/Script/Engine.DataTable'/Game/Characters/DataTables/HunterCharacteristics.HunterCharacteristics'"));

}

void ACCharacter_Hunter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	LoadHunterDataFromTable();

}

void ACCharacter_Hunter::BeginPlay()
{
	Super::BeginPlay();

}

void ACCharacter_Hunter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACCharacter_Hunter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACCharacter_Hunter::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ACCharacter_Hunter::LoadHunterDataFromTable()
{
    CheckNull(CharacteristicsTable);
    Characteristics = CharacteristicsTable->FindRow<FHunterCharacteristics>(Name, TEXT("Hunter Init"));

    CheckNull(Characteristics);

    // SkeletalMesh
    if (USkeletalMesh* mesh = LoadObject<USkeletalMesh>(nullptr, *Characteristics->SkeletalMesh))
        GetMesh()->SetSkeletalMesh(mesh);

    // AnimInstance
    if (UClass* anim = Cast<UClass>(StaticLoadClass(UCAnimInstance::StaticClass(), nullptr, *Characteristics->AnimInstanceClass)))
        GetMesh()->SetAnimClass(anim);

    CheckNull(Movement);
    Movement->SetNormalSpeed(Characteristics->NormalSpeed);
    Movement->SetSkillSpeed(Characteristics->SkillSpeed);

    Fear->SetSphereRadius(Characteristics->FearRadius);

}
