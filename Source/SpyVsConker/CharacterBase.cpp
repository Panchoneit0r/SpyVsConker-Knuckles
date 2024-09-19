// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 0.0f, 500.0f);
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	health = maxHealth - 10;
	
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
	
	if (AbilitySystemComponent) 
	{
		BasicAttributeSet = AbilitySystemComponent->GetSet<UBasicAttributeSet>();
	}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::Running()
{
	GetCharacterMovement()->MaxWalkSpeed = runSpeed;
}

void ACharacterBase::Walking()
{
	GetCharacterMovement()->MaxWalkSpeed = walkSpeed;
}

void ACharacterBase::Attack()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Blue,
		FString::Printf(TEXT("vida actual del player: %f"), health)
		);
}

void ACharacterBase::Ability1()
{
	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Blue,
		FString::Printf(TEXT("Vida maxima del player: %f"), maxHealth)
		);
}
