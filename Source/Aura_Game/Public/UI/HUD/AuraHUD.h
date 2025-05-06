// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AuraHUD.generated.h"

struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;
/**
 * Aura的HUD类，用于处理游戏界面的显示和交互。
 */
UCLASS()
class AURA_GAME_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	// 覆加在组界面的小组件
	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	// 获取OverlayWidgetController
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);

	// 初始化Overlay
	void InitOverlay(class APlayerController* PC, class APlayerState* PS, class UAbilitySystemComponent* ASC, class UAttributeSet* AS);

protected:

private:
	// 覆盖式小部件类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAuraUserWidget> OverlayWidgetClass;

	// 覆盖式小部件控制器
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	// 覆盖式小部件控制器类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
};
