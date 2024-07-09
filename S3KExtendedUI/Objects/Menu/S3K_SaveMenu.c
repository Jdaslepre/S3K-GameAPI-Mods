#include "../../Include.h"

ObjectS3K_SaveMenu *S3K_SaveMenu;
ModObjectS3K_SaveMenu *ModS3K_SaveMenu;

void S3K_SaveMenu_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(S3K_SaveMenu);

    if (!cfg.useTouch)
        return;

    MOD_REGISTER_OBJ_OVERLOAD_MSV(S3K_SaveMenu, ModS3K_SaveMenu, NULL, NULL, S3K_SaveMenu_StaticUpdate, S3K_SaveMenu_Draw, S3K_SaveMenu_Create,
                                  S3K_SaveMenu_StageLoad, NULL, NULL, NULL);
}

void S3K_SaveMenu_BackButton(void) {
    // Back button
    SpriteFrame *back = RSDK.GetFrame(ModS3K_SaveMenu->aniFrames, 0, 0);

    int32 touchX = ScreenInfo->size.x - back->width - 6;
    int32 touchY = ScreenInfo->size.y - back->height - 6;

    if (TouchHelpers_CheckTouchRect(touchX, touchY, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
        // check if we're touching the back button

        ModS3K_SaveMenu->backAlpha         = 224;
        ModS3K_SaveMenu->backActionPending = true;
        ModS3K_SaveMenu->backPrevTouch     = true;
    } else if (ModS3K_SaveMenu->backPrevTouch && TouchHelpers_CheckAnyTouch() >= 0) {
        // check if we slid off the button, so cancel the scene transition

        ModS3K_SaveMenu->backAlpha         = 255;
        ModS3K_SaveMenu->backActionPending = false;
        ModS3K_SaveMenu->backPrevTouch     = false;
    } else if (ModS3K_SaveMenu->backActionPending) {
        // if we really mean to go back, just go back

        ModS3K_SaveMenu->backAlpha         = 255;
        ModS3K_SaveMenu->backActionPending = false;
        ModS3K_SaveMenu->backPrevTouch     = false;

        ControllerInfo->keyB.press = true;
    }
}

// ----------------------
// Standard Entity Events
// ----------------------

void S3K_SaveMenu_StaticUpdate(void) {
    S3K_SaveMenu_BackButton();

    Mod.Super(S3K_SaveMenu->classID, SUPER_STATICUPDATE, NULL);
}

void S3K_SaveMenu_Draw(void) {
    RSDK_THIS(S3K_SaveMenu);

    Vector2 drawPos;

    // -----------
    // Back Button
    // -----------

    SpriteFrame *back = RSDK.GetFrame(ModS3K_SaveMenu->aniFrames, 0, 0);

    // back up our values
    int32 prevValues[2];
    prevValues[0] = self->inkEffect;
    prevValues[1] = self->alpha;

    drawPos.x = ScreenInfo->size.x - back->width << 16;
    drawPos.y = ScreenInfo->size.y - back->height << 16;

    self->inkEffect                  = INK_ALPHA;
    self->alpha                      = ModS3K_SaveMenu->backAlpha;
    ModS3K_SaveMenu->animator.frameID = 0;
    RSDK.DrawSprite(&ModS3K_SaveMenu->animator, &drawPos, true);

    // set em back
    self->inkEffect = prevValues[0];
    self->alpha     = prevValues[1];

    // drawPos.x  = ScreenInfo->size.x - back->width - 6;
    // drawPos.y = ScreenInfo->size.y - back->height - 6;

    // RSDK.DrawRect(drawPos.x, drawPos.y, back->width + 6, back->height + 6, touchCol, 60, INK_ALPHA, true);

    Mod.Super(S3K_SaveMenu->classID, SUPER_DRAW, NULL);
}

void S3K_SaveMenu_Create(void *data) {
    RSDK_THIS(S3K_SaveMenu);
    RSDK.SetSpriteAnimation(ModS3K_SaveMenu->aniFrames, 0, &ModS3K_SaveMenu->animator, true, 0);

    Mod.Super(S3K_SaveMenu->classID, SUPER_CREATE, data);
}

void S3K_SaveMenu_StageLoad(void) {
    ModS3K_SaveMenu->aniFrames         = RSDK.LoadSpriteAnimation("3K_Menu/Menu_TouchEx.bin", SCOPE_STAGE);
    ModS3K_SaveMenu->backAlpha         = 255;
    ModS3K_SaveMenu->backActionPending = false;
    ModS3K_SaveMenu->backPrevTouch     = false;
    Mod.Super(S3K_SaveMenu->classID, SUPER_STAGELOAD, NULL);
}