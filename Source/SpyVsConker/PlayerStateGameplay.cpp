// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateGameplay.h"
#include "CharacterBase.h"
#include "HUDWidget.h"
#include "PlayerController_Gameplay.h"

APlayerStateGameplay::APlayerStateGameplay()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSetBase = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("AttributeSetBase"));
	NetUpdateFrequency  = 100.f;
}

UAbilitySystemComponent* APlayerStateGameplay::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UBasicAttributeSet* APlayerStateGameplay::GetAttributeSetBase() const
{
	return AttributeSetBase;
}

bool APlayerStateGameplay::IsAlive() const
{
	return GetHealth() > 0.0f;
}

float APlayerStateGameplay::GetHealth() const
{
	return AttributeSetBase->GetHealth();
}

float APlayerStateGameplay::GetMaxHealth() const
{
	return AttributeSetBase->GetMaxHealth();
}

float APlayerStateGameplay::GetHealthRegenRate() const
{
	return AttributeSetBase->GetHealthRegenRate();
}

void APlayerStateGameplay::BeginPlay()
{
	Super::BeginPlay();

	if(AbilitySystemComponent)
	{
		HealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthAttribute()).AddUObject(this, &APlayerStateGameplay::HealthChanged);
		MaxHealthChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetMaxHealthAttribute()).AddUObject(this, &APlayerStateGameplay::MaxHealthChanged);
		HealthRegenRateChangedDelegateHandle = AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSetBase->GetHealthRegenRateAttribute()).AddUObject(this, &APlayerStateGameplay::HealthRegenRate);
	}
}

void APlayerStateGameplay::HealthChanged(const FOnAttributeChangeData& Data)
{
	float Health = Data.NewValue;

	ACharacterBase* Char = Cast<ACharacterBase>(GetPawn());
	if(!IsAlive() && !AbilitySystemComponent->HasMatchingGameplayTag(DeadTag))
	{
		if(Char)
		{
			Char->Die();
		}
	}
}

void APlayerStateGameplay::MaxHealthChanged(const FOnAttributeChangeData& Data)
{
	float MaxHealth = Data.NewValue;

	APlayerController_Gameplay* PC = Cast<APlayerController_Gameplay>(GetOwner());
	if(PC)
	{
		UHUDWidget* HUD = PC->GetHUD();
		if(HUD)
		{
			HUD->SetMaxHealth(MaxHealth);
		}
	}
}

void APlayerStateGameplay::HealthRegenRate(const FOnAttributeChangeData& Data)
{
	float HealthRegenRate = Data.NewValue;

	APlayerController_Gameplay* PC = Cast<APlayerController_Gameplay>(GetOwner());
	if(PC)
	{
		UHUDWidget* HUD = PC->GetHUD();
		if(HUD)
		{
			HUD->SetHealthRegenRate(HealthRegenRate);
		}
	}
}
