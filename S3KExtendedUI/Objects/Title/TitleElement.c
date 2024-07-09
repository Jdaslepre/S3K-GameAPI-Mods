#include "../../Include.h"

ObjectTitleElement *TitleElement;

void TitleElement_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(TitleElement);

    if (!cfg.useTouch)
        return;

    MOD_REGISTER_OBJ_OVERLOAD(TitleElement, NULL, NULL, NULL, NULL, TitleElement_Create, NULL, NULL, NULL, NULL);
}

// ----------------------
// Standard Entity Events
// ----------------------

void TitleElement_Create(void* data) {
    RSDK_THIS(TitleElement);

    Mod.Super(TitleElement->classID, SUPER_CREATE, data);

    if (self->type == ELEMENT_START)
        RSDK.SetSpriteAnimation(TitleElement->aniFrames, 5, &self->animator[0], true, 13);
}