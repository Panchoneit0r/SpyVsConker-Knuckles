// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpyVsConker/CharacterBase.h"
#include "CartoonPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class SPYVSCONKER_API ACartoonPlayerController : public APlayerController
{
	GENERATED_BODY()

		
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> YouswarMappingContext;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AimingAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> RunAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AttackAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AbilityAction1;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AbilityAction2;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> AbilityAction3;

protected:
	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	
	void StopJumping();
	void Jump();

	void Aiming();
	void StopAiming();

	void Run();
	void RunStop();

	void Attack();
	void StopAttack();

	void Ability1();

	void Ability2();

	void Ability3();

public:
	ACartoonPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	ACharacterBase* CharacterBase;
};
