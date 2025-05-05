// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "AbilitySystem/AuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	InitHealth(50.f);
	InitMaxHealth(100.f);
	InitMana(25);
	InitMaxMana(50.f);
}


void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}

// 属性改变时
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

// 属性改变后
void UAuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	/*if (Data.EvaluatedData.Attribute.GetUProperty() == nullptr) return;

	// 属性名
	FString AttributeName = Data.EvaluatedData.Attribute.GetUProperty()->GetName();
	// 血量限制
	if (AttributeName == "Health") SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	if (AttributeName == "MaxHealth") SetMaxHealth(FMath::Clamp(GetMaxHealth(), 0.f, GetMaxHealth()));
	// 魔法值限制
	if (AttributeName == "Mana") SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	if (AttributeName == "MaxMana") SetMaxMana(FMath::Clamp(GetMaxMana(), 0.f, GetMaxMana()));*/
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// 源 = 效果的起因，目标 = 效果的对象（此 AS 的所有者）

	// 1. 设置效果上下文
	Props.EffectContextHandle = Data.EffectSpec.GetContext();

	// 2. 获取源能力系统组件
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	// 3. 处理源方信息
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		// 获取源方的Avatar角色
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		// 获取源方的控制器
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		// 如果控制器为空但Avatar存在，尝试从Pawn获取控制器
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		// 如果控制器有效，获取其控制的角色
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	// 4. 处理目标方信息
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		// 获取目标方的Avatar角色
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		// 获取目标方的控制器
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		// 获取目标方的角色对象
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		// 获取目标方的能力系统组件
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth)
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth)
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana)
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana)
}
