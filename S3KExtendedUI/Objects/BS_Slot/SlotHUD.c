#include "../../Include.h"

ObjectSlotHUD *SlotHUD;

void SlotHUD_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(SlotHUD);

    if (!cfg.useTouch)
        return;

    MOD_REGISTER_OBJ_OVERLOAD(SlotHUD, NULL, NULL, NULL, SlotHUD_Draw, SlotHUD_Create, SlotHUD_StageLoad, NULL, NULL, NULL);
}

// ----------------------
// Standard Entity Events
// ----------------------

void SlotHUD_Draw(void) {
    Mod.Super(SlotHUD->classID, SUPER_DRAW, NULL);
    // SlotHUD_DrawMobile();
    VirtualDPad_Draw();
}

void SlotHUD_Create(void *data) {
    RSDK_THIS(SlotHUD);
    Mod.Super(SlotHUD->classID, SUPER_CREATE, data);

    if (!SceneInfo->inEditor) {
        VirtualDPad_Create(self);

        self->ringsPos.x = 0;
        self->ringsPos.y = 0;
        self->lifePos.x  = 0;  // TO_FIXED(ScreenInfo->size.x - 64);
        self->lifePos.y = TO_FIXED(8);

        // self->lifePos.x  = TO_FIXED(ScreenInfo->size.x - 64);
        // self->lifePos.y  = 0x180000;
    }
}

void SlotHUD_StageLoad(void) {
    Mod.Super(SlotHUD->classID, SUPER_STAGELOAD, NULL);
    VirtualDPad_StageLoad();
}

// ----------------------
// Extra Entity Functions
// ----------------------

void SlotHUD_DrawMobile(void) {
    RSDK_THIS(SlotHUD);

    EntityS1SS_Player *player = RSDK_GET_ENTITY(SceneInfo->currentScreenID, S1SS_Player);

    Vector2 drawPos;
    Vector2 ringsPos;
    ringsPos.x = self->ringsPos.x;
    ringsPos.y = self->ringsPos.y;

    Vector2 lifePos;
    lifePos.x = self->lifePos.x;
    lifePos.y = self->lifePos.y;

    self->ringFlashFrame = player->rings ? 0 : ((globals->persistentTimer >> 3) & 1);

    // Draw "Rings" Text
    self->hudElementsAnimator.frameID = self->ringFlashFrame + 3;
    RSDK.DrawSprite(&self->hudElementsAnimator, &ringsPos, true);

    // Draw Rings
    if (!self->enableRingFlash || globals->persistentTimer & 8) {
        self->numbersAnimator.frameID = 0;
        drawPos.x                     = ringsPos.x + (self->extendedHUD ? 0x630000 : 0x4B0000);
        drawPos.y                     = ringsPos.y + TO_FIXED(8); // TO_FIXED(((SpriteFrame*)self->numbersAnimator.frames[0]).height);

        if (player->hyperRing) {
            // HUD_DrawNumbersBase10(&self->hyperNumbersAnimator, &drawPos, player->rings, 0);
            drawPos.x -= 0x40000;
            self->hyperNumbersAnimator.frameID = 10;
            RSDK.DrawSprite(&self->hyperNumbersAnimator, &drawPos, true);
        } // else
          // HUD_DrawNumbersBase10(&self->numbersAnimator, &drawPos, player->rings, 0);
    }

    EntityS1SS_Player *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, S1SS_Player);

    // Draw Debug Info
    if (player1->classID == DebugMode->classID) {
        if (player->camera) {
            // Draw Camera YPos
            drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
            drawPos.y = 0x180000;
            // HUD::DrawNumbersBase16((HUD *)self, &drawPos, screenInfo[player->camera->screenID].position.y);

            // Draw Camera XPos
            drawPos.x -= 0x90000;
            // HUD_DrawNumbersBase16((EntityHUD *)self, &drawPos, ScreenInfo[player->camera->screenID].position.x);

            // Draw Player YPos
            drawPos.x = TO_FIXED(ScreenInfo[player->camera->screenID].size.x - 16);
            drawPos.y += 0x100000;
            // HUD_DrawNumbersBase16((EntityHUD *)self, &drawPos, player->position.y.whole);

            // Draw Player XPos
            drawPos.x -= 0x90000;
            // HUD_DrawNumbersBase16((EntityHUD *)self, &drawPos, player->position.x.whole);
        }
    }

    drawPos = lifePos;
    int32 lives;
    if (globals->medalMods & MEDAL_NOLIVES) {
        self->lifeIconAnimator.frameID  = self->lifeIconAnimator.frameCount - 1;
        self->lifeNamesAnimator.frameID = self->lifeIconAnimator.frameID;
        lives                           = globals->coinCount;
    } else {
        lives                           = self->lives[player->playerID];
        self->lifeIconAnimator.frameID  = HUD_CharacterIndexFromID(player->characterID);
        self->lifeNamesAnimator.frameID = HUD_CharacterIndexFromID(player->characterID);

        // "Miles" name
        if ((globals->playerID & 0xFF) == ID_TAILS && globals->secrets & SECRET_REGIONSWAP)
            self->lifeNamesAnimator.frameID = self->lifeNamesAnimator.frameCount - 1;
    }

    if (self->lifeIconAnimator.frameID < 0) {
        self->lifeIconAnimator.frameID = self->lifeFrameIDs[SLOT_PLAYER1];
        lives--;
    } else {
        self->lifeFrameIDs[SLOT_PLAYER1] = self->lifeIconAnimator.frameID;
        self->lives[player->playerID]    = player->lives;
    }

    // RSDK.DrawSprite(&self->lifeIconAnimator, &drawPos, true);

    if (globals->gameMode == MODE_ENCORE) {
        for (int32 p = 0; p < PLAYER_COUNT; ++p) {
            if (SlotHUD->stockFlashTimers[p] > 0)
                SlotHUD->stockFlashTimers[p]--;
        }
    } else {
        switch (globals->gameSpriteStyle) {
            case GAME_S1:
            case GAME_CD:
            case GAME_S2:
            case GAME_SM:
                self->hudElementsAnimator.frameID = 14;
                RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true);
                drawPos.x += 0x300000;
                if (player->lives < 10)
                    drawPos.x -= 0x80000;
                // HUD_DrawNumbersBase10(&self->numbersAnimator, &drawPos, lives, 0);
                break;

            case GAME_S3K:
            case GAME_S3:
            case GAME_SK:
                // RSDK.DrawSprite(&self->lifeNamesAnimator, &drawPos, true);
                // self->hudElementsAnimator.frameID = 14;
                // RSDK.DrawSprite(&self->hudElementsAnimator, &drawPos, true); // X
                drawPos.x += 0x280000;
                // HUD_DrawNumbersBase10(&self->lifeNumbersAnimator, &drawPos, lives, 0);
                break;
        }
    }
}
