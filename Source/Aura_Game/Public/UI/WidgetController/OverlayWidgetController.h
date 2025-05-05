// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "GameplayTagContainer.h"
#include "OverlayWidgetController.generated.h"

class UAuraUserWidget;
struct FOnAttributeChangeData;

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

// 创建一个动态多播委托复制监听属性发生改变
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);

// 创建一个动态多播委托广播UI的数据表
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);


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

	/**
	 * UI数据表消息监听
	 */
	UPROPERTY(BlueprintAssignable, Category="GAS|Message")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

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

	/**
	 * 根据标签获取数据表行
	 * 
	 * @tparam T 数据表行的类型，通常是一个数据结构
	 * @param DataTable 数据表对象，从中获取数据
	 * @param Tag 游戏标签，用于标识特定的数据表行
	 * @return T* 如果找到匹配的行则返回该行的指针，否则返回nullptr
	 * 
	 * 此函数通过游戏标签在指定的数据表中查找对应的行，并返回该行的指针
	 * 它假设数据表中包含与标签关联的行数据如果标签没有在数据表中找到匹配项，
	 * 则返回nullptr此函数适用于需要根据标签快速检索数据表行的场景
	 */
	template <typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
};

template <typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(),TEXT(""));
}
