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
	// 资产标签
	FGameplayTagContainer TagContainer;
	// 获取所有资产标签
	EffectSpec.GetAllAssetTags(TagContainer);

	for (const FGameplayTag& Tag : TagContainer)
	{
		//TODO:Broadcast the tag to Widget Controller 广播标签到Widget控制器
		const FString Msg = FString::Printf(TEXT("GE Tag: %s"), *Tag.ToString());
		GEngine->AddOnScreenDebugMessage(-1, 8.f, FColor::Blue, Msg);
	}
}


void UAuraAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
