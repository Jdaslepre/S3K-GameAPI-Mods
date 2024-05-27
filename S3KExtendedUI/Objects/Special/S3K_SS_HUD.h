#ifndef OBJ_S3K_SS_HUD_H
#define OBJ_S3K_SS_HUD_H

#include "../../include.h"

typedef struct {
    RSDK_OBJECT

} ObjectS3K_SS_HUD;

typedef struct {
    RSDK_ENTITY

} EntityS3K_SS_HUD;

// Object Struct
extern ObjectS3K_SS_HUD *S3K_SS_HUD;

// Standard Entity Events
void S3K_SS_HUD_Update(void);
void S3K_SS_HUD_LateUpdate(void);
void S3K_SS_HUD_StaticUpdate(void);
void S3K_SS_HUD_Draw(void);
void S3K_SS_HUD_Create(void *data);
void S3K_SS_HUD_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void S3K_SS_HUD_EditorDraw(void);
void S3K_SS_HUD_EditorLoad(void);
#endif
void S3K_SS_HUD_Serialize(void);

void S3K_SS_HUD_Init(void);

#endif //! OBJ_S3K_SS_HUD_H
