#pragma once

#include "CoreMinimal.h"
#include "Components/CActorComponent.h"
#include "CStatusComponent.generated.h"

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	Crawl = 0, Crouch, Normal, Seat, MAX
};

UCLASS()
class NEWIDENTITYN_API UCStatusComponent : public UCActorComponent
{
	GENERATED_BODY()
	
public:
	UCStatusComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SetCrawl();

private:
	void SetCrawlTime(float InTime);

private:
	UPROPERTY(meta = (AllowPrivateAccess = true))
	EStatusType Type = EStatusType::Normal;

private:
	float CrawlCurrentTime = 0;
	float CrawlMaximumTime = 60;

};
