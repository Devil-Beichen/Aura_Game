import * as UE from "ue";
import mixin from "../../../mixin";
import {BP_OverlayWidgetController} from "../WidgetController/BP_OverlayWidgetController";

// 资产路径
const AssetPath = "/Game/Blueprints/UI/ProgressBar/WBP_GlobeProgressBar.WBP_GlobeProgressBar_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface WBP_GlobeProgressBar extends UE.Game.Blueprints.UI.ProgressBar.WBP_GlobeProgressBar.WBP_GlobeProgressBar_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class WBP_GlobeProgressBar implements WBP_GlobeProgressBar {

    // 蓝图OverlayWidgetController
    OverlayWidgetController: BP_OverlayWidgetController;

    // 设置进度条百分比
    SetProgressBarPercent(Percent: number) {
        this.ProgressBar_Globe.SetPercent(Percent)
    }
} 