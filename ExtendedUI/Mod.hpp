#pragma once
#include "GameAPI/Game.hpp"
#include "cfg.hpp"
#include "GameAPIExtensions.hpp"

#if RETRO_USE_MOD_LOADER
extern "C" {
DLLExport bool32 LinkModLogic(RSDK::EngineInfo *info, const char *modID);
}
#endif

// ------------
// Game Objects
// ------------

// Forward Declarations
namespace GameLogic {

RSDK_TYPEDEF(Camera);
RSDK_TYPEDEF(DebugMode);
RSDK_TYPEDEF(HUD);
RSDK_TYPEDEF(Player);
RSDK_TYPEDEF(S1SS_Player);
RSDK_TYPEDEF(S3K_SS_HUD);
RSDK_TYPEDEF(S3K_SS_Player);
RSDK_TYPEDEF(SlotHUD);
RSDK_TYPEDEF(Touch);
RSDK_TYPEDEF(TitleElement);

} // namespace GameLogic

// Helpers
#include "Touch.hpp"

#include "Objects/Camera.hpp"
#include "Objects/DebugMode.hpp"
#include "Objects/HUD.hpp"
#include "Objects/Player.hpp"
#include "Objects/S1SS_Player.hpp"
#include "Objects/S3K_SS_HUD.hpp"
#include "Objects/S3K_SS_Player.hpp"
#include "Objects/SlotHUD.hpp"

// --------------
// Misc Variables
// --------------

static bool32 *usePathTracer;