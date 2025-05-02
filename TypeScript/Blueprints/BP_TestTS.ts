import * as UE from "ue";
import mixin from "../mixin";

// 资产路径
const AssetPath = "/Game/Blueprints/BP_TestTS.BP_TestTS_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface BP_TestTS extends UE.Game.Blueprints.BP_TestTS.BP_TestTS_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class BP_TestTS implements BP_TestTS {
    ReceiveBeginPlay() {
        console.log("ReceiveBeginPlay启动");
    }

    TsFun() {

        console.log("TsFun");


    }


}

