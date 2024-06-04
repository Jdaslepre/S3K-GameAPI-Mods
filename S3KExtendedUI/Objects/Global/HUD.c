#include "../../Include.h"

ObjectHUD *HUD;

void HUD_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(HUD);

    if (!cfg.useTouch)
        return;

    MOD_REGISTER_OBJ_OVERLOAD(HUD, NULL, NULL, NULL, HUD_Draw, HUD_Create, HUD_StageLoad, NULL, NULL, NULL);
}

// ----------------------
// Standard Entity Events
// ----------------------

void HUD_Draw(void) {
    Mod.Super(HUD->classID, SUPER_DRAW, NULL);
    VirtualDPad_Draw();
}

void HUD_Create(void *data) {
    RSDK_THIS(HUD);

    VirtualDPad_Create(self);
    Mod.Super(HUD->classID, SUPER_CREATE, data);
    self->lifePos.x = TO_FIXED(ScreenInfo->size.x - 64);
    self->lifePos.y = 0x180000;
}

void HUD_StageLoad(void) {
    VirtualDPad_StageLoad();
    Mod.Super(HUD->classID, SUPER_STAGELOAD, NULL);
}