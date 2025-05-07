// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "Aura_Game.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerController.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"


AAuraCharacter::AAuraCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true; // 角色移动时自动调整旋转
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true; // 限制角色移动方向为平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 角色开始移动时自动调整位置

	// 禁用控制器旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_GREE);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_GREE);
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	// 服务器初始化能力参与者信息
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// 客户端初始化能力参与者信息
	InitAbilityActorInfo();
}

// 初始化能力系统参与者信息
// 该方法在服务器端(PossessedBy)和客户端(OnRep_PlayerState)都会被调用
// 主要功能：
// 1. 初始化AbilitySystemComponent的Actor信息
// 2. 设置本地AbilitySystemComponent和AttributeSet引用
// 3. 初始化HUD的Overlay界面
void AAuraCharacter::InitAbilityActorInfo()
{
	// 获取AuraPlayerState实例
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState) // 确保PlayerState有效

	// 初始化AbilitySystemComponent的Actor信息
	// 参数说明：
	// - AuraPlayerState: 作为OwnerActor
	// - this: 作为AvatarActor
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);

	// 设置本地引用
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();

	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet(); // Actor的GAS能力成化设置

	// 初始化HUD Overlay界面
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController()))
	{
		if (AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD()))
		{
			// 初始化Overlay界面
			// 参数说明：
			// - AuraPlayerController: 玩家控制器
			// - AuraPlayerState: 玩家状态
			// - AbilitySystemComponent: 能力系统组件
			// - AttributeSet: 属性集
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}

	InitializePrimaryAttributes(); // 初始化主要属性
}

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
