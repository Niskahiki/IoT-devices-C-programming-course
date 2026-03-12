#include <stdio.h>
#include "debug.h"
#include <stdarg.h>

static int dbg_level;

void set_debug_level(int debug_level) {
    dbg_level = debug_level;
}

int dprintf(int debug_level, const char *fmt, ...) {
    if (debug_level > dbg_level)
        return 0;

    va_list args;

    printf("[DBG%d] ", debug_level);

    va_start(args, fmt);
    int ret = vprintf(fmt, args);
    va_end(args);

    return ret;
}