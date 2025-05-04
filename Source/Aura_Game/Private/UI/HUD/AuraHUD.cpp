// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "UI/HUD/AuraHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

// 获取或创建覆盖层(Overlay)的Widget控制器
// @param WCParams - Widget控制器初始化参数
// @return 返回OverlayWidgetController实例指针
UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	// 如果控制器尚未创建
	if (OverlayWidgetController == nullptr)
	{
		// 创建新的OverlayWidgetController实例
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		// 初始化控制器参数
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		// 绑定控制器属性的回调
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}
	// 返回已存在的控制器实例
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(class APlayerController* PC, class APlayerState* PS, class UAbilitySystemComponent* ASC, class UAttributeSet* AS)
{
	// 检查OverlayWidgetClass是填写
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, olease fill out BP_AuraHUD"));
	// 检查OverlayWidgetControllerClass是填写
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, olease fill out BP_AuraHUD"))

	// 创建用户界面小部件
	// GetWorld() 提供当前世界的引用，OverlayWidgetClass 是要创建的小部件类的蓝图类型
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	// 将创建的小部件转换为特定的 UAuraUserWidget 类型
	OverlayWidget = Cast<UAuraUserWidget>(Widget);

	// 初始化小部件控制器参数
	// 参数包括：PC（玩家控制器），PS（玩家状态），ASC（属性系统控制器），AS（属性系统）
	FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);

	// 获取覆盖小部件控制器
	// 该控制器用于管理特定的小部件，这里是为 OverlayWidget 准备的
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);

	// 设置小部件的控制器
	// 这样小部件就能通过控制器与游戏的其他部分交互
	OverlayWidget->SetWidgetController(WidgetController);

	// 广播初始值
	WidgetController->BroadcastInitialValues();

	// 将小部件添加到视口
	// 使其在屏幕上可见
	Widget->AddToViewport();
}
