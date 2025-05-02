// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBase.generated.h"

/**
 * 这是一个游戏角色的基类，用于定义游戏角色的基础属性和方法。
 */
UCLASS(Abstract)
class AURA_GAME_API AAuraCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBase();

protected:
	virtual void BeginPlay() override;

	// 武器
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
