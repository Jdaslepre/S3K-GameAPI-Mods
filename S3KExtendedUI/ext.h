#ifndef EXT_H
#define EXT_H

// -------
// General
// -------

#define EXTERNDEF(x)                                                                                                                                 \
    x;                                                                                                                                               \
    extern x

// ----------
// RSDK Types
// ----------

typedef unsigned long long uint64;

// -----
// Extra
// -----

typedef enum {
    StageCategoryPresentation,
    StageCategoryRegular,
    StageCategoryCompetition,
    StageCategoryBossAttack,
    StageCategoryBonus,
    StageCategorySpecial,
    StageCategoryDebug
} StageCategories;

// ------------
// StateMachine
// ------------

typedef void (*StatePtr)(void);

typedef struct {
    StatePtr state;
    int32 timer;
    uint8 unknown1;
    uint8 unknown2;
    uint8 unknown3;
    uint8 priority;
} ext_StateMachine;

static void *ext_ToGenericPtr(StatePtr ptr);
static void ext_StateMachine_Init(ext_StateMachine *machine);
int32 ext_StateMachine_Set(ext_StateMachine *machine, StatePtr state, uint8 priority);
static int32 ext_StateMachine_SetAndRun(ext_StateMachine *machine, StatePtr state, Entity *self, uint8 priority);
static int32 ext_StateMachine_QueueForTime(ext_StateMachine *machine, StatePtr state, uint32 duration, uint8 priority);
void ext_StateMachine_Run(ext_StateMachine *machine, Entity *self);
int32 ext_StateMachine_Matches(ext_StateMachine *machine, StatePtr other);
static void ext_StateMachine_Copy(ext_StateMachine *dest, ext_StateMachine *src);

#endif