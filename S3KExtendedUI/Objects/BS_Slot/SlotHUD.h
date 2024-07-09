#ifndef OBJ_SLOTHUD_H
#define OBJ_SLOTHUD_H

#include "../../include.h"

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    uint16 superButtonFrames; // this isn't actually used
    uint16 sfxClick;
    uint16 sfxStarpost;
    bool32 showTAPrompt;
    int32 screenBorderType[PLAYER_COUNT];
    int32 swapCooldown;
    int32 stockFlashTimers[PLAYER_COUNT];
} ObjectSlotHUD;

typedef struct {
    RSDK_ENTITY
    ext_StateMachine state;
    Vector2 ringsPos;
    Vector2 lifePos;
    int32 lifeFrameIDs[PLAYER_COUNT];
    int32 lives[PLAYER_COUNT];
    int32 field_a8;
    int32 field_ac;
    int32 ringFlashFrame;
    bool32 enableRingFlash;
    Animator hudElementsAnimator;
    Animator numbersAnimator;
    Animator hyperNumbersAnimator;
    Animator lifeIconAnimator;
    Animator lifeNamesAnimator;
    Animator lifeNumbersAnimator;
    Animator playerIDAnimator;
    Animator superIconAnimator;
    Animator superButtonAnimator;
    Animator thumbsUpIconAnimator;
    Animator thumbsUpButtonAnimator;
    Animator replayClapAnimator;
    Animator saveReplayButtonAnimator;
    uint8 extendedHUD;
} EntitySlotHUD;

// Object Struct
extern ObjectSlotHUD *SlotHUD;

// Standard Entity Events
void SlotHUD_Draw(void);
void SlotHUD_Create(void *data);
void SlotHUD_StageLoad(void);

// Extra Entity Functions
void SlotHUD_Init(void);
void SlotHUD_DrawMobile(void);

#endif //! OBJ_SLOTHUD_H
