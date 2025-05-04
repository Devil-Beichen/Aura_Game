import * as UE from "ue";
import mixin from "../../../mixin";

// 资产路径
const AssetPath = "/Game/Blueprints/UI/Overlay/WBP_Overlay.WBP_Overlay_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface WBP_Overlay extends UE.Game.Blueprints.UI.Overlay.WBP_Overlay.WBP_Overlay_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class WBP_Overlay implements WBP_Overlay {

    // 控制器设置完成
    WidgetControllerSet() {
        this.WBPHealthGlobe.SetWidgetController(this.WidgetController)
        this.WBPManaGlobe.SetWidgetController(this.WidgetController)
    }
}