// Fill out your copyright notice in the Description page of Project Settings.


#include "SpyVsConker/Public/Game/CartoonGameModeBase.h"

ACartoonGameModeBase* ACartoonGameModeBase::Get(const UObject* WorldContextObject)
{
	if (WorldContextObject)
	   if (auto* World = WorldContextObject->GetWorld())
	   {
	   	if (World->WorldType == EWorldType::Editor || World->WorldType == EWorldType::EditorPreview)
	   		if (auto* Settings = World->GetWorldSettings())
	   			return Cast<ACartoonGameModeBase>(Settings->DefaultGameMode.GetDefaultObject());

	   	return Cast<ACartoonGameModeBase>(World->GetAuthGameMode());
	   }

	return nullptr;
}

void ACartoonGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}
