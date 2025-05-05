// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
	EffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;
	EffectRemovalPolicy = EEffectRemovalPolicy::DoNotRemoval;
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
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect> GameplayEffClass)
{
	// 获取目标Actor的能力系统组件
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr)return;

	checkf(GameplayEffClass, *FString::Printf(TEXT("%s:没有设置对应效果类"),*this->GetName()));

	// 创建效果上下文并设置来源对象
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);

	// 创建效果规格(Level设为1.0f)
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffClass, ActorLevel, EffectContextHandle);

	// 将效果应用到目标自身
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// 判断效果是否为无限
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && EffectRemovalPolicy == EEffectRemovalPolicy::RemovalOnEndOverlap)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, GameplayEffectClass);
	}
}

/**
 * 当Actor结束重叠时调用的函数
 * 
 * @param TargetActor 结束重叠的目标Actor
 * 
 * 功能逻辑：
 * 1. 检查效果应用策略，如果是ApplyOnEndOverlap则对目标应用效果
 * 2. 检查效果移除策略，如果是RemovalOnEndOverlap则移除之前应用的无限效果
 */
void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	// 如果设置为在结束重叠时应用效果，则调用应用函数
	if (EffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, GameplayEffectClass);
	}

	// 如果设置为在结束重叠时移除效果
	if (EffectRemovalPolicy == EEffectRemovalPolicy::RemovalOnEndOverlap)
	{
		// 获取目标的能力系统组件
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		// 准备要移除的效果句柄列表
		TArray<FActiveGameplayEffectHandle> HandleToRemove;

		// 遍历所有已存储的活跃效果
		for (TPair<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair : ActiveEffectHandles)
		{
			// 如果找到属于当前目标ASC的效果
			if (TargetASC == HandlePair.Value)
			{
				// 从目标ASC中移除该效果
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				// 记录要移除的句柄
				HandleToRemove.Add(HandlePair.Key);
			}
		}

		// 从ActiveEffectHandles中移除已处理的效果句柄
		for (FActiveGameplayEffectHandle& Handle : HandleToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}
