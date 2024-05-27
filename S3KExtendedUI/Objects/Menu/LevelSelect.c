#include "../../Include.h"

ObjectLevelSelect *LevelSelect;
ModObjectLevelSelect *ModLevelSelect;

void LevelSelect_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(LevelSelect);
    LevelSelect_State_Navigate = Mod.GetPublicFunction(NULL, "LevelSelect::State_Navigate");

    if (!cfg.useTouch)
        return;
    
    Mod.RegisterStateHook(LevelSelect_State_Navigate, LevelSelect_State_Navigate_Hook, true);
    MOD_REGISTER_OBJ_OVERLOAD_MSV_STATIC(LevelSelect, ModLevelSelect, NULL, NULL, NULL, LevelSelect_Draw, LevelSelect_Create, LevelSelect_StageLoad,
                                         NULL, NULL, NULL, LevelSelect_StaticLoad);
}

bool32 LevelSelect_State_Navigate_Hook(bool32 skippedState) {
    RSDK_THIS(LevelSelect);

    // Dpad
    int32 touch = TouchHelpers_CheckTouchRect(0, 96, ScreenInfo->center.x - 56, ScreenInfo->size.y, NULL, NULL);
    if (touch >= 0) {

        int32 touchX = (int32)(TouchInfo->x[touch] * ScreenInfo->size.x) - 64;
        int32 touchY = (int32)(TouchInfo->y[touch] * ScreenInfo->size.y) - 202;

        RSDK.ATan2(touchX, touchY);

        // I think there's a problem with this, it might not work near the bottom of the screen? check v4 player script
        switch (((RSDK.ATan2(touchX, touchY) + 0x20) & 0xFF) >> 6) {
            case 0:
                ControllerInfo->keyRight.down = true;

                if (!ModLevelSelect->pressedLR)
                    ControllerInfo->keyRight.press |= ControllerInfo->keyRight.down;

                ModLevelSelect->pressedLR = ControllerInfo->keyRight.down;
                break;

            case 1: ControllerInfo->keyDown.down = true; break;

            case 2:
                ControllerInfo->keyLeft.down = true;

                if (!ModLevelSelect->pressedLR)
                    ControllerInfo->keyLeft.press |= ControllerInfo->keyLeft.down;

                ModLevelSelect->pressedLR = ControllerInfo->keyLeft.down;
                break;

            case 3: ControllerInfo->keyUp.down = true; break;
        }

        int32 x1 = ScreenInfo->size.x - 62;
        int32 x2 = x1 + 48;

        if (TouchHelpers_CheckTouchRect(x1, 172, x2, 222, NULL, NULL) >= 0)
            ModLevelSelect->pressed = true;
        else
            ModLevelSelect->pressed = false;
    } else {
        ModLevelSelect->pressedLR = false;
    }

    // Go/Start button
    if (TouchHelpers_CheckTouchRect(0, 0, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL) >= 0) {
        int32 x1 = ScreenInfo->size.x - 62;
        int32 x2 = x1 + 48;

        if (TouchHelpers_CheckTouchRect(x1, 172, x2, 222, NULL, NULL) >= 0)
            ModLevelSelect->pressed = true;
        else
            ModLevelSelect->pressed = false;
    } else if (ModLevelSelect->pressed) {
        ModLevelSelect->pressed = false;

        if (self->labelID >= self->labelCount - 1)
            ControllerInfo->keyA.press = true;
        else
            ControllerInfo->keyStart.press = true;
    }

    return false;
}

void LevelSelect_Draw(void) {
    RSDK_THIS(LevelSelect);

    int32 prevInfo[3];
    prevInfo[0] = self->alpha;
    prevInfo[1] = self->inkEffect;
    prevInfo[2] = RSDK.GetPaletteEntry(0, 82);

    self->alpha     = 160;
    self->inkEffect = INK_ALPHA;

    // set a blue color, because this specific index
    // is messed up in origins for whatever reason
    RSDK.SetPaletteEntry(0, 82, 0x000080);

    Vector2 drawPos;
    drawPos.x = TO_FIXED(62);
    drawPos.y = TO_FIXED(202);

    // Dpad
    RSDK.SetSpriteAnimation(ModLevelSelect->aniFrames, 0, &ModLevelSelect->animator, false, 0);

    ModLevelSelect->animator.frameID = ControllerInfo->keyUp.down ? LS_DPAD_UP_PRESSED : LS_DPAD_UP;
    RSDK.DrawSprite(&ModLevelSelect->animator, &drawPos, true);

    ModLevelSelect->animator.frameID = ControllerInfo->keyDown.down ? LS_DPAD_DOWN_PRESSED : LS_DPAD_DOWN;
    RSDK.DrawSprite(&ModLevelSelect->animator, &drawPos, true);

    ModLevelSelect->animator.frameID = ControllerInfo->keyLeft.down ? LS_DPAD_LEFT_PRESSED : LS_DPAD_LEFT;
    RSDK.DrawSprite(&ModLevelSelect->animator, &drawPos, true);

    ModLevelSelect->animator.frameID = ControllerInfo->keyRight.down ? LS_DPAD_RIGHT_PRESSED : LS_DPAD_RIGHT;
    RSDK.DrawSprite(&ModLevelSelect->animator, &drawPos, true);

    // Go/Start button
    drawPos.x = TO_FIXED(ScreenInfo->size.x - 38);

    RSDK.SetSpriteAnimation(ModLevelSelect->aniFrames, 1, &ModLevelSelect->animator, false, 0);

    // sound test
    if (self->labelID >= self->labelCount - 1) {
        if (ModLevelSelect->pressed)
            ModLevelSelect->animator.frameID = BUTTON_PLAY_DOWN;
        else
            ModLevelSelect->animator.frameID = BUTTON_PLAY;

    }
    // stages
    else {
        if (ModLevelSelect->pressed)
            ModLevelSelect->animator.frameID = BUTTON_GO_DOWN;
        else
            ModLevelSelect->animator.frameID = BUTTON_GO;
    }

    RSDK.DrawSprite(&ModLevelSelect->animator, &drawPos, true);
    //

    self->alpha     = prevInfo[0];
    self->inkEffect = prevInfo[1];
    RSDK.SetPaletteEntry(0, 82, prevInfo[2]);

    Mod.Super(LevelSelect->classID, SUPER_DRAW, NULL);
}

void LevelSelect_Create(void *data) {
    RSDK.SetSpriteAnimation(ModLevelSelect->aniFrames, 0, &ModLevelSelect->animator, true, 0);
    Mod.Super(LevelSelect->classID, SUPER_CREATE, data);
}

void LevelSelect_StageLoad(void) {
    ModLevelSelect->aniFrames = RSDK.LoadSpriteAnimation("LSelect/LSelect_TouchEx.bin", SCOPE_STAGE);
    Mod.Super(LevelSelect->classID, SUPER_STAGELOAD, NULL);
}

void LevelSelect_StaticLoad(ObjectLevelSelect *sVars)
{
    int32 bgAniDurationTable[]     = { 240, 3, 3, 3 };
    int32 cheat_RickyMode[]        = { 1, 9, 7, 9, 0, 8, 1, 1, 255 };
    int32 cheat_AllEmeralds[]      = { 4, 1, 2, 6, 255 };
    int32 cheat_MaxContinues[]     = { 1, 9, 9, 2, 1, 1, 2, 4, 255 };
    int32 cheat_SwapGameMode[]     = { 2, 0, 1, 8, 0, 6, 2, 3, 255 };
    int32 cheat_UnlockAllMedals[]  = { 1, 9, 8, 9, 0, 5, 0, 1, 255 };
    int32 cheat_SuperDash[]        = { 2, 0, 1, 7, 0, 8, 1, 5, 255 };
    int32 cheat_MaxControl[]       = { 9, 0, 0, 1, 255 };
    int32 cheat_ToggleSuperMusic[] = { 6, 2, 1, 4, 255, 0, 0, 0, 0 };

    memcpy(&sVars->bgAniDurationTable, bgAniDurationTable, sizeof(bgAniDurationTable));
    memcpy(&sVars->cheat_RickyMode, cheat_RickyMode, sizeof(cheat_RickyMode));
    memcpy(&sVars->cheat_AllEmeralds, cheat_AllEmeralds, sizeof(cheat_AllEmeralds));
    memcpy(&sVars->cheat_MaxContinues, cheat_MaxContinues, sizeof(cheat_MaxContinues));
    memcpy(&sVars->cheat_SwapGameMode, cheat_SwapGameMode, sizeof(cheat_SwapGameMode));
    memcpy(&sVars->cheat_UnlockAllMedals, cheat_UnlockAllMedals, sizeof(cheat_UnlockAllMedals));
    memcpy(&sVars->cheat_SuperDash, cheat_SuperDash, sizeof(cheat_SuperDash));
    memcpy(&sVars->cheat_MaxControl, cheat_MaxControl, sizeof(cheat_MaxControl));
    memcpy(&sVars->cheat_ToggleSuperMusic, cheat_ToggleSuperMusic, sizeof(cheat_ToggleSuperMusic));

    sVars->bgAniDuration = 240;

    /*
    sVars->sfxFail.Init();
    sVars->sfxRing.Init();
    sVars->sfxEmerald.Init();
    sVars->sfxContinue.Init();
    sVars->sfxMedalCaught.Init();

    sVars->checkCheatActivated[0] = LevelSelect::Cheat_RickyMode;
    // sVars->checkCheatActivated[1] = sub_140201490;
    sVars->checkCheatActivated[2] = LevelSelect::Cheat_MaxContinues;
    sVars->checkCheatActivated[3] = LevelSelect::Cheat_SuperDash;
    sVars->checkCheatActivated[4] = LevelSelect::Cheat_SuperMusic;
    sVars->checkCheatActivated[5] = LevelSelect::Cheat_VSPhysics;
    // sVars->checkCheatActivated[6] = LevelSelect::Cheat_SpriteStyle;
    sVars->checkCheatActivated[7] = LevelSelect::Cheat_DebugMode;
    sVars->checkCheatActivated[8] = LevelSelect::Cheat_CameraTracking;
    // sVars->checkCheatActivated[9] = nullsub_1;
    sVars->checkCheatActivated[10] = LevelSelect::Cheat_PenPenMode;
    sVars->checkCheatActivated[11] = LevelSelect::Cheat_RandomItems;
    sVars->checkCheatActivated[12] = LevelSelect::Cheat_BlueShieldMode;
    sVars->checkCheatActivated[13] = LevelSelect::Cheat_Peelout;
    sVars->checkCheatActivated[14] = LevelSelect::Cheat_BananaMode;
    sVars->checkCheatActivated[15] = LevelSelect::Cheat_NoItems;
    */
}