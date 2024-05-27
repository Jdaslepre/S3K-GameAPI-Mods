#ifndef OBJ_S3K_MENUSETUP_H
#define OBJ_S3K_MENUSETUP_H

#include "../../include.h"

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    int16 unknown1;
    int32 stageID;
} ObjectS3K_MenuSetup;

// Entity Class
typedef struct {
    RSDK_ENTITY
    uint8 id;
    Vector2 size;
} EntityS3K_MenuSetup;

// Object Struct
extern ObjectS3K_MenuSetup *S3K_MenuSetup;

// Standard Entity Events
void S3K_MenuSetup_Update(void);
void S3K_MenuSetup_LateUpdate(void);
void S3K_MenuSetup_StaticUpdate(void);
void S3K_MenuSetup_Draw(void);
void S3K_MenuSetup_Create(void *data);
void S3K_MenuSetup_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void S3K_MenuSetup_EditorDraw(void);
void S3K_MenuSetup_EditorLoad(void);
#endif
void S3K_MenuSetup_Serialize(void);

void S3K_MenuSetup_Init(void);

#endif //! OBJ_S3K_MENUSETUP_H
