#pragma once
#include "Mod.hpp"

GlobalVariables *globals = nullptr;
ModConfig config;

using namespace RSDK;
using namespace GameLogic;

#if RETRO_USE_MOD_LOADER
extern "C" {
bool32 LinkModLogic(RSDK::EngineInfo *info, const char *modID) {
    InitModLogic(info, modID);

    // ---------------------
    // Link Global Variables
    // ---------------------

    globals = (GlobalVariables *)Mod::GetGlobals();

    // -------------------------
    // Mod Config Initialization
    // -------------------------

    config.vDPadSize     = Mod::Settings::GetFloat("", "Config:vDPadSize", 1.0);
    config.vDPadOpacity  = Mod::Settings::GetFloat("", "Config:vDPadOpacity", .625);
    config.moveDPadPos.x = Mod::Settings::GetInteger("", "Config:moveDPadPosX", 56);
    config.moveDPadPos.y = Mod::Settings::GetInteger("", "Config:moveDPadPosY", 184);
    config.jumpDPadPos.x = Mod::Settings::GetInteger("", "Config:jumpDPadPosX", -56);
    config.jumpDPadPos.y = Mod::Settings::GetInteger("", "Config:jumpDPadPosY", 188);

    Mod::Settings::SetFloat("Config:vDPadSize", config.vDPadSize);
    Mod::Settings::SetFloat("Config:vDPadOpacity", config.vDPadOpacity);
    Mod::Settings::SetInteger("Config:moveDPadPosX", config.moveDPadPos.x);
    Mod::Settings::SetInteger("Config:moveDPadPosY", config.moveDPadPos.y);
    Mod::Settings::SetInteger("Config:jumpDPadPosX", config.jumpDPadPos.x);
    Mod::Settings::SetInteger("Config:jumpDPadPosY", config.jumpDPadPos.y);
    Mod::Settings::SaveSettings();

    // --------------------
    // Get Public Functions
    // --------------------

    GetPublicFuncAssign(HUD_DrawNumbersBase10, NULL, "HUD::DrawNumbersBase10");
    GetPublicFuncAssign(HUD_DrawNumbersBase16, NULL, "HUD::DrawNumbersBase16");
    GetPublicFuncAssign(HUD_CharacterIndexFromID, NULL, "HUD::CharacterIndexFromID");
    GetPublicFuncAssign(Player_Input_Gamepad, NULL, "Player::Input_Gamepad");
    GetPublicFuncAssign(S3K_SS_Player_Input_Gamepad, NULL, "S3K_SS_Player::Input_Gamepad");

    usePathTracer = (bool32 *)Mod::GetPublicFunction(NULL, "usePathTracer");

    // --------------------
    // Set Public Functions
    // --------------------

    // Set a variable that allows other mods to detect if touch controls are enabled
    // this should be fine to do i think...
    // Mod::AddPublicFunction("useTouchControls", &config.useTouch);

    // --------------------
    // Register State Hooks
    // --------------------

    Mod::RegisterStateHook(Player_Input_Gamepad, Player_Input_Gamepad_Hook, true);
    Mod::RegisterStateHook(S3K_SS_Player_Input_Gamepad, S3K_SS_Player_Input_Gamepad_Hook, true);

    return true;
}
}
#endif