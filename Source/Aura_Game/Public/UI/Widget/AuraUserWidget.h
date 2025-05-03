// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 艾拉用户小部件
 */
UCLASS()
class AURA_GAME_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// 设置小部件控制器
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	// 小部件控制器
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	// 小部件控制器已经设置
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
