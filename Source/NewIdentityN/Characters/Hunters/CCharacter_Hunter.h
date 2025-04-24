#pragma once

#include "CoreMinimal.h"
#include "Characters/CCharacter.h"
#include "CCharacter_Hunter.generated.h"

USTRUCT(BlueprintType)
struct FHunterCharacteristics : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere)
    FString SkeletalMesh;

    UPROPERTY(VisibleAnywhere)
    FString AnimInstanceClass;

    UPROPERTY(VisibleAnywhere)
    float NormalSpeed;

    UPROPERTY(VisibleAnywhere)
    float SkillSpeed = 1;

    UPROPERTY(VisibleAnywhere)
    float FearRadius;

};

UCLASS()
class NEWIDENTITYN_API ACCharacter_Hunter : public ACCharacter
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
    class USphereComponent* Fear;
	
public:
	ACCharacter_Hunter();

    virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
    void LoadHunterDataFromTable();

protected:
    FHunterCharacteristics* Characteristics;

private:
    UPROPERTY(EditDefaultsOnly, Category = "DataTable")
    class UDataTable* CharacteristicsTable;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Characteristic")
    FName Name;

};
