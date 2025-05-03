import * as UE from "ue";
import mixin from "../../mixin";

// 资产路径
const AssetPath = "/Game/Blueprints/Character/BP_EnemyBase.BP_EnemyBase_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface BP_EnemyBase extends UE.Game.Blueprints.Character.BP_EnemyBase.BP_EnemyBase_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class BP_EnemyBase implements BP_EnemyBase {
}