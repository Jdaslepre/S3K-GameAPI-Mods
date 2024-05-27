#ifndef OBJ_S3K_SS_PLAYER_H
#define OBJ_S3K_SS_PLAYER_H

#include "../../include.h"

typedef struct {
    RSDK_OBJECT

} ObjectS3K_SS_Player;

typedef struct {
    RSDK_ENTITY
    int32 gravityStrength;
    bool32 sidekick;
    ext_StateMachine stateInput;
    int32 controllerID;
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    bool32 jumpHold;
    Animator animator;
    Animator tailAnimator;
    uint16 aniFrames;
} EntityS3K_SS_Player;

// Object Struct
extern ObjectS3K_SS_Player *S3K_SS_Player;

// Standard Entity Events
EXTERNDEF(void(*S3K_SS_Player_Input_Gamepad));
bool32 S3K_SS_Player_Input_Gamepad_Hook(bool32 skippedState);

void S3K_SS_Player_Update(void);
void S3K_SS_Player_LateUpdate(void);
void S3K_SS_Player_StaticUpdate(void);
void S3K_SS_Player_Draw(void);
void S3K_SS_Player_Create(void *data);
void S3K_SS_Player_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void S3K_SS_Player_EditorDraw(void);
void S3K_SS_Player_EditorLoad(void);
#endif
void S3K_SS_Player_Serialize(void);

void S3K_SS_Player_Init(void);

#endif //! OBJ_S3K_SS_PLAYER_H
