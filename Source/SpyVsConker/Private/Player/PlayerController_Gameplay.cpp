// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerController_Gameplay.h"
#include "UI/HUDWidget.h"
#include "Blueprint/UserWidget.h"

void APlayerController_Gameplay::CreateHUD()
{
	if (UI_HUDWidget)
		return;

	if (!UI_HUDWidgetClass)
		return;

	if(!IsLocalPlayerController())
		return;

	APlayerStateGameplay* PS = GetPlayerState<APlayerStateGameplay>();
	if(!PS)
		return;

	UI_HUDWidget = CreateWidget<UHUDWidget>(this, UI_HUDWidgetClass);

	//Set Attributes
	UI_HUDWidget->SetCurrentHealth(PS->GetHealth());
	UI_HUDWidget->SetMaxHealth(PS->GetMaxHealth());
	UI_HUDWidget->SetHealthRegenRate(PS->GetHealthRegenRate());

	UI_HUDWidget->AddToViewport();
}

UHUDWidget* APlayerController_Gameplay::GetHUD()
{
	return UI_HUDWidget;
}

void APlayerController_Gameplay::SetRespawnCountdown_Implementation(float RespawnTimeRemaining)
{
	if(UI_HUDWidget)
	{
		UI_HUDWidget->SetRespawnCountDown(RespawnTimeRemaining);
	}
}

bool APlayerController_Gameplay::SetRespawnCountdown_Validate(float RespawnTimeRemaining)
{
	return true;
}

APlayerStateGameplay* APlayerController_Gameplay::GetCurrentPlayerState()
{
	APlayerStateGameplay* PS = GetPlayerState<APlayerStateGameplay>();
	if (!PS)
		return nullptr;
	return PS;
}

//Server Only
void APlayerController_Gameplay::OnPossess(APawn *InPawn)
{
	Super::OnPossess(InPawn);

	
	APlayerStateGameplay* PS = GetPlayerState<APlayerStateGameplay>();
	if (PS)
	{
		// Init ASC with PS (Owner) and our new Pawn (AvatarActor)
		PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, InPawn);
	}
	
}

void APlayerController_Gameplay::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	CreateHUD();
}

void APlayerController_Gameplay::BeginPlay()
{
	Super::BeginPlay();
	
}
