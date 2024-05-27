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

// Menu
#include "Objects/Menu/LevelSelect.h"
#include "Objects/Menu/S3K_MenuSetup.h"
#include "Objects/Menu/S3K_SaveMenu.h"

// Helpers
#include "Objects/Helpers/TouchHelpers.h"

// Global
#include "Objects/Global/HUD.h"
#include "Objects/Global/PauseMenu.h"
#include "Objects/Global/Player.h"
#include "Objects/Global/VirtualDPad.h"

// Special
#include "Objects/Special/S3K_SS_HUD.h"
#include "Objects/Special/S3K_SS_Player.h"

// Title
#include "Objects/Title/TitleElement.h"
#include "Objects/Title/TitleSeq.h"

#endif // !INCLUDE_H