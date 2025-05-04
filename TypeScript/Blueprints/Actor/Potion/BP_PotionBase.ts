import * as UE from "ue";
import mixin from "../../../mixin";
import {$Nullable} from "puerts";

// 资产路径
const AssetPath = "/Game/Blueprints/Actor/Potion/BP_PotionBase.BP_PotionBase_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface BP_PotionBase extends UE.Game.Blueprints.Actor.Potion.BP_PotionBase.BP_PotionBase_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class BP_PotionBase implements BP_PotionBase {

    ReceiveBeginPlay() {
        this.Sphere.OnComponentBeginOverlap.Add((...args) => this.SphereBeginOverlay(...args))
    }

    // 重叠
    SphereBeginOverlay(OverlappedComponent: $Nullable<UE.PrimitiveComponent>, OtherActor: $Nullable<UE.Actor>, OtherComp: $Nullable<UE.PrimitiveComponent>, OtherBodyIndex: number, bFromSweep: boolean, SweepResult: UE.HitResult) {

        if (OtherActor == this) return
        this.ApplyEffectToTarget(OtherActor, this.GameplayEffectClass)

        this.K2_DestroyActor()
    }
}