#pragma once

struct ModConfig {
    float vDPadSize;
    float vDPadOpacity;
    RSDK::Vector2 moveDPadPos;
    RSDK::Vector2 jumpDPadPos;
};

extern ModConfig config;