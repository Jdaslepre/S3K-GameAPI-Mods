#include "include.h"

#if RETRO_USE_MOD_LOADER
DLLExport bool32 LinkModLogic(EngineInfo *info, const char *id);
#endif

void InitModAPI(void) {

    // -------------------------
    // Mod Config Initialization
    // -------------------------

    cfg.useTouch = Mod.GetSettingsBool("", "Config:Use Touch Controls", false);
    Mod.SetSettingsBool("Config:Use Touch Controls", cfg.useTouch);

    cfg.touchAlpha = Mod.GetSettingsInteger("", "Config:Touch Control Opacity (Default 160)", 160);
    Mod.SetSettingsInteger("Config:Touch Control Opacity (Default 160)", cfg.touchAlpha);

    Mod.SaveSettings();

    // ------------
    // Object Setup
    // ------------

    MOD_REGISTER_OBJECT_HOOK(TitleCard);
    
    // Global
    HUD_Init();
    PauseMenu_Init();
    Player_Init();

    // Menu
    LevelSelect_Init();
    S3K_MenuSetup_Init();
    S3K_SaveMenu_Init();

    // Special
    S3K_SS_HUD_Init();
    S3K_SS_Player_Init();

    // Title
    TitleElement_Init();
    TitleSeq_Init();
}

#if RETRO_USE_MOD_LOADER
#define ADD_PUBLIC_FUNC(func) Mod.AddPublicFunction(#func, (void *)(func))

void InitModAPI(void);

bool32 LinkModLogic(EngineInfo *info, const char *id) {
    LinkGameLogicDLL(info);

    globals = Mod.GetGlobals();

    modID = id;

    InitModAPI();

    return true;
}
#endif