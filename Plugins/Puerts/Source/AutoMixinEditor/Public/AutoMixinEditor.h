#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FAutoMixinEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	// 添加mixin文件
	void AddMixinFile() const;
	// 注册按键
	void RegistrationButton();
	// 按键按下
	void ButtonPressed();
	// 获取当前激活的Blueprint
	UBlueprint* GetActiveBlueprint() const;

	/**
	 * 处理模板
	 * @param TemplateContent	模板内容 
	 * @param BlueprintPath		蓝图路径路径
	 * @param FileName			文件名
	 * @return 
	 */
	FString ProcessTemplate(const FString& TemplateContent, FString BlueprintPath, FString FileName);

	// 样式名称
	FName GetStyleName() const;

	void InitStyleSet();

	// 样式
	static TSharedPtr<FSlateStyleSet> StyleSet;

	// mixin文件路径
	const FString MixinPath = FPaths::Combine(FPaths::ProjectDir(),TEXT("TypeScript"),TEXT("mixin.ts"));
};
