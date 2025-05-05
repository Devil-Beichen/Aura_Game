// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "AbilitySystem/AuraAbilitySystemComponent.h"


UAuraAbilitySystemComponent::UAuraAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAuraAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAuraAbilitySystemComponent::EffectApplied);
}


void UAuraAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAuraAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	GEngine->AddOnScreenDebugMessage(1, 8.f, FColor::Blue, TEXT("Effect Applied"));
}


void UAuraAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
