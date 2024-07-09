#ifndef INCLUDE_H
#define INCLUDE_H

#include "GameAPI/Game.h"
#include "cfg.h"
#include "ext.h"

typedef struct {
    RSDK_OBJECT

} ObjectTitleCard;

typedef struct {
    RSDK_OBJECT

} EntityTitleCard;

EXTERNDEF(ObjectTitleCard *TitleCard);

typedef struct {
    RSDK_OBJECT

} ObjectCamera;

typedef struct {
    RSDK_OBJECT
    ext_StateMachine state;
    Entity *target;
    int32 screenID;
    Vector2 center;
    Vector2 targetMoveVel;
    Vector2 lastPos;
    Vector2 shakePos;
    Vector2 shakeDuration;
    Vector2 shakeTimer;
    Vector2 lookPos;
    Vector2 offset;
    bool32 disableYOffset;
    int32 centerY;
    int32 adjustY;
    int32 lerpPercent;
    int32 lerpSpeed;
    int32 lerpType;
    Vector2 endLerpPos;
    Vector2 startLerpPos;
    Vector2 unknown3;
    Vector2 boundsOffset;
    int32 boundsL;
    int32 boundsR;
    int32 boundsT;
    int32 boundsB;
    int32 field_10C;
} EntityCamera;

EXTERNDEF(ObjectCamera *Camera);

// BS_Slot
#include "Objects/BS_Slot/S1SS_Player.h"
#include "Objects/BS_Slot/SlotHUD.h"

// Global
#include "Objects/Global/DebugMode.h"
#include "Objects/Global/HUD.h"
#include "Objects/Global/PauseMenu.h"
#include "Objects/Global/Player.h"
#include "Objects/Global/VirtualDPad.h"

// Helpers
#include "Objects/Helpers/TouchHelpers.h"

// Menu
#include "Objects/Menu/LevelSelect.h"
#include "Objects/Menu/S3K_MenuSetup.h"
#include "Objects/Menu/S3K_SaveMenu.h"

// Special
#include "Objects/Special/S3K_SS_HUD.h"
#include "Objects/Special/S3K_SS_Player.h"

// Title
#include "Objects/Title/TitleElement.h"
#include "Objects/Title/TitleSeq.h"

#endif // !INCLUDE_H