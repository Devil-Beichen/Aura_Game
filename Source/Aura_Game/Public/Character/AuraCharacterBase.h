// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * 这是一个游戏角色的基类，用于定义游戏角色的基础属性和方法。
 */
UCLASS(Abstract)
class AURA_GAME_API AAuraCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

	// 获取技能系统组件
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// 获取属性集
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	virtual void BeginPlay() override;

	// 武器
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	// 技能系统组件
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// 属性集
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	// 初始化能力信息
	virtual void InitAbilityActorInfo();
};
