// 这是一款名为《元素之主：艾拉》的游戏项目，所有者是逸辰


#include "Player/AuraPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	PrimaryActorTick.bCanEverTick = true; // 确保玩家控制器每帧都会执行Tick函数
	bReplicates = true; // 确保玩家控制器在服务器和客户端之间同步
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 检查输入映射上下文资源是否有效
	check(AuraContext);

	// 获取本地玩家的增强输入子系统
	if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// 添加输入映射上下文到子系统，优先级为0
		EnhancedSubsystem->AddMappingContext(AuraContext, 0);
	}
	// 设置鼠标显示状态
	bShowMouseCursor = true; // 显示鼠标光标
	DefaultMouseCursor = EMouseCursor::Default; // 使用默认光标样式

	// 配置游戏和UI混合输入模式
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); // 不锁定鼠标到视口
	InputModeData.SetHideCursorDuringCapture(false); // 捕获输入时不隐藏光标
	SetInputMode(InputModeData); // 应用配置好的输入模式
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit && !CursorHit.GetActor()) return;
	if (!CursorHit.GetActor()->GetClass()->ImplementsInterface(UEnemyInterface::StaticClass())) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 *	在光标命中处，存在多种情况
	 *	A.	LastActor和ThisActor都为空
	 *		-	什么都不做
	 *	B.	LastActor为空 ThisActor有效
	 *		-	ThisActor高亮显示
	 *	C.	LastActor有效 ThisActor为空
	 *		-	LastActor取消高亮显示
	 *	D.	LastActor和ThisActor都有效，但是 LastActor != ThisActor
	 *		-	LastActor取消高亮显示，LastActor高亮显示
	 *	E.	LastActor和ThisActor都有效
	 *		-	什么都不做
	 */

	if (LastActor == nullptr && ThisActor)
	{
		// B
		ThisActor->HighLightActor();
	}
	else if (LastActor && ThisActor == nullptr)
	{
		// C
		LastActor->UnHighLightActor();
	}
	else if (LastActor && ThisActor && LastActor != ThisActor)
	{
		// D
		LastActor->UnHighLightActor();
		ThisActor->HighLightActor();
	}
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	GetPawn()->AddMovementInput(ForwardDirection, InputAxisVector.Y);
	GetPawn()->AddMovementInput(RightDirection, InputAxisVector.X);
}
