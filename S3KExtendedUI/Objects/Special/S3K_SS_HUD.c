#include "../../Include.h"

ObjectS3K_SS_HUD *S3K_SS_HUD;

void S3K_SS_HUD_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(S3K_SS_HUD);

    if (!cfg.useTouch)
        return;

    MOD_REGISTER_OBJ_OVERLOAD(S3K_SS_HUD, NULL, NULL, NULL, S3K_SS_HUD_Draw, S3K_SS_HUD_Create, S3K_SS_HUD_StageLoad, NULL, NULL, NULL);
}

// ----------------------
// Standard Entity Events
// ----------------------

void S3K_SS_HUD_Draw(void) {
    Mod.Super(S3K_SS_HUD->classID, SUPER_DRAW, NULL);
    VirtualDPad_Draw();
}

void S3K_SS_HUD_Create(void *data) {
    RSDK_THIS(S3K_SS_HUD);

    VirtualDPad_Create(self);

    Mod.Super(S3K_SS_HUD->classID, SUPER_CREATE, data);
}

void S3K_SS_HUD_StageLoad(void) {
    VirtualDPad_StageLoad();
    Mod.Super(S3K_SS_HUD->classID, SUPER_STAGELOAD, NULL);
}