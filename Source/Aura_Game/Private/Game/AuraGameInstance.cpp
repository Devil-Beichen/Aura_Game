// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "Game/AuraGameInstance.h"

// 初始化
void UAuraGameInstance::Init()
{
	Super::Init();
	CreateTSVirtual();
}

// 启动
void UAuraGameInstance::OnStart()
{
	Super::OnStart();
}

// 关闭
void UAuraGameInstance::Shutdown()
{
	Super::Shutdown();
	DestroyTSVirtual();
}

// 创建虚拟机
void UAuraGameInstance::CreateTSVirtual(FString ScriptName)
{
	if (bDebugMode)
	{
		// 在调试模式下，创建一个带有调试功能的 `puerts::FJsEnv` 实例
		// 使用自定义的 JavaScript 模块加载器和默认的日志记录器，并指定调试端口为 8080
		GameScript = MakeShared<puerts::FJsEnv>(
			std::make_unique<puerts::DefaultJSModuleLoader>(TEXT("JavaScript")),
			std::make_shared<puerts::FDefaultLogger>(),
			8080
		);

		// 如果需要等待调试器连接，则调用 `WaitDebugger` 方法
		if (bWaitForDebugger)
		{
			GameScript->WaitDebugger();
		}
	}
	else
	{
		// 在非调试模式下，创建一个普通的 `puerts::FJsEnv` 实例
		GameScript = MakeShared<puerts::FJsEnv>();
	}

	// 准备传递给脚本的参数列表，包含游戏实例对象
	TArray<TPair<FString, UObject*>> Arguments;
	Arguments.Add({TEXT("GameInstance"), this});

	// 启动脚本，指定入口模块为 "MainGame"，并传递参数
	GameScript->Start(ScriptName, Arguments);
}

// 销毁虚拟机
void UAuraGameInstance::DestroyTSVirtual()
{
	if (GameScript.IsValid())
	{
		GameScript.Reset();
	}
}

// 调用脚本方法
void UAuraGameInstance::TSCall(FString FunctionName, UObject* Uobject)
{
	FTsCall.ExecuteIfBound(FunctionName, Uobject);
}
