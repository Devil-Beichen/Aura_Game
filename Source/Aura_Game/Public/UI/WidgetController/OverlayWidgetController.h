// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
// 创建一个动态多播委托复制监听属性发生改变
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

/**
 * OverlayWidget的控制器
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_GAME_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	// 广播初始值
	virtual void BroadcastInitialValues() override;
	// 绑定属性监听
	virtual void BindCallbacksToDependencies() override;

	/**
	 * 血量值监听
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	/**
	 * 魔法值监听
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

protected:
	// 监听当前血量
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	// 监听最大血量
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	// 监听当前魔法值
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	// 监听最大魔法值
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
