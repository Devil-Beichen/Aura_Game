import * as UE from "ue";
import mixin from "../../../mixin";
import {Brush} from "ue";

// 资产路径
const AssetPath = "/Game/Blueprints/UI/ProgressBar/WBP_GlobeProgressBar.WBP_GlobeProgressBar_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface WBP_GlobeProgressBar extends UE.Game.Blueprints.UI.ProgressBar.WBP_GlobeProgressBar.WBP_GlobeProgressBar_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class WBP_GlobeProgressBar implements WBP_GlobeProgressBar {
   /* PreConstruct(IsDesignTime: boolean) {

        this.UpdateBoxSize()
        this.UpdateBackgroundBrush()


    }*/

    /*// 刷新大小
    UpdateBoxSize() {
        this.SizeBoxRoot.SetWidthOverride(this.BoxWidth)
        this.SizeBoxRoot.SetHeightOverride(this.BoxHeight)
    }

    // 更新背景画布
    UpdateBackgroundBrush() {
        this.ImageBackground.SetBrush(this.BackgroundBrush)
    }*/
}