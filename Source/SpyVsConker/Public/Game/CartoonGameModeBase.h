// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Characters/CharacterBase.h"
#include "CartoonGameModeBase.generated.h"

/**
 * 
 */
UCLASS(minimalapi)
class ACartoonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	ACartoonGameModeBase();

	UFUNCTION(BlueprintPure, Category = "Youswar Global", Meta = (WorldContext = "WorldContextObject", DisplayName = "YousWar Game Mode"))
	static ACartoonGameModeBase* Get(const UObject* WorldContextObject);
	
	virtual void BeginPlay() override;

	void PlayerDied(AController* Controller);

	void RespawnPlayer(AController* Controller);

	//void PossessPlayer(AController* Controller, ACharacterBase* PlayerCharacter);
protected:
	float RespawnDelay;

	TSubclassOf<ACharacterBase> PlayerClass;
};
