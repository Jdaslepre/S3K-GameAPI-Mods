#ifndef CFG_H
#define CFG_H

#include "GameAPI/Game.h"

typedef struct {
    int32 useTouch;
    int32 touchAlpha;
    int32 dpadX;
} mcfg;

extern mcfg cfg;
mcfg cfg;

#endif