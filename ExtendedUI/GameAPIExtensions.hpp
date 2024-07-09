#pragma once
#include <functional>

namespace RSDK {

#define Type_VoidPtr       void (*)(void)
#define Type_StateHook     bool32 (*)(bool32)
#define RSDK_TYPEDEF(name) typedef struct name name

#define THIS_REF(class) class *self = RSDK_THIS(class)
#define SELF_REF(class) class *self = RSDK_SELF(class)

#define RSDK_THIS(class) ((class *)this)
#define RSDK_SELF(class) ((class *)sceneInfo->entity)

// Gets & Sets a public function to a pointer
#define GetPublicFuncAssign(ptr, id, functionName) ptr = (decltype(ptr))Mod::GetPublicFunction(id, functionName)

template <typename T> inline static bool32 StateMatchesExt(StateMachine<T> *state, void(*other)) {
    union {
        void (*in);
        void (T::*out)();
    } u;
    u.in = other;
    return state->Matches(u.out);
}

} // namespace RSDK
