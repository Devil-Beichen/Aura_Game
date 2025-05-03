// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

/**
 * 玩家状态
 */
UCLASS()
class AURA_GAME_API AAuraPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
};
