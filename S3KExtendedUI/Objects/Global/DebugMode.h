#ifndef OBJ_DEBUGMODE_H
#define OBJ_DEBUGMODE_H

#include "../../include.h"

typedef struct {
    RSDK_OBJECT

} ObjectDebugMode;

typedef struct {
    RSDK_ENTITY

} EntityDebugMode;

// Object Struct
extern ObjectDebugMode *DebugMode;

// Standard Entity Events
void DebugMode_Update(void);
void DebugMode_LateUpdate(void);
void DebugMode_StaticUpdate(void);
void DebugMode_Draw(void);
void DebugMode_Create(void *data);
void DebugMode_StageLoad(void);
void DebugMode_Init(void);

#endif //! OBJ_DEBUGMODE_H
