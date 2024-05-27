#ifndef OBJ_LEVELSELECT_H
#define OBJ_LEVELSELECT_H

#include "../../include.h"

typedef enum {
    LS_DPAD_UP,
    LS_DPAD_UP_PRESSED,
    LS_DPAD_DOWN,
    LS_DPAD_DOWN_PRESSED,
    LS_DPAD_LEFT,
    LS_DPAD_LEFT_PRESSED,
    LS_DPAD_RIGHT,
    LS_DPAD_RIGHT_PRESSED,
} LSelect_DpadFrameIDs;

typedef enum {
    BUTTON_GO,
    BUTTON_PLAY,
    BUTTON_GO_DOWN,
    BUTTON_PLAY_DOWN,
} LSelect_ButtonFrameIDs;

typedef struct {
    RSDK_OBJECT
    int32 bgAniDuration;
    int32 bgAniDurationTable[4];
    int32 cheat_RickyMode[9];
    int32 cheat_AllEmeralds[5];
    int32 cheat_MaxContinues[9];
    int32 cheat_SwapGameMode[9];
    int32 cheat_UnlockAllMedals[9];
    int32 cheat_SuperDash[9];
    int32 cheat_MaxControl[5];
    int32 cheat_ToggleSuperMusic[9];
    int32 bgAniFrame;
    int32 startMusicID;
    int32 soundTestMax;
    uint16 sfxFail;
    uint16 sfxRing;
    uint16 sfxEmerald;
    uint16 sfxContinue;
    uint16 sfxMedalCaught;
    uint16 sfxHotlineBusy;
    uint16 sfxLoseRings;
    int32 *cheatCodePtrs[8];
    int32 cheatCodePos[8];
    void (*checkCheatActivated[8])();
} ObjectLevelSelect;

typedef struct {
    RSDK_OBJECT
    uint16 aniFrames;
    Animator animator;
    bool32 pressed;
    bool32 pressedLR;
} ModObjectLevelSelect;

// Entity Class
typedef struct {
    RSDK_ENTITY
    ext_StateMachine state;
    ext_StateMachine stateDraw;
    int32 timer;
    int32 labelID;
    int32 soundTestID;
    int32 leaderCharacterID;
    int32 sidekickCharacterID;
    /*UIText*/ void *zoneNameLabels[64];
    /*UIText*/ void *stageIDLabels[64];
    /*UIText*/ void *soundTestLabel;
    /*UIPicture*/ void *zoneIcon;
    /*UIPicture*/ void *player1Icon;
    /*UIPicture*/ void *player2Icon;
    /*UIText*/ void *pinballLabel;
    int32 labelCount;
    int32 offsetUFO;
    int32 offsetBSS;
    int32 unused1;
    int32 unused2;
    int32 unused3;
    int32 unused4;
} EntityLevelSelect;

// Object Struct
extern ObjectLevelSelect *LevelSelect;
extern ModObjectLevelSelect *ModLevelSelect;

// Standard Entity Events
void LevelSelect_Draw(void);
void LevelSelect_Create(void *data);
void LevelSelect_StageLoad(void);
void LevelSelect_StaticLoad(ObjectLevelSelect *sVars);

EXTERNDEF(void(*LevelSelect_State_Navigate));
bool32 LevelSelect_State_Navigate_Hook(bool32 skippedState);

void LevelSelect_Init(void);

#endif //! OBJ_LEVELSELECT_H
