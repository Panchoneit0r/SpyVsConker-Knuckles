// Fill out your copyright notice in the Description page of Project Settings.


#include "SpyVsConker/Public/Game/CartoonGameModeBase.h"

#include "Player/PlayerController_Gameplay.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Player/PlayerStateGameplay.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/SpectatorPawn.h"

ACartoonGameModeBase::ACartoonGameModeBase() 
{
	RespawnDelay = 5.f;

	PlayerClass = StaticLoadClass(UObject::StaticClass(), nullptr, TEXT("/Game/Blueprints/Characters/BP_OnlineCharacter.BP_OnlineCharacter_C"));
}

ACartoonGameModeBase* ACartoonGameModeBase::Get(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	   if (auto* World = WorldContextObject->GetWorld())
	   {
	   	if (World->WorldType == EWorldType::Editor || World->WorldType == EWorldType::EditorPreview)
	   		if (auto* Settings = World->GetWorldSettings())
	   			return Cast<ACartoonGameModeBase>(Settings->DefaultGameMode.GetDefaultObject());

	   	return Cast<ACartoonGameModeBase>(World->GetAuthGameMode());
	   }

	return nullptr;
}

void ACartoonGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACartoonGameModeBase::PlayerDied(AController* Controller) 
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ASpectatorPawn* SpectatorPawn = GetWorld()->SpawnActor<ASpectatorPawn>(SpectatorClass, Controller->GetPawn()->GetActorTransform(), SpawnParameters);

	Controller->UnPossess();
	Controller->Possess(SpectatorPawn);

	FTimerHandle RespawnTimerHandle;
	FTimerDelegate RespawnDelegate;

	RespawnDelegate = FTimerDelegate::CreateUObject(this, &ACartoonGameModeBase::RespawnPlayer, Controller);
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, RespawnDelegate, RespawnDelay, false);

	APlayerController_Gameplay* PC = Cast<APlayerController_Gameplay>(Controller);
	if (PC)
	{
		PC->SetRespawnCountdown(RespawnDelay);
	}
}

void ACartoonGameModeBase::RespawnPlayer(AController* Controller)
{
	if (Controller->IsPlayerController()) {
		AActor* PlayerStart = FindPlayerStart(Controller);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		ACharacterBase* PlayerCharacter = GetWorld()->SpawnActor<ACharacterBase>(PlayerClass, PlayerStart->GetActorLocation(), PlayerStart->GetActorRotation(), SpawnParams);

		APawn* OldSpectatorPawn = Controller->GetPawn();
		Controller->UnPossess();
		OldSpectatorPawn->Destroy();
		Controller->Possess(PlayerCharacter);
	}
}