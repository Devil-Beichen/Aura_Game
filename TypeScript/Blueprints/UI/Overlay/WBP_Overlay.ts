import * as UE from "ue";
import mixin from "../../../mixin";
import {BP_OverlayWidgetController} from "../WidgetController/BP_OverlayWidgetController";

// 资产路径
const AssetPath = "/Game/Blueprints/UI/Overlay/WBP_Overlay.WBP_Overlay_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface WBP_Overlay extends UE.Game.Blueprints.UI.Overlay.WBP_Overlay.WBP_Overlay_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class WBP_Overlay implements WBP_Overlay {

    // 蓝图OverlayWidgetController
   OverlayWidgetController: BP_OverlayWidgetController;

    // 控制器设置完成
    WidgetControllerSet() {
        this.OverlayWidgetController = this.WidgetController as BP_OverlayWidgetController
        this.BindCallBack()
        this.WBPHealthGlobe.SetWidgetController(this.WidgetController)
        this.WBPManaGlobe.SetWidgetController(this.WidgetController)
    }

    // 绑定回调函数
    BindCallBack() {
        if(!this.OverlayWidgetController) return
        this.OverlayWidgetController.MessageWidgetRowDelegate.Add((...args) => this.MessageWidgetRowEvent(...args))
    }

    // 消息事件
    MessageWidgetRowEvent(Row: UE.UIWidgetRow) {
        UE.KismetSystemLibrary.PrintString(this, Row.Message)
    }
}