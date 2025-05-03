// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "Character/AuraCharacter.h"

#include "Aura_Game.h"
#include "GameFramework/CharacterMovementComponent.h"


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

void AAuraCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
