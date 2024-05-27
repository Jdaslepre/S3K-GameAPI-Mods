#ifndef OBJ_S3K_SAVEMENU_H
#define OBJ_S3K_SAVEMENU_H

#include "../../include.h"

typedef struct {
    RSDK_OBJECT
    uint16 sfxButton;
    uint16 sfxSlot;
    uint16 sfxBumper;
    uint16 sfxWarp;
    int32 fl_c;
    int32 fl_10;
    uint8 deletingSave;
    uint8 transitionScene;
    uint8 fl_16;
    uint8 pad[3];
    uint8 fl_1a;
} ObjectS3K_SaveMenu;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Animator animator;
    // Back button variables
    int32 backAlpha;
    uint8 backActionPending;
    uint8 backPrevTouch;
} ModObjectS3K_SaveMenu;

// Entity Class
typedef struct {
    RSDK_ENTITY
    ext_StateMachine state;
    ext_StateMachine stateDraw;
    uint16 fade;
    uint8 gap80[4];
    Animator dataSelectAnimator;
    Animator animator;
    int32 dwordC8;
    uint16 saveSlotSlot;
    String dataSelectString;
} EntityS3K_SaveMenu;

// Object Struct
extern ObjectS3K_SaveMenu *S3K_SaveMenu;
extern ModObjectS3K_SaveMenu *ModS3K_SaveMenu;

// Standard Entity Events
void S3K_SaveMenu_StaticUpdate(void);
void S3K_SaveMenu_Draw(void);
void S3K_SaveMenu_Create(void *data);
void S3K_SaveMenu_StageLoad(void);

void S3K_SaveMenu_Init(void);
void S3K_SaveMenu_BackButton(void);

#endif //! OBJ_S3K_SAVEMENU_H
