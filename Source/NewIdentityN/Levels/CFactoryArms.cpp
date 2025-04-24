#include "Levels/CFactoryArms.h"
#include "Global.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

void ACFactoryArms::BeginPlay()
{
	Super::BeginPlay();

	SelectUI = CreateWidget<UUserWidget>(SelectUI, SelectUIClass, "SelectUI");
	SelectUI->AddToViewport();
	
	if (APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		controller->SetShowMouseCursor(true);

		FInputModeGameAndUI mode;
		mode.SetWidgetToFocus(SelectUI->GetSlateWidgetFromName("SelectUI"));

		controller->SetInputMode(mode);
	}

}
