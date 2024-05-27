#ifndef OBJ_PLAYER_H
#define OBJ_PLAYER_H

#include "../../include.h"

typedef struct {
    RSDK_OBJECT

} ObjectPlayer;

typedef struct {
    RSDK_ENTITY
    uint8 pathTracer[112];
    int32 rings;
    int32 lives;
    int32 score;
    int32 ringExtraLife;
    int32 score1UP;
    bool32 hyperRing;
    uint8 shield;
    ext_StateMachine state;
    ext_StateMachine nextAirState;
    ext_StateMachine nextGroundState;
    ext_StateMachine stateGravity;
    void *camera;
    Animator animator;
    Animator tailAnimator;
    int32 minJogVelocity;
    int32 minRunVelocity;
    int32 minDashVelocity;
    int32 unused; // the only unused variable in the player struct, I cant find a ref to it anywhere so...
    int32 tailRotation;
    int32 tailDirection;
    uint16 aniFrames;
    uint16 tailFrames;
    uint16 animationReserve; // what anim to return to after SpringTwirl/SpringDiagonal has finished and the player is falling downwards
    uint16 playerID;
    Hitbox *outerbox;
    Hitbox *innerbox;
    int32 characterID;
    int32 hurtAirborneTimer; // I don't actually know what this is. it counts up when you are hit until you land, as well as hold up and down to move
                             // the camera.
    int32 timer;             // where player timer ACTUALLY is. this one is responsible for many things, such as: player idle animation.
    int32 abilityTimer;      // handles ability timers for certain things, spindash being one of them.
    int32 spindashCharge;    // handles the pitch of the spindash. note: it never goes down. why? i dunno.
    int32 abilityValue;
    int32 drownTimer;
    int32 invincibleTimer;
    int32 speedShoesTimer;
    int32 blinkTimer;
    int32 scrollDelay;
    int32 skidding;
    int32 pushing;
    int32 underwater;     // 0 = not in water, 1 = in palette water, else water entityID
    bool32 groundedStore; // prev frame's onGround value
    bool32 invertGravity; // technically not used, but it still has effects on the player's control if forced to 1 on cheat engine. comes from Mania's
                          // FBZ invert gravity sections?
    bool32 isChibi;       // This is still in Sonic 3. Wild.
    bool32 isTransforming;
    bool32 disableGravity;
    int32 superState;
    int32 superRingLossTimer;
    int32 superBlendAmount;
    int32 superBlendState;
    int32 superBlendTimer;
    uint8 superColorIndex;
    uint8 superColorCount;
    uint8 superTableIndex;
    bool32 sidekick;
    int32 scoreBonus;
    int32 jumpOffset;
    int32 collisionFlagH;
    int32 collisionFlagV;
    int32 topSpeed;
    int32 acceleration;
    int32 deceleration;
    int32 airAcceleration;
    int32 airDeceleration;
    int32 skidSpeed;
    int32 rollingFriction;
    int32 rollingDeceleration;
    int32 gravityStrength;
    int32 abilitySpeed;
    int32 jumpStrength;
    int32 jumpCap;
    uint32 flailing; // bitfield for flailing.
    int32 sensorX[5];
    int32 sensorY;
    Vector2 moveLayerPosition;
    Vector2 lastMoveLayerPosition;
    ext_StateMachine stateInputReplay;
    ext_StateMachine stateInput;
    int32 controllerID;
    // ....
} EntityPlayer;

// Object Struct
extern ObjectPlayer *Player;

// Standard Entity Events
EXTERNDEF(void(*Player_Input_Gamepad));
bool32 Player_Input_Gamepad_Hook(bool32 skippedState);

void Player_Draw(void);

void Player_Init(void);

#endif //! OBJ_PLAYER_H
