// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "Libray/AuraExtensionMethods.h"

#include "EnhancedInputComponent.h"
#include "Game/AuraGameInstance.h"

// 绑定动作函数
void UAuraExtensionMethods::BindAction(UEnhancedInputComponent* InputComponent, const UInputAction* InputAction, const ETriggerEvent TriggerEvent, UObject* Object, const FName& FunctionName)
{
	if (InputComponent)
	{
		InputComponent->BindAction(InputAction, TriggerEvent, Object, FunctionName);
	}
}

// 调用TypeScript函数。
void UAuraExtensionMethods::CallTS(const UObject* Object, const FString FunctionName)
{
	if (Object)
	{
		UAuraGameInstance* GameInstance = Cast<UAuraGameInstance>(Object->GetWorld()->GetGameInstance());
		GameInstance->TSCall(FunctionName, const_cast<UObject*>(Object));
	}
}

/**
 * 将内容写入指定文件
 * @param FilePath 目标文件路径
 * @param WriteContent 要写入的内容
 * @note 实现逻辑：
 * 1. 先读取文件现有内容
 * 2. 检查内容是否已存在
 * 3. 若不存在则写入新内容
 */
void UAuraExtensionMethods::WriteFile(const FString& FilePath, const FString& WriteContent)
{
	FString ExistingContent; // 现有内容
	TArray<FString> ExistingLines;

	// 读取文件内容
	if (FFileHelper::LoadFileToString(ExistingContent, *FilePath))
	{
		// 将文件内容按行分割
		ExistingContent.ParseIntoArrayLines(ExistingLines, true);
	}
	TSet<FString> ExistingSet(ExistingLines);
	if (!ExistingSet.Contains(WriteContent))
	{
		// 在尾部写入新内容
		FFileHelper::SaveStringToFile(ExistingContent + WriteContent, *FilePath, FFileHelper::EEncodingOptions::ForceUTF8);
		return;
	}
}
