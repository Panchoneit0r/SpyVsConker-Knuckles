// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "BasicAttributeSet.h"
#include "CharacterBase.generated.h"

class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SPYVSCONKER_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta=(AllowPrivateAccess))
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="GAS", meta=(AllowPrivateAcces="true"))
	const class UBasicAttributeSet* BasicAttributeSet;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FollowCamera; }

private:

	UPROPERTY(EditAnywhere, Category="Stats")
	float walkSpeed;

	UPROPERTY(EditAnywhere, Category="Stats")
	float runSpeed;

	UPROPERTY(EditAnywhere, Category="Stats")
	float health;

	UPROPERTY(EditAnywhere, Category="Stats")
	float maxHealth;

public:
	
	void Running();

	void Walking();

	void Attack();

	void Ability1();
};
