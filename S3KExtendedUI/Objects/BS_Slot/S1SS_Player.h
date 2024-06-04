#ifndef OBJ_S1SS_PLAYER_H
#define OBJ_S1SS_PLAYER_H

#include "../../include.h"

typedef struct {
    RSDK_OBJECT

} ObjectS1SS_Player;

typedef struct {
    RSDK_ENTITY
    int32 rings;
    int32 lives;
    int32 score;
    int32 ringExtraLife;
    int32 score1UP;
    bool32 hyperRing;
    uint8 shield;
    uint16 playerID;
    uint8 gap7C[4];
    ext_StateMachine state;
    void *camera;
    Animator animator;
    Animator tailAnimator;
    int32 tailRotation;
    int32 tailDirection;
    uint16 aniFrames;
    uint8 gapD8[2];
    int32 characterID;
    uint8 gapE8[16];
    ext_StateMachine stateInput;
    uint8 controllerID;
    char paddings[7];
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    bool32 jumpHold;
    int32 unkn128;
    int32 gravity;
    Vector2 worldVelocity;
    Vector2 moveVelocity;
    int32 moveSpeed;
    bool32 isGhost;
    uint8 padding[96];
    bool32 va8;
    uint8 padding2[20];
    int32 rotateBlockTimer;
    int32 upDownBlockTimer;
    uint16 animationSpeed;
    int32 v1cc;
    int32 v1d0;
    int32 v1d4;
} EntityS1SS_Player;

// Object Struct
extern ObjectS1SS_Player *S1SS_Player;

// Standard Entity Events
void S1SS_Player_Update(void);

// Extra Entity Functions
void S1SS_Player_Init(void);

#endif //! OBJ_PLAYER_H
