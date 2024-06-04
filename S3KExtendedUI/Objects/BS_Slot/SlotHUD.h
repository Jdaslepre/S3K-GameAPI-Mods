#ifndef OBJ_SLOTHUD_H
#define OBJ_SLOTHUD_H

#include "../../include.h"

typedef struct {
    RSDK_OBJECT

} ObjectSlotHUD;

typedef struct {
    RSDK_ENTITY
    ext_StateMachine state;
    Vector2 ringsPos;
    Vector2 lifePos;
} EntitySlotHUD;

// Object Struct
extern ObjectSlotHUD *SlotHUD;

// Standard Entity Events
void SlotHUD_Draw(void);
void SlotHUD_Create(void *data);
void SlotHUD_StageLoad(void);

// Extra Entity Functions
void SlotHUD_Init(void);

#endif //! OBJ_SLOTHUD_H
