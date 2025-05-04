import * as UE from "ue";
import mixin from "../../../mixin";
import {$Nullable} from "puerts";

// 资产路径
const AssetPath = "/Game/Blueprints/Actor/Crystal/BP_CrystalBase.BP_CrystalBase_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface BP_CrystalBase extends UE.Game.Blueprints.Actor.Crystal.BP_CrystalBase.BP_CrystalBase_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class BP_CrystalBase implements BP_CrystalBase {


    ReceiveBeginPlay() {
        this.Capsule.OnComponentBeginOverlap.Add((...args) => this.CapsuleBeginOverlay(...args))
    }

    // 重叠
    CapsuleBeginOverlay(OverlappedComponent: $Nullable<UE.PrimitiveComponent>, OtherActor: $Nullable<UE.Actor>, OtherComp: $Nullable<UE.PrimitiveComponent>, OtherBodyIndex: number, bFromSweep: boolean, SweepResult: UE.HitResult) {

        if (OtherActor == this) return
        this.ApplyEffectToTarget(OtherActor, this.GameplayEffectClass)

        this.K2_DestroyActor()
    }
}