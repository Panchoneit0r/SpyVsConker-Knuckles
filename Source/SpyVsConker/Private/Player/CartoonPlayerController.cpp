// Fill out your copyright notice in the Description page of Project Settings.


#include "SpyVsConker/Public/Player/CartoonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

ACartoonPlayerController::ACartoonPlayerController()
{
	bReplicates = true;
}

void ACartoonPlayerController::BeginPlay()
{
	Super::BeginPlay();

	CharacterBase = GetPawn<ACharacterBase>();
	
	check(YouswarMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(YouswarMappingContext, 0);
}

void ACartoonPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	//Moving
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	// Looking
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	//Jump
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);

	//Aiming
	EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Started, this, &ThisClass::Aiming);
	EnhancedInputComponent->BindAction(AimingAction, ETriggerEvent::Completed, this, &ThisClass::StopAiming);

	//Run
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started, this, &ThisClass::Run);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &ThisClass::RunStop);

	//Attack
	EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ThisClass::Attack);

	//Abilities
	EnhancedInputComponent->BindAction(AbilityAction1, ETriggerEvent::Started, this, &ThisClass::Ability1);
	EnhancedInputComponent->BindAction(AbilityAction2, ETriggerEvent::Started, this, &ThisClass::Ability2);
	EnhancedInputComponent->BindAction(AbilityAction3, ETriggerEvent::Started, this, &ThisClass::Ability3);
}

void ACartoonPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ACartoonPlayerController::Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

void ACartoonPlayerController::StopJumping()
{
	if(!CharacterBase) return;
	CharacterBase->ACharacter::StopJumping();
}

void ACartoonPlayerController::Jump()
{
	if(!CharacterBase) return;
	CharacterBase->ACharacter::Jump();
}

void ACartoonPlayerController::Aiming()
{
	if(!CharacterBase) return;
}

void ACartoonPlayerController::StopAiming()
{
	if(!CharacterBase) return;
}

void ACartoonPlayerController::Run()
{
	if(!CharacterBase) return;
	CharacterBase->Running();
}

void ACartoonPlayerController::RunStop()
{
	if(!CharacterBase) return;
	CharacterBase->Walking();
}

void ACartoonPlayerController::Attack()
{
	if(!CharacterBase) return;
	CharacterBase->Attack();
}

void ACartoonPlayerController::StopAttack()
{
	if(!CharacterBase) return;
}

void ACartoonPlayerController::Ability1()
{
	if(!CharacterBase) return;
	CharacterBase->Ability1();
}

void ACartoonPlayerController::Ability2()
{
	if(!CharacterBase) return;
}

void ACartoonPlayerController::Ability3()
{
	if(!CharacterBase) return;
}