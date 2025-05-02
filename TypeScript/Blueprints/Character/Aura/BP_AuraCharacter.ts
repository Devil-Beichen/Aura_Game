// 艾拉
import * as UE from "ue";
import mixin from "../../../mixin";

// 资产路径
const AssetPath = "/Game/Blueprints/Character/Aura/BP_AuraCharacter.BP_AuraCharacter_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface BP_AuraCharacter extends UE.Game.Blueprints.Character.Aura.BP_AuraCharacter.BP_AuraCharacter_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class BP_AuraCharacter implements BP_AuraCharacter {
}