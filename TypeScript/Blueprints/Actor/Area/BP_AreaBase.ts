import * as UE from "ue";
import mixin from "../../../mixin";
import {$Nullable} from "puerts";

// 资产路径
const AssetPath = "/Game/Blueprints/Actor/Area/BP_AreaBase.BP_AreaBase_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface BP_AreaBase extends UE.Game.Blueprints.Actor.Area.BP_AreaBase.BP_AreaBase_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class BP_AreaBase implements BP_AreaBase {

    ReceiveBeginPlay() {
        this.Box.OnComponentBeginOverlap.Add((...args) => this.BoxBeginOverlay(...args))
        this.Box.OnComponentEndOverlap.Add((...args) => this.BoxEndOverlay(...args))
    }

    // 重叠
    BoxBeginOverlay(OverlappedComponent: $Nullable<UE.PrimitiveComponent>, OtherActor: $Nullable<UE.Actor>, OtherComp: $Nullable<UE.PrimitiveComponent>, OtherBodyIndex: number, bFromSweep: boolean, SweepResult: UE.HitResult) {

        if (OtherActor == this) return
        this.OnOverlap(OtherActor)
    }

    // 离开
    BoxEndOverlay(OverlappedComponent: $Nullable<UE.PrimitiveComponent>, OtherActor: $Nullable<UE.Actor>, OtherComp: $Nullable<UE.PrimitiveComponent>, OtherBodyIndex: number) {

        this.OnEndOverlap(OtherActor)
    }
}