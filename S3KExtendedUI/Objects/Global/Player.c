#include "../../Include.h"

ObjectPlayer *Player;

void Player_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(Player);

    Player_Input_Gamepad = Mod.GetPublicFunction(NULL, "Player::Input_Gamepad");
    Mod.RegisterStateHook(Player_Input_Gamepad, Player_Input_Gamepad_Hook, true);
}

// ----------------------
// Standard Entity Events
// ----------------------

bool32 Player_Input_Gamepad_Hook(bool32 skippedState) {
    RSDK_THIS(Player);

    if (cfg.useTouch && RSDK.GetEntitySlot(self) == SLOT_PLAYER1)
        VirtualDPad_HandleInput(self->controllerID, 240, NULL, ScreenInfo->size.x, 40, NULL, NULL);

    if (ControllerInfo[0].keyStart.press || UnknownInfo->pausePress) {
        if (SceneInfo->state == ENGINESTATE_REGULAR) {
            EntityPauseMenu *pauseMenu = RSDK_GET_ENTITY(SLOT_PAUSEMENU, PauseMenu);
            bool32 allowPause          = true;
            /*
            if (ActClear && ActClear->actClearActive)
                allowPause = false;
            */

            if (!RSDK.GetEntityCount(TitleCard->classID, false) && !pauseMenu->classID && allowPause) {
                RSDK.ResetEntitySlot(SLOT_PAUSEMENU, PauseMenu->classID, NULL);
                pauseMenu->triggerPlayer = self->playerID;

                if (globals->gameMode == MODE_COMPETITION)
                    pauseMenu->disableRestart = true;
            }
        }
    }

    return false;
}