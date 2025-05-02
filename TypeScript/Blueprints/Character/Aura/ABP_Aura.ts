import * as UE from "ue";
import mixin from "../../../mixin";
import {BP_AuraCharacter} from "./BP_AuraCharacter";

// 资产路径
const AssetPath = "/Game/Blueprints/Character/Aura/ABP_Aura.ABP_Aura_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface ABP_Aura extends UE.Game.Blueprints.Character.Aura.ABP_Aura.ABP_Aura_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class ABP_Aura implements ABP_Aura {
    // 角色
    Character: BP_AuraCharacter;

    
    /**
     * 动画蓝图初始化函数
     * 在动画蓝图首次创建时被调用，用于初始化角色引用
     * 
     * 实现逻辑：
     * 1. 通过TryGetPawnOwner获取动画实例所属的Pawn
     * 2. 将Pawn转换为BP_AuraCharacter类型并赋值给Character成员变量
     * 
     * @note 这是动画蓝图的标准生命周期函数，由UE引擎自动调用
     */
    BlueprintInitializeAnimation() {
        this.Character = this.TryGetPawnOwner() as BP_AuraCharacter
    }


      /**
     * 动画蓝图更新函数（每帧调用）
     * 计算并更新角色的地面移动速度
     * 
     * 实现逻辑：
     * 1. 检查Character引用是否有效
     * 2. 获取角色移动组件的水平速度（忽略Z轴）
     * 3. 将速度值赋给动画蓝图的GroundSpeed变量
     * 
     * @param DeltaTimeX 帧时间差（秒）
     * @note 这是动画蓝图的标准更新函数，由UE引擎每帧自动调用
     * @see CharacterMovement 角色的移动组件
     * @see Velocity 当前帧的角色速度向量
     * @see Size2D() 计算水平面(XY)速度大小
     */
    BlueprintUpdateAnimation(DeltaTimeX: number) {
        if (this.Character) {
            this.GroundSpeed = this.Character.CharacterMovement.Velocity.Size2D()
        }
    }

}