// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;
/**
 * 玩家控制器
 */
UCLASS()
class AURA_GAME_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();

	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputMappingContext> AuraContext;

	// 移动动作
	UPROPERTY(EditDefaultsOnly, Category=Input)
	TObjectPtr<UInputAction> MoveAction;

	// 移动
	UFUNCTION()
	void Move(const FInputActionValue& InputActionValue);

	// 鼠标追踪
	void CursorTrace();

	// 上一帧鼠标悬停的敌人接口指针
	IEnemyInterface* LastActor;
	// 当前帧鼠标悬停的敌人接口指针
	IEnemyInterface* ThisActor;

};
