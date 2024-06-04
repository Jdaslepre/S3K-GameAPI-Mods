#include "../../Include.h"

ObjectS1SS_Player *S1SS_Player;

void S1SS_Player_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(S1SS_Player);
    MOD_REGISTER_OBJ_OVERLOAD(S1SS_Player, S1SS_Player_Update, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
}

// ----------------------
// Standard Entity Events
// ----------------------

void S1SS_Player_Update(void) {
    RSDK_THIS(S1SS_Player);

    // S1SS_Player uses Player_Input_Gamepad which we've already
    // hooked - but due to S1SS_Player essentially overriding the
    // controls, we'll have to do this instead
    if (self->stateInput.state == Player_Input_Gamepad) {

        // if (cfg.useTouch && self->controllerID == CONT_P1)
           // VirtualDPad_HandleInput(self->controllerID, 240, NULL, ScreenInfo->size.x, 40, NULL, NULL);
        VirtualDPad_HandleInput(self->controllerID, 240, NULL, ScreenInfo->size.x, 40, NULL, NULL);
        if (ControllerInfo[CONT_ANY].keyStart.press || UnknownInfo->pausePress) {
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
    }

    Mod.Super(S1SS_Player->classID, SUPER_UPDATE, NULL);
}