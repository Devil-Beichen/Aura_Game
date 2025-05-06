import * as UE from "ue";
import mixin from "../../../mixin";
import {WBP_GlobeProgressBar} from "./WBP_GlobeProgressBar";
import {BP_OverlayWidgetController} from "../WidgetController/BP_OverlayWidgetController";


// 资产路径
const AssetPath = "/Game/Blueprints/UI/ProgressBar/WBP_HealthGlobe.WBP_HealthGlobe_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface WBP_HealthGlobe extends UE.Game.Blueprints.UI.ProgressBar.WBP_HealthGlobe.WBP_HealthGlobe_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class WBP_HealthGlobe extends WBP_GlobeProgressBar implements WBP_HealthGlobe {

    Health: number;
    MaxHealth: number;

    Tick(MyGeometry: UE.Geometry, InDeltaTime: number) {
        super.Tick(MyGeometry, InDeltaTime);
    }

    // 控制器完成设置
    WidgetControllerSet() {
        this.OverlayWidgetController = this.WidgetController as BP_OverlayWidgetController
        this.OverlayWidgetController.OnHealthChanged.Add((...args) => this.OnCurrentChanged(...args))
        this.OverlayWidgetController.OnMaxHealthChanged.Add((...args) => this.OnMaxChanged(...args))
    }

    // 监听当前属性变化
    OnCurrentChanged(NewValue: number) {
        this.Health = NewValue
        const pre = (this.MaxHealth != 0) ? (this.Health / this.MaxHealth) : 0
        this.SetProgressBarPercent(pre)
    }

    // 监听最大属性变化
    OnMaxChanged(NewValue: number) {
        this.MaxHealth = NewValue
        const pre = (this.MaxHealth != 0) ? (this.Health / this.MaxHealth) : 0
        this.SetProgressBarPercent(pre)
    }
}