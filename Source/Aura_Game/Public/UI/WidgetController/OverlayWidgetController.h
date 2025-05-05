// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
struct FOnAttributeChangeData;
// 创建一个动态多播委托复制监听属性发生改变
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

/**
 * 用于数据表格(DataTable)的UI控件行配置结构
 * 用于定义游戏中各种UI消息的显示方式和内容
 */
USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	// 消息关联的GameplayTag，用于标识和匹配特定类型的消息
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	// 实际显示的文本消息内容
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	// 用于显示此消息的自定义Widget类
	// 可以为不同类型的消息指定不同的显示样式
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAuraUserWidget> MessageWidget;

	// 用于显示此消息的图标
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};


/**
 * OverlayWidget的控制器
 */
UCLASS(BlueprintType, Blueprintable)
class AURA_GAME_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	// 广播初始值
	virtual void BroadcastInitialValues() override;
	// 绑定属性监听
	virtual void BindCallbacksToDependencies() override;

	/**
	 * 血量值监听
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	/**
	 * 魔法值监听
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

protected:
	// 消息数据表
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	// 监听当前血量
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	// 监听最大血量
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	// 监听当前魔法值
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	// 监听最大魔法值
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
