// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterDiedDelegate, ACharacterBase*, Character);

class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SPYVSCONKER_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase(const class FObjectInitializer& ObjectInitializer);

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	
	UCameraComponent* GetFirstPersonCameraComponent() const { return FollowCamera; }
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Character")
	FCharacterDiedDelegate OnCharacterDied;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category="GAS|Character")
	virtual bool IsAlive() const;

	virtual void RemoveCharacterAbilities();

	UFUNCTION(BlueprintCallable, Category = "GAS|Character|Attributes")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "GAS|Character|Attributes")
	float GetMaxHealth() const;

	virtual void Die();

	UFUNCTION(BlueprintCallable, Category = "GAS|Character")
	virtual void FinishDying();

	virtual void PossessedBy(AController* NewController) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<class UAbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<class UBasicAttributeSet> AttributeSetBase;

	FGameplayTag DeadTag;
	FGameplayTag EffectRemoveOnDeathTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GAS|Animation")
	UAnimMontage* DeathMontage;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GAS|Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	virtual void OnRep_PlayerState() override;

	virtual void AddCharacterAbilities();

	virtual void InitializeAttributes();

	virtual void AddStartupEffects();
	
	virtual void SetHealth(float Health);
};
