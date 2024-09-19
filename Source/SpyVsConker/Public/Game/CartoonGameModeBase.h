// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CartoonGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SPYVSCONKER_API ACartoonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Youswar Global", Meta = (WorldContext = "WorldContextObject", DisplayName = "YousWar Game Mode"))
	static ACartoonGameModeBase* Get(const UObject* WorldContextObject);
	
	virtual void BeginPlay() override;
	
};
