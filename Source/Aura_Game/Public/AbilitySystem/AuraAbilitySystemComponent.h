// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

// 声明多播代理（一个参数）
DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&/*AssetTags*/)

/**
 *	艾拉的AbilitySystemComponent
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class AURA_GAME_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UAuraAbilitySystemComponent();

	// Actor的GAS能力成化设置
	void AbilityActorInfoSet();

	
	FEffectAssetTags EffectAssetTags;

protected:
	virtual void BeginPlay() override;

	/**
	 * 当GameplayEffect被成功应用到目标时调用的回调函数
	 * @param AbilitySystemComponent 应用效果的能力系统组件(可能是来源或目标)
	 * @param EffectSpec 包含效果详细信息的规格(如修饰符、持续时间等)
	 * @param ActiveEffectHandle 新创建的活动效果句柄，可用于后续管理效果(如移除效果)
	 * 
	 * 使用场景：
	 * - 监听并响应效果应用事件
	 * - 记录效果日志或调试信息
	 * - 触发视觉效果或音效
	 * - 实现自定义的效果应用逻辑
	 */
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
