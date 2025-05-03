// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 敌人接口
 * 所有敌人都需要实现这个接口
 * 敌人的行为都需要实现这个接口
 */
class AURA_GAME_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 高亮敌人
	virtual void HighLightActor() = 0;
	// 取消高亮
	virtual void UnHighLightActor() = 0;
};
