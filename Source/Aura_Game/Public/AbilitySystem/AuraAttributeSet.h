// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

// 标准属性宏
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// 游戏效果的属性
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties()
	{
	}

	// 游戏效果上下文句柄，包含效果的应用信息
	FGameplayEffectContextHandle EffectContextHandle;

	// 来源方的能力系统组件
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	// 来源方的Avatar角色（玩家控制的角色）
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	// 来源方的控制器（玩家或AI控制器）
	UPROPERTY()
	AController* SourceController = nullptr;

	// 来源方的角色对象
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	// 目标方的能力系统组件
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	// 目标方的Avatar角色（玩家控制的角色）
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	// 目标方的控制器（玩家或AI控制器）
	UPROPERTY()
	AController* TargetController = nullptr;

	// 目标方的角色对象
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};


/**
 * Aura属性集
 */
UCLASS()
class AURA_GAME_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	// 预属性更改
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	// 游戏效果结束后的执行
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;


#pragma region Vital Attributes // 关键属性

	/**
	 * 生命
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Health, Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxHealth, Category="Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth)

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	/**
	 * 魔法
	 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Mana, Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_MaxMana, Category="Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana)

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

#pragma endregion


#pragma region Primary Attributes // 主要属性

	// 力量
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Strength, Category="Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength)
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	// 智力 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Intelligence, Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence)
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	// 韧性
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Resilience, Category="Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience)
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	// 活力
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing= OnRep_Vigor, Category="Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor)
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

#pragma endregion

private:
	/**
	 * 设置游戏效果的属性
	 * @param Data		 游戏玩法效果回调数据
	 * @param Props		 游戏效果的属性
	 */
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
