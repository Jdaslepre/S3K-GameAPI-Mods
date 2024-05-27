#ifndef OBJ_TITLESEQ_H
#define OBJ_TITLESEQ_H

#include "../../include.h"

typedef struct {
    union {
        uint64 mask;
        uint8 codes[8];
    } input;
    bool32 active;
} CheatStatus;

typedef struct {
    RSDK_OBJECT
    uint16 sfxSega;
    uint16 sfxButton;
    uint16 sfxFail;
    uint16 sfxStart;
    uint16 sfxRing;
    uint16 unused;
    color colors[14];
    int32 timer;
    uint16 introLayerID;
    int8 sonicIntroFrameTimes[12];
    int32 option;
    bool32 blueSpheresEnabled;
    uint8 matchLevelSelect[8];
    uint8 matchUnknown[7];
    uint8 matchUnknown2[12];
    CheatStatus statusLevelSelect;
    CheatStatus statusUnknown;
    CheatStatus statusUnknown2;
    uint8 seqCountLevelSelect;
    uint8 seqCountUnknown;
    uint8 seqCountUnknown2;
} ObjectTitleSeq;

typedef struct {
    RSDK_ENTITY
    uint16 timer;
    ext_StateMachine state;
    Animator animator[3];
    uint8 type;
    Vector2 originPos;
    int32 osc;
    uint8 sub;
} EntityTitleSeq;

// Object Struct
extern ObjectTitleSeq *TitleSeq;

// Standard Entity Events
void TitleSeq_Update(void);
void TitleSeq_LateUpdate(void);
void TitleSeq_StaticUpdate(void);
void TitleSeq_Draw(void);
void TitleSeq_Create(void *data);
void TitleSeq_StageLoad(void);
#if GAME_INCLUDE_EDITOR
void TitleSeq_EditorDraw(void);
void TitleSeq_EditorLoad(void);
#endif
void TitleSeq_Serialize(void);

void TitleSeq_Init(void);

#endif //! OBJ_TITLESEQ_H
