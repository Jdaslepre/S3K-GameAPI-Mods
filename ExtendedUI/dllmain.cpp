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
    GetPublicFuncAssign(LevelSelect_State_Navigate, NULL, "LevelSelect::State_Navigate");
    GetPublicFuncAssign(Player_Input_Gamepad, NULL, "Player::Input_Gamepad");
    GetPublicFuncAssign(S3K_SS_Player_Input_Gamepad, NULL, "S3K_SS_Player::Input_Gamepad");
    GetPublicFuncAssign(TitleSeq_State_WaitSEGA, NULL, "TitleSeq::State_WaitSEGA");
    GetPublicFuncAssign(TitleSeq_State_Animate, NULL, "TitleSeq::State_Animate");
    GetPublicFuncAssign(TitleSeq_State_WaitEx, NULL, "TitleSeq::State_WaitEx");

    config.usePathTracer = static_cast<bool*>(Mod::GetPublicFunction(0, "usePathTracer"));

    // --------------------
    // Set Public Functions
    // --------------------

    // Add a variable that allows other mods to detect if touch controls are enabled
    // this should be fine to do i think...
    Mod::AddPublicFunction("useTouchControls", INT_TO_VOID(config.useTouchControls));

    // --------------------
    // Register State Hooks
    // --------------------

    Mod::RegisterStateHook(LevelSelect_State_Navigate, LevelSelect_State_Navigate_Hook, true);
    Mod::RegisterStateHook(Player_Input_Gamepad, Player_Input_Gamepad_Hook, true);
    Mod::RegisterStateHook(S3K_SS_Player_Input_Gamepad, S3K_SS_Player_Input_Gamepad_Hook, true);
    Mod::RegisterStateHook(TitleSeq_State_WaitSEGA, TitleSeq_State_WaitSEGA_Hook, true);
    Mod::RegisterStateHook(TitleSeq_State_Animate, TitleSeq_CheckSkip, true);
    Mod::RegisterStateHook(TitleSeq_State_WaitEx, TitleSeq_CheckSkip, true);

    return true;
}
}
#endif