// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "ExtensionMethods.h"
#include "AuraExtensionMethods.generated.h"

/**
 * 导出扩展方法
 */
UCLASS()
class AURA_GAME_API UAuraExtensionMethods : public UExtensionMethods
{
	GENERATED_BODY()

public:
	/**
	 * 绑定输入动作
	 * @param InputComponent 输入组件
	 * @param InputAction 输入动作
	 * @param TriggerEvent 触发事件
	 * @param Object 绑定的对象
	 * @param FunctionName 绑定的函数名
	 */
	UFUNCTION(BlueprintCallable, Category="AuraExtensionMethods")
	static void BindAction(UEnhancedInputComponent* InputComponent, const UInputAction* InputAction, const ETriggerEvent TriggerEvent, UObject* Object, const FName& FunctionName);

	/**
	 * 调用TS方法
	 * @param Object			对象
	 * @param FunctionName		函数名
	 */
	UFUNCTION(BlueprintCallable, Category="AuraExtensionMethods")
	static void CallTS(const UObject* Object, const FString FunctionName);

	/**
	 * 写入文件
	 * @param FilePath			文件路径
	 * @param WriteContent		写入内容
	 */
	UFUNCTION(BlueprintCallable, Category="AuraExtensionMethods")
	static void WriteFile(const FString& FilePath, const FString& WriteContent);
};
