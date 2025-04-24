#include "Components/CStatusComponent.h"
#include "Global.h"
#include "Characters/CCharacter.h"

UCStatusComponent::UCStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCStatusComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UCStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (Type)
	{
	case EStatusType::Crawl:
	{
		SetCrawlTime(DeltaTime);

		break;
	}
	case EStatusType::Crouch:
		break;
	case EStatusType::Normal:
		break;
	case EStatusType::Seat:
		break;
	}

}

void UCStatusComponent::SetCrawl()
{
	Type = EStatusType::Crawl;

}

void UCStatusComponent::SetCrawlTime(float InTime)
{
	CrawlCurrentTime += InTime;

	if (CrawlCurrentTime < CrawlMaximumTime) return;



}
