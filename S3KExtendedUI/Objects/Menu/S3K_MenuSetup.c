#include "../../Include.h"

ObjectS3K_MenuSetup *S3K_MenuSetup;

void S3K_MenuSetup_Init(void) {
    MOD_REGISTER_OBJECT_HOOK(S3K_MenuSetup);
}