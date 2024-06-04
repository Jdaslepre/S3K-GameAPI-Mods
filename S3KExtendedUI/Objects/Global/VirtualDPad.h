#ifndef OBJ_VIRTUALDPAD_H
#define OBJ_VIRTUALDPAD_H

#include "../../include.h"

enum VirtualDPad_FrameIDs {
    DPAD_BASE,
    DPAD_UP,
    DPAD_DOWN,
    DPAD_LEFT,
    DPAD_RIGHT,
    DPAD_UP_PRESSED,
    DPAD_DOWN_PRESSED,
    DPAD_LEFT_PRESSED,
    DPAD_RIGHT_PRESSED,
    DPAD_BUTTON_A,
    DPAD_BUTTON_A_PRESSED,
    DPAD_BUTTON_PAUSE,
};

typedef struct {
    RSDK_ENTITY
    Entity *parent;
    uint16 aniFrames;
    int32 fade;
    int32 pauseFade;
    int32 pauseXPos;
    int32 AButtonXPos;
    int32 DPadXPos;
    bool32 touchJump;
    bool32 touchDebug;
    bool32 isJumpHeld;
    Animator animator;
    int32 nullInputState;
} str_VirtualDPad;

extern str_VirtualDPad VirtualDPad;

// Standard Entity Events
void VirtualDPad_Update(void);
void VirtualDPad_LateUpdate(void);
void VirtualDPad_StaticUpdate(void);
void VirtualDPad_Draw(void);
void VirtualDPad_Create(void *data);
void VirtualDPad_StageLoad(void);
void VirtualDPad_EditorDraw(void);
void VirtualDPad_EditorLoad(void);
void VirtualDPad_Serialize(void);

void VirtualDPad_HandleInput(int32 controllerID, int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy);

#endif //! OBJ_VIRTUALDPAD_H
