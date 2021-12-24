﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/LastWeaponAbility.h"

#include "Character/CharacterInventoryComponent.h"
#include "GAS/Abilities/EquipWeaponAbility.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"


ULastWeaponAbility::ULastWeaponAbility()
{
	Input = EAbilityInput::MWheelDown;

	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalOnly;
}


void ULastWeaponAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
/*
	const int32 CurrentIndex = CastChecked<UEquipWeaponAbility>(ActorInfo->AbilitySystemComponent.Get()->FindAbilitySpecFromClass(UEquipWeaponAbility::StaticClass())->Ability)->GetCurrentIndex();
	const TArray<AWeapon*>& Weapons = IInventoryInterface::Execute_GetInventory(ActorInfo->AvatarActor.Get())->GetWeapons();
	const int32 NewIndex = Weapons.IsValidIndex(CurrentIndex - 1) ? CurrentIndex - 1 : Weapons.Num() - 1;
	UEquipWeaponAbility::EquipWeaponEvent(ActorInfo->AbilitySystemComponent.Get(), NewIndex);*/

	const UCharacterInventoryComponent* CharacterInventory = CastChecked<UCharacterInventoryComponent>(IInventoryInterface::Execute_GetInventory(ActorInfo->AvatarActor.Get()));
	const int32 NewIndex = CharacterInventory->GetWeapons().IsValidIndex(CharacterInventory->GetCurrentIndex() - 1) ? CharacterInventory->GetCurrentIndex() - 1 : CharacterInventory->GetWeapons().Num() - 1;
	UEquipWeaponAbility::EquipWeaponEvent(ActorInfo->AbilitySystemComponent.Get(), NewIndex);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

