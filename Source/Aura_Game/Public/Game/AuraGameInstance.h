// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰

#pragma once

#include "CoreMinimal.h"
#include "JsEnv.h"
#include "Engine/GameInstance.h"
#include "AuraGameInstance.generated.h"

/**
 * 艾拉游戏实例
 */
UCLASS()
class AURA_GAME_API UAuraGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// 初始化
	virtual void Init() override;
	// 启动
	virtual void OnStart() override;
	// 退出
	virtual void Shutdown() override;

	// 创建ts虚拟机
	UFUNCTION(BlueprintCallable, Category="TS")
	void CreateTSVirtual(FString ScriptName = FString("MainGame"));

	// 销毁虚拟机
	UFUNCTION(BlueprintCallable, Category="TS")
	void DestroyTSVirtual();

protected:
	// 是否为调试模式
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Debug")
	uint8 bDebugMode : 1;

	// 是否等待调试
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Debug")
	uint8 bWaitForDebugger : 1;

	// 调用ts函数的代理
	DECLARE_DYNAMIC_DELEGATE_TwoParams(FCall, FString, FunctionName, UObject*, Uobject);

	// ts调用代理
	UPROPERTY()
	FCall FTsCall;

private:
	// 脚本环境
	TSharedPtr<puerts::FJsEnv> GameScript;

public:
	// 调用ts函数
	void TSCall(FString FunctionName, UObject* Uobject);
};
