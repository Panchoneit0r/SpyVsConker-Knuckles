// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HUDWidget.h"
#include "GameFramework/PlayerController.h"
#include "PlayerController_Gameplay.generated.h"

/**
 * 
 */
UCLASS()
class SPYVSCONKER_API APlayerController_Gameplay : public APlayerController
{
	GENERATED_BODY()

public:
	void CreateHUD();

	UHUDWidget* GetHUD();

	UFUNCTION(Client, Reliable, WithValidation)
	void SetRespawnCountdown(float RespawnTimeRemaining);
	void SetRespawnCountdown_Implementation(float RespawnTimeRemaining);
	bool SetRespawnCountdown_Validate(float RespawnTimeRemaining);

	

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="UI")
	TSubclassOf<UHUDWidget> UI_HUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, Category="UI")
	UHUDWidget* UI_HUDWidget;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void OnRep_PlayerState() override;

	virtual void BeginPlay() override;
};
