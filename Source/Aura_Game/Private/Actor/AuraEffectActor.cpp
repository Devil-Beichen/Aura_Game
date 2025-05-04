// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

/**
 * 对目标Actor应用游戏效果(GameplayEffect)
 * 
 * @param TargetActor 要应用效果的目标Actor，必须具有AbilitySystemComponent组件
 * @param GameplayEffClass 要应用的UGameplayEffect子类，定义效果的具体行为
 * 
 * 实现流程：
 * 1. 从目标Actor获取能力系统组件(ASC)
 * 2. 创建效果上下文(EffectContext)，设置效果来源
 * 3. 创建效果规格(EffectSpec)，包含效果的具体参数
 * 4. 将效果应用到目标自身
 */
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffClass) const
{
	// 获取目标Actor的能力系统组件
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr)return;

	checkf(GameplayEffClass, *FString::Printf(TEXT("%s:没有设置对应效果类"),*this->GetName()));

	// 创建效果上下文并设置来源对象
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	// 创建效果规格(Level设为1.0f)
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffClass, 1.f, EffectContextHandle);

	// 将效果应用到目标自身
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
