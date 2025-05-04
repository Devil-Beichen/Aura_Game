// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(AuraAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(AuraAttributeSet->GetMaxMana());
	BindCallbacksToDependencies();
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	if (AbilitySystemComponent)
	{
		// 绑定OnHealthChanged事件
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
		// 绑定OnMaxHealthChanged事件
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
		// 绑定OnManaChanged事件
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
		// 绑定OnMaxManaChanged事件
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UAuraAttributeSet::GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
	}
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	if (Data.OldValue != Data.NewValue)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	}
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	if (Data.OldValue != Data.NewValue)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	}
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	if (Data.OldValue != Data.NewValue)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	}
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	if (Data.OldValue != Data.NewValue)
	{
		OnMaxManaChanged.Broadcast(Data.NewValue);
	}
}
