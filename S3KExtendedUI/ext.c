#include "include.h"

// ------------------
// GameAPI Extensions
// ------------------

// ------------
// StateMachine
// ------------

void *ext_ToGenericPtr(StatePtr ptr) { return (void *)ptr; }

void ext_StateMachine_Init(ext_StateMachine *machine) {
    machine->state    = NULL;
    machine->timer    = 0;
    machine->unknown1 = 0;
    machine->unknown2 = 0;
    machine->unknown3 = 0;
    machine->priority = 0;
}

int32 ext_StateMachine_Set(ext_StateMachine *machine, StatePtr state, uint8 priority) {
    if (priority < machine->priority || machine->priority == 1)
        return 0;

    machine->state    = state;
    machine->timer    = 0;
    machine->priority = priority;
    return 1;
}

int32 ext_StateMachine_SetAndRun(ext_StateMachine *machine, StatePtr state, Entity *self, uint8 priority) {
    int32 applied = ext_StateMachine_Set(machine, state, priority);
    if (applied)
        ext_StateMachine_Run(machine, self);
    return applied;
}

int32 ext_StateMachine_QueueForTime(ext_StateMachine *machine, StatePtr state, uint32 duration, uint8 priority) {
    if (priority < machine->priority || machine->priority == 1)
        return 0;

    machine->state    = state;
    machine->timer    = duration;
    machine->priority = priority;
    return 1;
}

void ext_StateMachine_Run(ext_StateMachine *machine, Entity *self) {
    if (machine->timer)
        machine->timer--;

    if (machine->state)
        machine->state();
}

int32 ext_StateMachine_Matches(ext_StateMachine *machine, StatePtr other) { return machine->state == other; }

void ext_StateMachine_Copy(ext_StateMachine *dest, ext_StateMachine *src) {
    dest->state    = src->state;
    dest->timer    = src->timer;
    dest->unknown1 = src->unknown1;
    dest->unknown2 = src->unknown2;
    dest->unknown3 = src->unknown3;
    dest->priority = src->priority;
}
