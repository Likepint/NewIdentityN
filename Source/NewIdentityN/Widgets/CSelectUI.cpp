#include "Widgets/CSelectUI.h"
#include "Global.h"
#include "Components/Button.h"
#include "Games/CPlayerController.h"
#include "Games/CPlayerState.h"

void UCSelectUI::NativeConstruct()
{
	Super::NativeConstruct();

	// Survivor
	Button_Survivor->OnClicked.AddDynamic(this, &UCSelectUI::SelectedSurvivor);

	// Hunter
	Button_Hunter->OnClicked.AddDynamic(this, &UCSelectUI::SelectedHunter);

}

void UCSelectUI::SelectedSurvivor()
{
	if (auto pc = GetOwningPlayer<ACPlayerController>())
		pc->ServerRequestSpawn(EPlayerRole::Survivor);

}

void UCSelectUI::SelectedHunter()
{
	if (auto pc = GetOwningPlayer<ACPlayerController>())
		pc->ServerRequestSpawn(EPlayerRole::Hunter);

}
