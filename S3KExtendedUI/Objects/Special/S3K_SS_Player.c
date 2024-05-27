#include "../../Include.h"

ObjectS3K_SS_Player *S3K_SS_Player;

void S3K_SS_Player_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(S3K_SS_Player);

    S3K_SS_Player_Input_Gamepad = Mod.GetPublicFunction(NULL, "S3K_SS_Player::Input_Gamepad");
    Mod.RegisterStateHook(S3K_SS_Player_Input_Gamepad, S3K_SS_Player_Input_Gamepad_Hook, true);
}

// ----------------------
// Standard Entity Events
// ----------------------

bool32 S3K_SS_Player_Input_Gamepad_Hook(bool32 skippedState) {
    RSDK_THIS(S3K_SS_Player);

    if (cfg.useTouch && RSDK.GetEntitySlot(self) == SLOT_PLAYER1)
        VirtualDPad_HandleInput(self->controllerID, (ScreenInfo->center.x - 0x54), NULL, (ScreenInfo->center.x + 0x54), 40, NULL, NULL);

    if (ControllerInfo[0].keyStart.press || UnknownInfo->pausePress) {
        if (SceneInfo->state == ENGINESTATE_REGULAR) {
            EntityPauseMenu *pauseMenu = RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu);
            bool32 allowPause          = true;
            /*
            if (ActClear && ActClear->actClearActive)
                allowPause = false;
            */

            if (!pauseMenu->classID && allowPause) {
                RSDK.ResetEntitySlot(SLOT_PAUSEMENU, PauseMenu->classID, NULL);
                pauseMenu->triggerPlayer = RSDK.GetEntitySlot(self); // self->playerID;
            }
        }
    }

    return false;
}