﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/DropItemAbility.h"

#include "Camera/CameraComponent.h"
#include "Character/ShooterCharacter.h"
#include "Objects/WeaponPickup.h"

UDropItemAbility::UDropItemAbility()
{
	Input = EAbilityInput::Drop;

	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::NonInstanced;

	ActivationBlockedTags.AddTag(TAG("Status.State.Dead"));
	ActivationBlockedTags.AddTag(TAG("Status.Debuff.Stunned"));
	ActivationBlockedTags.AddTag(TAG("Status.State.Equipping"));
	ActivationBlockedTags.AddTag(TAG("WeaponState.Firing"));
	ActivationBlockedTags.AddTag(TAG("WeaponState.Reloading"));
}

bool UDropItemAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags) && INVENTORY->GetCurrentWeapon();
}

void UDropItemAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if(!CHARACTER->HasAuthority())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
		return;
	}
	
	const FVector& ForwardVector = CHARACTER->GetViewRotation().Vector();
	const FVector& Location = CHARACTER->GetCamera()->GetComponentLocation() + ForwardVector * DropSpawnOffset;
	const FVector& Impulse = ForwardVector * DropVelocity;
	AWeaponPickup::SpawnWeaponPickup(INVENTORY->GetCurrentWeapon(), Location, Impulse);
	INVENTORY->RemoveItem(INVENTORY->GetCurrentIndex());

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

