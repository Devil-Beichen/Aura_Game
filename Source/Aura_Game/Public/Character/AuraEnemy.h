// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 这是一个敌人角色的基类，继承自 AAuraCharacterBase
 */
UCLASS()
class AURA_GAME_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

protected:
	virtual void BeginPlay() override;

public:
	// 高亮显示
	virtual void HighLightActor() override;
	// 取消高亮显示
	virtual void UnHighLightActor() override;

protected:
	// 初始化能力组件
	virtual void InitAbilityActorInfo() override;
};
