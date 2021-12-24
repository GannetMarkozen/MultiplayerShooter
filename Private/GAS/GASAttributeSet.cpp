﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GASAttributeSet.h"

#include "Net/UnrealNetwork.h"

UGASAttributeSet::UGASAttributeSet()
{
	
}

void UGASAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, MovementSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGASAttributeSet, BulletResistance, COND_None, REPNOTIFY_Always);
}

void UGASAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
/*
	switch(Attribute.GetGameplayAttributeData(this))
	{
		case &Health || &MovementSpeed || &BulletResistance:
			NewValue = FMath::Max<float>(0.f, NewValue);
			break;
		
	}*/
	const FGameplayAttributeData* Data = Attribute.GetGameplayAttributeDataChecked(this);
	if(Data == &Health || Data == &MovementSpeed)
	{
		NewValue = FMath::Max<float>(0.f, NewValue);
	}
	else if(Data == &BulletResistance || Data == &ExplosionResistance)
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.f, 100.f);
	}
}


void UGASAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, Health, OldHealth);
}

void UGASAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, MovementSpeed, OldMovementSpeed);
}

void UGASAttributeSet::OnRep_BulletResistance(const FGameplayAttributeData& OldBulletResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, BulletResistance, OldBulletResistance);
}

void UGASAttributeSet::OnRep_ExplosionResistance(const FGameplayAttributeData& OldExplosionResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGASAttributeSet, ExplosionResistance, OldExplosionResistance);
}


