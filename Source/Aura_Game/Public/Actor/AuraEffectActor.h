// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;
/**
 * 产生特殊效果的Actor
 */
UCLASS()
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
	void ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffClass) const;

	// 一个即时游戏效果
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Applied Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
};
