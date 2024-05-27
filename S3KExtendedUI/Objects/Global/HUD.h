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
void HUD_Init(void);

#endif //! OBJ_HUD_H
