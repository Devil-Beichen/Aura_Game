// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AuraWidgetController.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
/**
 * 用户界面控制器的基类，用于管理游戏界面的逻辑和数据。
 */
UCLASS()
class AURA_GAME_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

protected:
	
	// 玩家控制器引用，用于处理玩家输入和界面交互
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	// 玩家状态引用，包含玩家等级、经验等游戏状态信息
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	// 能力系统组件，用于管理游戏中的技能和效果
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// 属性集，包含角色的各项属性数据(如生命值、法力值等)
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

};
