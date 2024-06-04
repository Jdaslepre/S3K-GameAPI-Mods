#include "../../Include.h"

ObjectSlotHUD *SlotHUD;

void SlotHUD_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(SlotHUD);

    if (!cfg.useTouch)
        return;

    MOD_REGISTER_OBJ_OVERLOAD(SlotHUD, NULL, NULL, NULL, SlotHUD_Draw, SlotHUD_Create, SlotHUD_StageLoad, NULL, NULL, NULL);
}

// ----------------------
// Standard Entity Events
// ----------------------

void SlotHUD_Draw(void) {
    Mod.Super(SlotHUD->classID, SUPER_DRAW, NULL);
    VirtualDPad_Draw();
}

void SlotHUD_Create(void *data) {
    RSDK_THIS(SlotHUD);

    VirtualDPad_Create(self);
    Mod.Super(SlotHUD->classID, SUPER_CREATE, data);
    self->lifePos.x = TO_FIXED(ScreenInfo->size.x - 64);
    self->lifePos.y = 0x180000;
}

void SlotHUD_StageLoad(void) {
    VirtualDPad_StageLoad();
    Mod.Super(SlotHUD->classID, SUPER_STAGELOAD, NULL);
}