import * as UE from "ue";
import mixin from "../../mixin";

// 资产路径
const AssetPath = "/Game/Blueprints/Character/ABP_Enemy.ABP_Enemy_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface ABP_Enemy extends UE.Game.Blueprints.Character.ABP_Enemy.ABP_Enemy_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class ABP_Enemy implements ABP_Enemy {
    Character: UE.AuraEnemy

    BlueprintInitializeAnimation() {
        this.Character = this.TryGetPawnOwner() as UE.AuraEnemy
    }
    
    BlueprintUpdateAnimation(DeltaTimeX: number) {
        if (this.Character) {
            this.GroundSpeed = this.Character.CharacterMovement.Velocity.Size2D()
        }
    }
}