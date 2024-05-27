#ifndef OBJ_TitleElement_H
#define OBJ_TitleElement_H

#include "../../include.h"

enum TitleElement_Types { ELEMENT_EMBLEM, ELEMENT_BANNER, ELEMENT_TORNADO, ELEMENT_COPYRIGHT, ELEMENT_START, ELEMENT_OPTION, ELEMENT_TYPECOUNT };

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
} ObjectTitleElement;

typedef struct {
    RSDK_ENTITY
    uint16 timer;
    ext_StateMachine state;
    Animator animator[3];
    uint8 type;
    Vector2 originPos;
    int32 osc;
    uint8 sub;
} EntityTitleElement;

// Object Struct
extern ObjectTitleElement *TitleElement;

// Standard Entity Events
void TitleElement_Update(void);
void TitleElement_LateUpdate(void);
void TitleElement_StaticUpdate(void);
void TitleElement_Draw(void);
void TitleElement_Create(void *data);
void TitleElement_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void TitleElement_EditorDraw(void);
void TitleElement_EditorLoad(void);
#endif
void TitleElement_Serialize(void);

void TitleElement_Init(void);

#endif //! OBJ_TitleElement_H
