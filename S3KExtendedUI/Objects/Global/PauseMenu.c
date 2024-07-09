#include "../../Include.h"

ObjectPauseMenu *PauseMenu;
ModObjectPauseMenu *ModPauseMenu;

// ----------------------
// Standard Entity Events
// ----------------------

void PauseMenu_Update(void) {
    RSDK_THIS(PauseMenu);

    StateMachine_Run(self->state);
    RSDK.ProcessAnimation(&self->selectionAnimator);

    RSDKControllerState *controller = &ControllerInfo[CONT_P1];
    RSDKAnalogState *stick          = &AnalogStickInfoL[CONT_P1];

    self->up = controller->keyUp.press;
    self->up |= stick->keyUp.press;

    self->down = controller->keyDown.press;
    self->down |= stick->keyDown.press;

    self->start = controller->keyStart.press;
    self->start |= controller->keyA.press;
    self->start |= Unknown_pausePress;
}

void PauseMenu_LateUpdate(void) {
    RSDK_THIS(PauseMenu);

    StateMachine(state) = RSDK_GET_ENTITY(self->triggerPlayer, Player)->state.state;

    if (!self->state) {
        if (1 == 0 /*state == Player_State_Death || state == Player_State_Drown */) {
            destroyEntity(self);
        } else {

            self->visible   = true;
            self->drawGroup = DRAWGROUP_COUNT - 1;
            self->state     = PauseMenu_State_StartPause;
        }
    }
}

int32 temp0;

void PauseMenu_Draw(void) {
    RSDK_THIS(PauseMenu);

    if (SceneInfo->activeCategory == StageCategorySpecial)
        RSDK.SetActivePalette(3, 0, 255);

    StateMachine_Run(self->stateDraw);

    if (SceneInfo->activeCategory == StageCategorySpecial)
        RSDK.SetActivePalette(0, 0, 255);
}

void PauseMenu_Create(void *data) {
    RSDK_THIS(PauseMenu);

    RSDK.SetSpriteAnimation(ModPauseMenu->aniFrames, 0, &self->animator, true, 0);

    uint16 targetListID = 0;
    switch (GET_CHARACTER_ID(1)) {
        case ID_NONE:
        case ID_SONIC: targetListID = 1; break;
        case ID_TAILS: targetListID = 2; break;
        case ID_KNUCKLES: targetListID = 3; break;
        case ID_AMY: targetListID = 4; break;
    }

    RSDK.SetSpriteAnimation(ModPauseMenu->aniFrames, targetListID, &self->selectionAnimator, true, 0);

    self->backgroundAlpha = 74;
    self->physicalInput   = cfg.useTouch;

    if (!SceneInfo->inEditor) {
        self->active = ACTIVE_ALWAYS;

        if (data == INT_TO_VOID(true)) {
            self->visible   = true;
            self->drawGroup = DRAWGROUP_COUNT - 1;
        } else {
            self->state     = StateMachine_None;
            self->stateDraw = StateMachine_None;
        }
    }
}

void PauseMenu_StageLoad(void) {
    ModPauseMenu->sfxBleep  = RSDK.GetSfx("Global/MenuBleep.wav");
    ModPauseMenu->sfxAccept = RSDK.GetSfx("Global/MenuAccept.wav");
    ModPauseMenu->sfxWoosh  = RSDK.GetSfx("Global/MenuWoosh.wav");
    ModPauseMenu->aniFrames = RSDK.LoadSpriteAnimation("3K_Global/Pause.bin", SCOPE_STAGE);

    for (int32 i = 0; i < CHANNEL_COUNT; ++i) ModPauseMenu->activeChannels[i] = false;
}

// ----------------------
// Extra Entity Functions
// ----------------------

void PauseMenu_Init(void) {
    MOD_REGISTER_OBJ_OVERLOAD_MSV(PauseMenu, ModPauseMenu, PauseMenu_Update, PauseMenu_LateUpdate, NULL, PauseMenu_Draw, PauseMenu_Create,
                                  PauseMenu_StageLoad, NULL, NULL, NULL);
}

void PauseMenu_DrawPauseRect(int32 y) {
    RSDK_THIS(PauseMenu);

    // 'PAUSE' rect left
    RSDK.DrawRect(self->position.x + 128, NULL, 128, ScreenInfo->size.y, 0, 255, INK_NONE, true);

    // 'PAUSE' text sprite
    self->animator.frameID = 4;
    self->drawPos.x        = TO_FIXED(self->pauseBarPos.x - ScreenInfo->size.x);
    self->drawPos.y        = TO_FIXED(y);
    RSDK.DrawSprite(&self->animator, &self->drawPos, true);

    // 'PAUSE' rect right
    RSDK.DrawRect(self->pauseBarPos.x - ScreenInfo->size.x + 106, y, ScreenInfo->size.x, 13, 0, 255, INK_NONE, true);
}

void PauseMenu_DrawSpikes(void) {
    RSDK_THIS(PauseMenu);

    for (int32 i = 0; i < 8; i++) {
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);
        self->drawPos.y += 0x200000;
    }
}

void PauseMenu_PauseSound(void) {
    for (int32 i = 0; i < CHANNEL_COUNT; ++i) {
        if (RSDK.ChannelActive(i)) {
            RSDK.PauseChannel(i);
            ModPauseMenu->activeChannels[i] = true;
        }
    }
}

void PauseMenu_ResumeSound(void) {
    for (int32 i = 0; i < CHANNEL_COUNT; ++i) {
        if (ModPauseMenu->activeChannels[i]) {
            RSDK.ResumeChannel(i);
            ModPauseMenu->activeChannels[i] = false;
        }
    }
}

void PauseMenu_StopSound(void) {
    for (int32 i = 0; i < CHANNEL_COUNT; ++i) {
        if (ModPauseMenu->activeChannels[i]) {
            RSDK.StopChannel(i);
            ModPauseMenu->activeChannels[i] = false;
        }
    }
}

// -------------
// Object States
// -------------

void PauseMenu_State_StartPause(void) {
    RSDK_THIS(PauseMenu);

    EntityPlayer *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

    PauseMenu_PauseSound();
    RSDK.SetEngineState(ENGINESTATE_FROZEN);
    RSDK.PlaySfx(ModPauseMenu->sfxWoosh, false, 255);

    self->position.x = ScreenInfo->size.x;
    self->spritePosX = ScreenInfo->size.x + 6;
    self->timer      = 0;
    self->alpha      = 0;

    // Add language switch for this(?)
    self->timerThreshold = 12;

    bool32 blockedCategories = SceneInfo->activeCategory == StageCategoryCompetition || SceneInfo->activeCategory == StageCategorySpecial
                               || SceneInfo->activeCategory == StageCategoryBonus;
    if (player->lives <= 1 || blockedCategories)
        self->disableRestart = true;
    else
        self->disableRestart = false;

    if (cfg.useTouch)
        self->selectedButton = -1;

    self->state     = PauseMenu_State_SlideIn;
    self->stateDraw = PauseMenu_Draw_Init;
}

void PauseMenu_State_SlideIn(void) {
    RSDK_THIS(PauseMenu);

    self->pauseBarPos.x = (self->timer * ScreenInfo->size.x) / 12;
    self->pauseBarPos.y = (self->timer * ScreenInfo->size.y) / 12;
    self->position.x    = ScreenInfo->size.x - (self->timer << 7) / 12;

    if (self->timer < self->timerThreshold) {
        self->timer++;
    } else {
        self->spritePosX = self->position.x + 48;
        self->timer      = 0;
        self->state      = PauseMenu_State_SpritesFadeIn;
    }
}

void PauseMenu_State_SpritesFadeIn(void) {
    RSDK_THIS(PauseMenu);

    if (self->timer < 256) {
        self->timer += 16;

        if (self->timer < 255)
            self->alpha = self->timer;
        else
            self->alpha = 255;
    } else {
        self->timer     = 0;
        self->alpha     = 255;
        self->state     = PauseMenu_State_Controls;
        self->stateDraw = PauseMenu_Draw_Controls;
    }
}

void PauseMenu_State_Controls(void) {
    RSDK_THIS(PauseMenu);

    if (!self->physicalInput) {
        if (self->up) {
            RSDK.PlaySfx(ModPauseMenu->sfxBleep, false, 255);

            self->timer      = 0;
            self->spritePosX = ScreenInfo->size.x;
            self->selectedButton--;

            if (self->selectedButton < 0)
                self->selectedButton = 3;

            if (self->disableRestart && self->selectedButton == 1)
                self->selectedButton--;
        }

        if (self->down) {
            RSDK.PlaySfx(ModPauseMenu->sfxBleep, false, 255);

            self->timer      = 0;
            self->spritePosX = ScreenInfo->size.x;
            self->selectedButton++;

            if (self->selectedButton > 3)
                self->selectedButton = 0;

            if (self->disableRestart && self->selectedButton == 1)
                self->selectedButton++;
        }

        if (self->start) {
            RSDK.PlaySfx(ModPauseMenu->sfxAccept, false, 255);
            self->state     = PauseMenu_State_Confirmed;
            self->stateDraw = PauseMenu_Draw_Confirmed;
            self->alpha     = 248;
            self->timer     = 0;
        }

        if (TouchHelpers_CheckAnyTouch() >= 0) {
            self->physicalInput  = false;
            self->selectedButton = -1;
        }
    } else {
        if (TouchHelpers_CheckTouchRect(self->spritePosX, 32, ScreenInfo->size.x, 64, NULL, NULL) >= 0) {
            self->selectedButton = 0;
        } else {
            if (TouchHelpers_CheckAnyTouch() < 0) {
                if (self->selectedButton == 0) {
                    RSDK.PlaySfx(ModPauseMenu->sfxAccept, false, 255);
                    self->state     = PauseMenu_State_Confirmed;
                    self->stateDraw = PauseMenu_Draw_Confirmed;
                    self->alpha     = 248;
                    self->timer     = 0;
                } else {
                    if (self->selectedButton == 0)
                        self->selectedButton = -1;
                }
            }
        }

        // Restart
        if (!self->disableRestart) {
            if (TouchHelpers_CheckTouchRect(self->spritePosX, 80, ScreenInfo->size.x, 112, NULL, NULL) >= 0) {
                self->selectedButton = 1;
            } else {
                if (TouchHelpers_CheckAnyTouch() < 0) {
                    if (self->selectedButton == 1) {
                        RSDK.PlaySfx(ModPauseMenu->sfxAccept, false, 255);
                        self->state     = PauseMenu_State_Confirmed;
                        self->stateDraw = PauseMenu_Draw_Confirmed;
                        self->alpha     = 248;
                        self->timer     = 0;
                    } else {
                        if (self->selectedButton == 1)
                            self->selectedButton = -1;
                    }
                }
            }
        }

        // Options
        if (TouchHelpers_CheckTouchRect(self->spritePosX, 128, ScreenInfo->size.x, 160, NULL, NULL) >= 0) {
            self->selectedButton = 2;
        } else {
            if (TouchHelpers_CheckAnyTouch() < 0) {
                if (self->selectedButton == 2) {
                    RSDK.PlaySfx(ModPauseMenu->sfxAccept, false, 255);
                    self->state     = PauseMenu_State_Confirmed;
                    self->stateDraw = PauseMenu_Draw_Confirmed;
                    self->alpha     = 248;
                    self->timer     = 0;
                }
            } else {
                if (self->selectedButton == 2)
                    self->selectedButton = -1;
            }
        }

        // Exit
        if (TouchHelpers_CheckTouchRect(self->spritePosX, 176, ScreenInfo->size.x, 208, NULL, NULL) >= 0) {
            self->selectedButton = 3;
        } else {
            if (TouchHelpers_CheckAnyTouch() < 0) {
                if (self->selectedButton == 3) {
                    RSDK.PlaySfx(ModPauseMenu->sfxAccept, false, 255);
                    self->state     = PauseMenu_State_Confirmed;
                    self->stateDraw = PauseMenu_Draw_Confirmed;
                    self->alpha     = 248;
                    self->timer     = 0;
                }
            } else {
                if (self->selectedButton == 3)
                    self->selectedButton = -1;
            }
        }

        if (self->up) {
            self->selectedButton = 3;
            self->physicalInput  = true;
        }

        if (self->down) {
            self->selectedButton = 0;
            self->physicalInput  = true;
        }

        if (self->timer < 60)
            self->timer++;
    }
}

void PauseMenu_State_Confirmed(void) {
    RSDK_THIS(PauseMenu);

    self->timer++;
    self->timer &= 3;

    self->spritePosX += 4;
    if (self->alpha > 0) {
        // controls the speed of exiting the menu (originally 8, adjusted for speed)
        self->alpha -= 12;
    } else {

        // Check for Resume (and options for now)
        if (self->selectedButton == -1 || self->selectedButton == 0 || self->selectedButton == 2) {
            self->spritePosX    = self->position.x + 48;
            self->pauseBarPos.y = 202;

            self->timer     = 0;
            self->alpha     = self->backgroundAlpha; // Used for the BG, return to the initial opacity and then fade out
            self->state     = PauseMenu_State_ResumeGame;
            self->stateDraw = PauseMenu_Draw_ResumeGame;
            RSDK.SetEngineState(ENGINESTATE_REGULAR);
        } else {
            // globals->recallEntities = false;
            // globals->initCoolBonus  = false;
            /*
            if (StarPost) {
                StarPost->postIDs[0] = 0;
                StarPost->postIDs[1] = 0;
                StarPost->postIDs[2] = 0;
                StarPost->postIDs[3] = 0;
            }
            */
            // globals->specialRingID = 0;

            // Music::Stop();

            self->spritePosX = self->position.x + 48;
            self->state      = PauseMenu_State_ExitLevel;
            self->stateDraw  = PauseMenu_Draw_ExitLevel;
        }
    }
}

void PauseMenu_State_ResumeGame(void) {
    RSDK_THIS(PauseMenu);

    if (self->alpha > 0) {
        self->alpha -= 8;
        self->position.x += 16;
        self->spritePosX += 16;
        self->pauseBarPos.y += 16;
    } else {
        PauseMenu_ResumeSound();
        destroyEntity(self);
    }
}

void PauseMenu_State_ExitLevel(void) {
    RSDK_THIS(PauseMenu);

    if (self->position.x > -64) {
        self->position.x -= 16;
        self->spritePosX += 16;
    } else {
        switch (self->selectedButton) {
            case 1: // Restart
                RSDK.LoadScene();
                break;

            case 2: // Options
                // TimeAttack.Round = -1;
                RSDK.SetEngineState(ENGINESTATE_DEVMENU);

                break;

            case 3: // Exit
                if (SceneInfo->activeCategory == StageCategoryCompetition)
                    RSDK.SetScene("Presentation & Menus", "Menu Comp");
                else
                    RSDK.SetScene("Presentation & Menus", "Title Screen");
                RSDK.LoadScene();
                break;
        }
    }
}

// -----------
// Draw States
// -----------

void PauseMenu_Draw_Init(void) {
    RSDK_THIS(PauseMenu);
    self->inkEffect = INK_NONE;

    if (self->pauseBarHeight < SCREEN_YSIZE) {
        if (self->pauseBarPos.y > self->pauseBarHeight)
            self->pauseBarHeight = self->pauseBarPos.y;
    }

    PauseMenu_Draw_Controls();
}

void PauseMenu_Draw_Controls(void) {
    RSDK_THIS(PauseMenu);
    self->inkEffect = INK_NONE;

    // Background fade
    RSDK.DrawRect(NULL, NULL, ScreenInfo->size.x, self->pauseBarHeight, 0, self->backgroundAlpha, INK_ALPHA, true);

    // 'PAUSE' bar
    PauseMenu_DrawPauseRect(202);

    // Spikes
    self->animator.frameID = 3;
    self->drawPos.x        = TO_FIXED(self->position.x);
    self->drawPos.y        = 0;
    PauseMenu_DrawSpikes();

    self->inkEffect = INK_ALPHA; // eh

    temp0 = self->position.x + 48;
    if (self->spritePosX > temp0) {
        self->spritePosX += temp0 - self->spritePosX >> 3;
    }

    // Draw 'CONTINUE' button
    self->animator.frameID = 6;
    self->drawPos.x        = TO_FIXED(temp0);
    self->drawPos.y        = TO_FIXED(48);
    RSDK.DrawSprite(&self->animator, &self->drawPos, true);

    if (self->selectedButton == 0) {
        // Selection Line
        self->animator.frameID = 5;
        self->drawPos.x        = TO_FIXED(self->spritePosX);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);

        // Selection Player
        self->drawPos.x = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
    }

    // Draw 'RESTART' button
    self->animator.frameID = 7;
    self->drawPos.x        = TO_FIXED(temp0);
    self->drawPos.y += TO_FIXED(48);

    if (!self->disableRestart) {
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);
    } else {
        int32 prevAlpha = self->alpha;
        self->alpha >>= 1;
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);
        self->alpha = prevAlpha;
    }

    if (self->selectedButton == 1) {
        // Selection Line
        self->animator.frameID = 5;
        self->drawPos.x        = TO_FIXED(self->spritePosX);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);

        // Selection Player
        self->drawPos.x = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
    }

    // Draw 'OPTIONS' button
    self->animator.frameID = 8;
    self->drawPos.y += TO_FIXED(48);
    RSDK.DrawSprite(&self->animator, &self->drawPos, true);

    if (self->selectedButton == 2) {
        // Selection Line
        self->animator.frameID = 5;
        self->drawPos.x        = TO_FIXED(self->spritePosX);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);

        // Selection Player
        self->drawPos.x = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
    }

    // Draw 'EXIT' button
    self->animator.frameID = 9;
    self->drawPos.y += TO_FIXED(48);
    RSDK.DrawSprite(&self->animator, &self->drawPos, true);

    if (self->selectedButton == 3) {
        // Selection Line
        self->animator.frameID = 5;
        self->drawPos.x        = TO_FIXED(self->spritePosX);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);

        // Selection Player
        self->drawPos.x = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
    }
}

void PauseMenu_Draw_Confirmed(void) {
    RSDK_THIS(PauseMenu);
    self->inkEffect = INK_NONE;

    // Background fade
    RSDK.DrawRect(NULL, NULL, ScreenInfo->size.x, self->pauseBarHeight, 0, self->backgroundAlpha, INK_ALPHA, true);

    // 'PAUSE' bar
    PauseMenu_DrawPauseRect(202);

    self->animator.frameID = 3;
    self->drawPos.x        = TO_FIXED(self->position.x);
    self->drawPos.y        = 0;
    PauseMenu_DrawSpikes();

    // Continue
    self->drawPos.y = TO_FIXED(48);
    if (self->selectedButton != 0) {
        self->inkEffect        = INK_ALPHA;
        self->animator.frameID = 6;
        self->drawPos.x        = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);
    }
    // Continue (Selected)
    else {
        // Continue flash
        if (self->timer < 2) {
            self->inkEffect        = INK_NONE;
            self->animator.frameID = 6;
            self->drawPos.x        = TO_FIXED(self->position.x + 48);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);
        }

        // Selection Line
        self->animator.frameID = 5;
        self->drawPos.x        = TO_FIXED(self->spritePosX);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);

        // Selection Player
        self->drawPos.x = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
    }

    // Restart
    self->drawPos.y += TO_FIXED(48);
    if (self->selectedButton != 1) {
        if (!self->disableRestart) {
            self->inkEffect        = INK_ALPHA;
            self->animator.frameID = 7;
            self->drawPos.x        = TO_FIXED(self->position.x + 48);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);
        } else {
            int32 prevAlpha = self->alpha;
            self->alpha >>= 1;
            self->inkEffect        = INK_ALPHA;
            self->animator.frameID = 7;
            self->drawPos.x        = TO_FIXED(self->position.x + 48);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);
            self->alpha = prevAlpha;
        }
    }
    // Restart (Selected)
    else {
        // Restart flash
        if (self->timer < 2) {
            self->inkEffect        = INK_NONE;
            self->animator.frameID = 7;
            self->drawPos.x        = TO_FIXED(self->position.x + 48);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);
        }

        // Selection Line
        self->inkEffect        = INK_NONE;
        self->animator.frameID = 5;
        self->drawPos.x        = TO_FIXED(self->spritePosX);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);

        // Selection Player
        self->drawPos.x = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
    }

    // Options
    self->drawPos.y += TO_FIXED(48);
    if (self->selectedButton != 2) {
        self->inkEffect        = INK_ALPHA;
        self->animator.frameID = 8;
        self->drawPos.x        = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);
    }
    // Options (Selected)
    else {
        // Options flash
        if (self->timer < 2) {
            self->inkEffect        = INK_NONE;
            self->animator.frameID = 8;
            self->drawPos.x        = TO_FIXED(self->position.x + 48);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);
        }

        // Selection Line
        self->inkEffect        = INK_NONE;
        self->animator.frameID = 5;
        self->drawPos.x        = TO_FIXED(self->spritePosX);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);

        // Selection Player
        self->drawPos.x = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
    }

    // Exit
    self->drawPos.y += TO_FIXED(48);
    if (self->selectedButton != 3) {
        self->inkEffect        = INK_ALPHA;
        self->animator.frameID = 9;
        self->drawPos.x        = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);
    }
    // Exit (Selected)
    else {
        // Exit flash
        if (self->timer < 2) {
            self->inkEffect        = INK_NONE;
            self->animator.frameID = 9;
            self->drawPos.x        = TO_FIXED(self->position.x + 48);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);
        }

        // Selection Line
        self->inkEffect        = INK_NONE;
        self->animator.frameID = 5;
        self->drawPos.x        = TO_FIXED(self->spritePosX);
        RSDK.DrawSprite(&self->animator, &self->drawPos, true);

        // Selection Player
        self->drawPos.x = TO_FIXED(self->position.x + 48);
        RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
    }
}

void PauseMenu_Draw_ResumeGame(void) {
    RSDK_THIS(PauseMenu);
    self->inkEffect = INK_NONE;

    // Background fade
    RSDK.DrawRect(NULL, NULL, ScreenInfo->size.x, self->pauseBarHeight, 0, self->alpha, INK_ALPHA, true);

    // 'PAUSE' bar
    PauseMenu_DrawPauseRect(self->pauseBarPos.y);

    self->animator.frameID = 3;
    self->drawPos.x        = TO_FIXED(self->position.x);
    self->drawPos.y        = 0;
    PauseMenu_DrawSpikes();

    switch (self->selectedButton) {
        case 0: // Continue
            self->animator.frameID = 6;
            self->drawPos.x        = TO_FIXED(self->spritePosX);
            self->drawPos.y        = TO_FIXED(48);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);

            self->drawPos.x = TO_FIXED(self->position.x + 48);
            RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
            break;
        case 1: // Reset
            self->animator.frameID = 7;
            self->drawPos.x        = TO_FIXED(self->spritePosX);
            self->drawPos.y        = TO_FIXED(96);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);

            self->drawPos.x = TO_FIXED(self->position.x + 48);
            RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
            break;
        case 2: // Options
            self->animator.frameID = 8;
            self->drawPos.x        = TO_FIXED(self->spritePosX);
            self->drawPos.y        = TO_FIXED(144);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);

            self->drawPos.x = TO_FIXED(self->position.x + 48);
            RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
            break;
        case 3: // Exit
            self->animator.frameID = 9;
            self->drawPos.x        = TO_FIXED(self->spritePosX);
            self->drawPos.y        = TO_FIXED(192);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);

            self->drawPos.x = TO_FIXED(self->position.x + 48);
            RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
            break;
    }
}

void PauseMenu_Draw_ExitLevel(void) {
    RSDK_THIS(PauseMenu);
    self->inkEffect = INK_NONE;

    // Background fade
    RSDK.DrawRect(NULL, NULL, ScreenInfo->size.x, self->pauseBarHeight, 0, self->backgroundAlpha, INK_ALPHA, true);

    // 'PAUSE' bar
    PauseMenu_DrawPauseRect(202);

    self->animator.frameID = 3;
    self->drawPos.x        = TO_FIXED(self->position.x);
    self->drawPos.y        = 0;
    PauseMenu_DrawSpikes();

    // The rectangle that consumes all life
    RSDK.DrawRect(self->position.x + 128, 0, ScreenInfo->size.x * 47, ScreenInfo->size.y, 0, 255, INK_NONE, true);

    self->drawPos.x = TO_FIXED(self->spritePosX);
    switch (self->selectedButton) {
        case 0: // Continue
            self->animator.frameID = 6;
            self->drawPos.y        = TO_FIXED(48);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);
            RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
            break;
        case 1: // Reset
            self->animator.frameID = 7;
            self->drawPos.y        = TO_FIXED(96);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);
            RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
            break;
        case 2: // Options
            self->animator.frameID = 8;
            self->drawPos.y        = TO_FIXED(144);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);
            RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
            break;
        case 3: // Exit
            self->animator.frameID = 9;
            self->drawPos.y        = TO_FIXED(192);
            RSDK.DrawSprite(&self->animator, &self->drawPos, true);
            RSDK.DrawSprite(&self->selectionAnimator, &self->drawPos, true);
            break;
    }
}