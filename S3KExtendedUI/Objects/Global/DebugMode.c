#include "../../Include.h"

ObjectDebugMode *DebugMode;

void DebugMode_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(DebugMode);

    /*
    if (!cfg.useTouch)
        return;

    MOD_REGISTER_OBJ_OVERLOAD(DebugMode, NULL, NULL, NULL, HUD_Draw, HUD_Create, HUD_StageLoad, NULL, NULL, NULL);
    */
}

// ----------------------
// Standard Entity Events
// ----------------------

void DebugMode_Draw(void) {
    Mod.Super(DebugMode->classID, SUPER_DRAW, NULL);
    //
}

void DebugMode_Create(void *data) {
    RSDK_THIS(DebugMode);
    // 
    Mod.Super(DebugMode->classID, SUPER_CREATE, data);
}

void DebugMode_StageLoad(void) {
    //
    Mod.Super(DebugMode->classID, SUPER_STAGELOAD, NULL);
}