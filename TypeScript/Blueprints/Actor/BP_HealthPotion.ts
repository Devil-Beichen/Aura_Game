import * as UE from "ue";
import mixin from "../../mixin";
import {$Nullable} from "puerts";

// 资产路径
const AssetPath = "/Game/Blueprints/Actor/BP_HealthPotion.BP_HealthPotion_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface BP_HealthPotion extends UE.Game.Blueprints.Actor.BP_HealthPotion.BP_HealthPotion_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class BP_HealthPotion implements BP_HealthPotion {

    ReceiveBeginPlay() {
        this.Sphere.OnComponentBeginOverlap.Add((...args) => this.SphereBeginOverlay(...args))
    }

    // 重叠
    SphereBeginOverlay(OverlappedComponent: $Nullable<UE.PrimitiveComponent>, OtherActor: $Nullable<UE.Actor>, OtherComp: $Nullable<UE.PrimitiveComponent>, OtherBodyIndex: number, bFromSweep: boolean, SweepResult: UE.HitResult) {
        
        if (OtherActor == this) return
        this.ApplyEffectToTarget(OtherActor, this.InstantGameplayEffectClass)
    }
}