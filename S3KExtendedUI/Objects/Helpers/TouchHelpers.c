#include "../../include.h"

int32 TouchHelpers_CheckTouchRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy) {
    if (fx)
        *fx = 0;
    if (fy)
        *fy = 0;

    for (int32 t = 0; t < TouchInfo->count; ++t) {
        int32 tx = (int32)(TouchInfo->x[t] * ScreenInfo->size.x);
        int32 ty = (int32)(TouchInfo->y[t] * ScreenInfo->size.y);

        if (TouchInfo->down[t]) {
            if (tx >= x1 && ty >= y1 && tx <= x2 && ty <= y2) {
                if (fx)
                    *fx = tx;
                if (fy)
                    *fy = ty;

                return t;
            }
        }
    }

    return -1;
}

int32 TouchHelpers_CheckAnyTouch(void) { return TouchHelpers_CheckTouchRect(NULL, NULL, ScreenInfo->size.x, ScreenInfo->size.y, NULL, NULL); }