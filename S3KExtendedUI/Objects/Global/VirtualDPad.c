#include "../../Include.h"

// this is technically not an object, but thats fine :)

str_VirtualDPad VirtualDPad;

// ----------------------
// Standard Entity Events
// ----------------------

void VirtualDPad_Draw(void) {
    int32 prevAlpha = VirtualDPad.parent->alpha;
    int32 prevInk   = VirtualDPad.parent->inkEffect;

    VirtualDPad.parent->alpha     = VirtualDPad.fade;
    VirtualDPad.parent->inkEffect = INK_ALPHA;

    RSDK.SetActivePalette(7, 0, 255);
    color colorStore[59];
    for (int32 count = 0; count < 58; ++count) colorStore[count] = RSDK.GetPaletteEntry(7, count);

    RSDKControllerState *controller = &ControllerInfo[CONT_P1];

    Vector2 dpadPos;
    dpadPos.x = VirtualDPad.DPadXPos;
    dpadPos.y = 160 << 16;

    Vector2 buttonAPos;
    buttonAPos.x       = VirtualDPad.AButtonXPos;
    buttonAPos.y       = 176 << 16;

    int32 pauseX =
        TO_FIXED(ScreenInfo->size.x - 85); // S3K_SS_Player::sVars ? TO_FIXED(screenInfo->center.x - 8) : TO_FIXED(screenInfo->size.x - 85);
    Vector2 pausePos = { pauseX, TO_FIXED(8) };

    // set our custom palette entries
    VirtualDPad_InitPalette();

    // if we aren't paused, and player 1 has control, draw as normal
    if (SceneInfo->state < ENGINESTATE_FROZEN && !VirtualDPad.nullInputState) {

        if (VirtualDPad.fade < cfg.touchAlpha) { // fading in
            VirtualDPad.fade += 4;
            VirtualDPad.pauseFade = VirtualDPad.fade << 1;
        }

        VirtualDPad.animator.frameID = DPAD_BASE;
        RSDK.DrawSprite(&VirtualDPad.animator, &dpadPos, true);

        VirtualDPad.animator.frameID = controller->keyUp.down ? DPAD_UP_PRESSED : DPAD_UP;
        RSDK.DrawSprite(&VirtualDPad.animator, &dpadPos, true);

        VirtualDPad.animator.frameID = controller->keyDown.down ? DPAD_DOWN_PRESSED : DPAD_DOWN;
        RSDK.DrawSprite(&VirtualDPad.animator, &dpadPos, true);

        VirtualDPad.animator.frameID = controller->keyLeft.down ? DPAD_LEFT_PRESSED : DPAD_LEFT;
        RSDK.DrawSprite(&VirtualDPad.animator, &dpadPos, true);

        VirtualDPad.animator.frameID = controller->keyRight.down ? DPAD_RIGHT_PRESSED : DPAD_RIGHT;
        RSDK.DrawSprite(&VirtualDPad.animator, &dpadPos, true);

        int32 jumpHold               = controller->keyA.down || controller->keyB.down || controller->keyC.down || controller->keyX.down;
        VirtualDPad.animator.frameID = jumpHold ? DPAD_BUTTON_A_PRESSED : DPAD_BUTTON_A;
        RSDK.DrawSprite(&VirtualDPad.animator, &buttonAPos, true);
    } else {

        if (VirtualDPad.fade > 0) { // fading out
            VirtualDPad.fade -= 4;
            VirtualDPad.pauseFade -= 8;
        }

        // this draws the entire dpad
        for (int32 s = 0; s <= 4; ++s) {
            VirtualDPad.animator.frameID = s;
            RSDK.DrawSprite(&VirtualDPad.animator, &dpadPos, true);
        }

        VirtualDPad.animator.frameID = DPAD_BUTTON_A;
        RSDK.DrawSprite(&VirtualDPad.animator, &buttonAPos, true);
    }

    // draw the pause button
    VirtualDPad.parent->alpha    = VirtualDPad.pauseFade < 256 ? VirtualDPad.pauseFade : 256;
    VirtualDPad.animator.frameID = DPAD_BUTTON_PAUSE;
    RSDK.DrawSprite(&VirtualDPad.animator, &pausePos, true);

    for (int32 count = 0; count < 58; ++count) RSDK.SetPaletteEntry(7, count, colorStore[count]);
    RSDK.SetActivePalette(0, 0, 255);

    VirtualDPad.parent->alpha     = prevAlpha;
    VirtualDPad.parent->inkEffect = prevInk;
}

void VirtualDPad_Create(void *data) {
    VirtualDPad.parent = (Entity *)data;

    VirtualDPad.fade        = 0;
    VirtualDPad.pauseFade   = 0;
    VirtualDPad.pauseXPos   = ScreenInfo->size.x - 68;
    VirtualDPad.AButtonXPos = ScreenInfo->size.x - 61 << 16;
    VirtualDPad.DPadXPos    = 16 << 16; // nice
    cfg.dpadX               = 48;

    RSDK.SetSpriteAnimation(VirtualDPad.aniFrames, 0, &VirtualDPad.animator, true, 0);
}

void VirtualDPad_StageLoad(void) { VirtualDPad.aniFrames = RSDK.LoadSpriteAnimation("3K_Global/TouchControls.bin", SCOPE_STAGE); }

// ----------------------
// Extra Entity Functions
// ----------------------

void VirtualDPad_InitPalette(void) {
    // CD Colors
    RSDK.SetPaletteEntry(7, 6, 0xE0E0E0);
    RSDK.SetPaletteEntry(7, 7, 0xA0A0A0);
    RSDK.SetPaletteEntry(7, 8, 0x808080);
    RSDK.SetPaletteEntry(7, 9, 0x404040);
    RSDK.SetPaletteEntry(7, 11, 0xA06040);
    RSDK.SetPaletteEntry(7, 15, 0xE0E000);
    RSDK.SetPaletteEntry(7, 43, 0x002020);
    RSDK.SetPaletteEntry(7, 44, 0x204040);
    RSDK.SetPaletteEntry(7, 45, 0x406060);
    RSDK.SetPaletteEntry(7, 58, 0xE0A000);

    /*
    // Mania Colors
    RSDK.SetPaletteEntry(7, 6, 0xE0E0E0);
    RSDK.SetPaletteEntry(7, 7, 0xA0A0A0);
    RSDK.SetPaletteEntry(7, 8, 0x587090);
    RSDK.SetPaletteEntry(7, 9, 0x282028);
    RSDK.SetPaletteEntry(7, 11, 0xA06040);
    RSDK.SetPaletteEntry(7, 15, 0xE0E000);
    RSDK.SetPaletteEntry(7, 43, 0x000000);
    RSDK.SetPaletteEntry(7, 44, 0x282028);
    RSDK.SetPaletteEntry(7, 45, 0x484868);
    RSDK.SetPaletteEntry(7, 58, 0xE0A000);
    */
}

void VirtualDPad_HandleInput(int32 controllerID, int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy) {
    if (controllerID < PLAYER_COUNT) {
        RSDKControllerState *controller = &ControllerInfo[controllerID];

        // this function call handles the dpad part of our touch controls
        int32 result = TouchHelpers_CheckTouchRect(0, 96, ScreenInfo->center.x, ScreenInfo->size.y, NULL, NULL);

        if (result > -1) { // if it returns a value over -1 (if we're actually touching something), continue

            int32 touchX = (int32)(TouchInfo->x[result] * ScreenInfo->size.x) - 48;  // 48 here is the dpad's x position, move to options
            int32 touchY = (int32)(TouchInfo->y[result] * ScreenInfo->size.y) - 192; // 192 here is the dpad's y position, move to options

            RSDK.ATan2(touchX, touchY);

            // I think there's a problem with this, it might not work near the bottom of the screen? check v4 player script
            switch (((RSDK.ATan2(touchX, touchY) + 32) & 255) >> 6) {
                case 0: controller->keyRight.down = true; break;

                case 1: controller->keyDown.down = true; break;

                case 2: controller->keyLeft.down = true; break;

                case 3: controller->keyUp.down = true; break;
            }
        }

        // check if we're touching the jump region
        if (TouchHelpers_CheckTouchRect(ScreenInfo->center.x, 96, ScreenInfo->size.x, 240, NULL, NULL) >= 0) {
            ControllerInfo->keyA.down |= true;
            controller->keyA.down = true; // do the thing
            VirtualDPad.isJumpHeld = true;
        }

        if (!VirtualDPad.touchJump && VirtualDPad.isJumpHeld) { // check if we don't currently have our keyA button held, but we'd like to do that
            ControllerInfo->keyA.press |= ControllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }

        VirtualDPad.touchJump = controller->keyA.down; // initialize our touchJump variable with a KeyA.down check

        bool32 touchedDebug = false;
        if (globals->medalMods == MEDAL_DEBUGMODE) {

            if (TouchHelpers_CheckTouchRect(0, 0, 112, 56, NULL, NULL) > -1) {
                ControllerInfo->keyX.down |= true;
                controller->keyX.down = true;
                touchedDebug          = true;
            }

            if (VirtualDPad.touchDebug == false) {
                ControllerInfo->keyX.press |= ControllerInfo->keyX.down;
                controller->keyX.press |= controller->keyX.down;
            }

            VirtualDPad.touchDebug = controller->keyX.down;
        }

        if (TouchHelpers_CheckTouchRect(x1, 0, x2, y2, fx, fy) > -1)
            controller->keyStart.press = true;
    }
}