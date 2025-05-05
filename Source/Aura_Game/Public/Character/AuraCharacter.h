// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 这是一个游戏角色的基类，继承自 AAuraCharacterBase
 */
UCLASS()
class AURA_GAME_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

	// 当玩家被控制时，调用此函数
	virtual void PossessedBy(AController* NewController) override;
	// 当玩家状态被重置时，调用此函数
	virtual void OnRep_PlayerState() override;

private:
	// 初始化能力信息
	virtual void InitAbilityActorInfo() override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
