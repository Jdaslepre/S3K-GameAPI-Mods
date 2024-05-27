#include "../../Include.h"

ObjectTitleSeq *TitleSeq;

void TitleSeq_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(TitleSeq);

    // MOD_REGISTER_OBJ_OVERLOAD(TitleSeq, NULL, NULL, NULL, NULL, TitleSeq_Create, NULL, NULL, NULL, NULL);
}

// ----------------------
// Standard Entity Events
// ----------------------

void TitleSeq_Create(void *data) {
    RSDK_THIS(TitleSeq);

    Mod.Super(TitleSeq->classID, SUPER_CREATE, data);
}