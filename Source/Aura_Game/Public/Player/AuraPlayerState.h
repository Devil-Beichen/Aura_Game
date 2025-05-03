// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
/**
 * 玩家状态
 */
UCLASS()
class AURA_GAME_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraPlayerState();
	// 获取技能系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// 获取属性集
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	// 技能系统组件
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// 属性集
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
