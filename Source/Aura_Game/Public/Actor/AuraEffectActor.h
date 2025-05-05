// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

// 应用效果的情况
UENUM(BlueprintType)
enum class EEffectApplicationPolicy:uint8
{
	// 应用于重叠的物体
	ApplyOnOverlap,
	// 应用于结束重叠的物体
	ApplyOnEndOverlap,
	// 不应用
	DoNotApply
};

// 移除效果的情况
UENUM(BlueprintType)
enum class EEffectRemovalPolicy:uint8
{
	//结束重叠物体时移除
	RemovalOnEndOverlap,
	// 不移除
	DoNotRemoval
};

/**
 * 产生特殊效果的Actor
 */
UCLASS(Abstract)
class AURA_GAME_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()

public:
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	/**
	 * 应用效果到目标
	 * @param TargetActor			目标 
	 * @param GameplayEffClass		效果类
	 */
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffClass);

	/**
	* 当其他Actor与效果Actor发生重叠时调用
	* 根据EffectApplicationPolicy决定是否应用效果
	* 
	* @param TargetActor 与效果Actor发生重叠的目标Actor
	*/
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	/**
	 * 当其他Actor与效果Actor结束重叠时调用
	* 根据EffectApplicationPolicy决定是否应用效果
	* 根据EffectRemovalPolicy决定是否移除已应用的效果
	* 
	* @param TargetActor 与效果Actor结束重叠的目标Actor
	*/
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	// 是否在效果移除时销毁此Actor
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	uint8 bDestroyOnEffectRemoval : 1;

	// 应用效果到目标的应用方式
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	EEffectApplicationPolicy EffectApplicationPolicy;

	// 移除效果的应用方式
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	EEffectRemovalPolicy EffectRemovalPolicy;

	// 游戏效果类
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;

	// 存储已应用的效果
	UPROPERTY()
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	// 应用效果的等级
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	float ActorLevel = 1.f;

	/*// 一个即时游戏效果
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	// 一个持续游戏效果
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	// 一个无限时间游戏效果
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;*/
};
