// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "Characters/AttributeSets/BasicAttributeSet.h"
#include "PlayerStateGameplay.generated.h"

/**
 * 
 */
UCLASS()
class SPYVSCONKER_API APlayerStateGameplay : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerStateGameplay();

	UPROPERTY(VisibleAnywhere);
	bool bInitializedAttributes;

	UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UBasicAttributeSet* GetAttributeSetBase() const;

	UFUNCTION(BlueprintCallable, Category = "GAS")
	bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "GAS")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS")
	float GetHealthRegenRate() const;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	UBasicAttributeSet* AttributeSetBase;

	FGameplayTag DeadTag;

	FDelegateHandle HealthChangedDelegateHandle;
	FDelegateHandle MaxHealthChangedDelegateHandle;
	FDelegateHandle HealthRegenRateChangedDelegateHandle;

	virtual void BeginPlay() override;

	virtual void HealthChanged(const FOnAttributeChangeData& Data);
	virtual void MaxHealthChanged(const FOnAttributeChangeData& Data);
	virtual void HealthRegenRate(const FOnAttributeChangeData& Data);
};
