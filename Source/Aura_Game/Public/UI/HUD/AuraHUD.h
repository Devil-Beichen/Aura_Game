// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

class UAuraUserWidget;
/**
 * Aura的HUD类，用于处理游戏界面的显示和交互。
 */
UCLASS()
class AURA_GAME_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	// 显示小组件
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:
	// 小组件类
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;
};
