#ifndef OBJ_HUD_H
#define OBJ_HUD_H

#include "../../include.h"

typedef struct {
    RSDK_OBJECT

} ObjectHUD;

typedef struct {
    RSDK_ENTITY
    ext_StateMachine state;
    Vector2 scorePos;
    Vector2 timePos;
    Vector2 ringsPos;
    Vector2 lifePos;
} EntityHUD;

// Object Struct
extern ObjectHUD *HUD;

// Standard Entity Events
void HUD_Update(void);
void HUD_LateUpdate(void);
void HUD_StaticUpdate(void);
void HUD_Draw(void);
void HUD_Create(void *data);
void HUD_StageLoad(void);

// Extra Entity Functions
void HUD_Init(void);
EXTERNDEF(int32 (*HUD_CharacterIndexFromID)(int32 characterID));
EXTERNDEF(void (*HUD_DrawNumbersBase10)(Animator *animator, Vector2 *drawPos, int32 value, int32 digitCount));
EXTERNDEF(void (*HUD_DrawNumbersBase16)(EntityHUD *entity, Vector2 *drawPos, int32 value));

#endif //! OBJ_HUD_H
