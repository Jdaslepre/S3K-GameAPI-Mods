#ifndef OBJ_PAUSEMENU_H
#define OBJ_PAUSEMENU_H

#include "../../include.h"

// --------------
// Object Structs
// --------------

typedef struct {
    RSDK_OBJECT
} ObjectPauseMenu;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 sfxWoosh;
    uint16 sfxBleep;
    uint16 sfxAccept;
    bool32 activeChannels[CHANNEL_COUNT];
} ModObjectPauseMenu;

typedef struct {
    RSDK_ENTITY
    StateMachine(state);
    StateMachine(stateDraw);
    int32 timer;
    Animator animator;
    Animator selectionAnimator;
    RSDKControllerState *controller;
    int32 backgroundAlpha;
    Vector2 drawPos;
    Vector2 pauseBarPos;
    int32 spritePosX;
    int32 selectedButton;
    bool32 disableRestart;
    uint8 triggerPlayer;
    int32 timerThreshold;
    int32 pauseBarHeight;
} EntityPauseMenu;

extern ObjectPauseMenu *PauseMenu;
extern ModObjectPauseMenu *ModPauseMenu;

// ----------------------
// Standard Entity Events
// ----------------------

void PauseMenu_Update(void);
void PauseMenu_LateUpdate(void);
void PauseMenu_Draw(void);
void PauseMenu_Create(void *data);
void PauseMenu_StageLoad(void);

// ----------------------
// Extra Entity Functions
// ----------------------

void PauseMenu_Init(void);
void PauseMenu_DrawPauseRect(int32 y);
void PauseMenu_DrawSpikes(void);
void PauseMenu_PauseSound(void);
void PauseMenu_ResumeSound(void);
void PauseMenu_StopSound(void);

// -------------
// Object States
// -------------

void PauseMenu_State_StartPause(void);
void PauseMenu_State_SlideIn(void);
void PauseMenu_State_SpritesFadeIn(void);
void PauseMenu_State_Controls(void);
void PauseMenu_State_Confirmed(void);
void PauseMenu_State_ResumeGame(void);
void PauseMenu_State_ExitLevel(void);

// -----------
// Draw States
// -----------

void PauseMenu_Draw_Init(void);
void PauseMenu_Draw_Controls(void);
void PauseMenu_Draw_Confirmed(void);
void PauseMenu_Draw_ResumeGame(void);
void PauseMenu_Draw_ExitLevel(void);

#endif //! OBJ_PAUSEMENU_H
