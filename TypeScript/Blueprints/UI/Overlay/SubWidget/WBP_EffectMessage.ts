import * as UE from "ue";
import mixin from "../../../../mixin";

// 资产路径
const AssetPath = "/Game/Blueprints/UI/Overlay/SubWidget/WBP_EffectMessage.WBP_EffectMessage_C";

// 创建一个继承ts类（或者其他类）的接口（用来类型提示）
export interface WBP_EffectMessage extends UE.Game.Blueprints.UI.Overlay.SubWidget.WBP_EffectMessage.WBP_EffectMessage_C {
}

// 创建一个继承ts的本体类    implements   实现类型提示
@mixin(AssetPath)
export class WBP_EffectMessage implements WBP_EffectMessage {

    // 设置图标和文本
    SetBrushAndText(Image: UE.Texture2D, Text: string) {
        this.Text_Message.SetText(Text)
        if (Image) {
            this.ImageSizeSet()
            this.Image_Icon.SetBrushFromTexture(Image)
        }
        this.PlayAnimationForward(this.MessageAnimation, (1 / 0.7))

        setTimeout(() => {
            this.RemoveFromParent()
        }, 0.7 * 1000);

    }
}