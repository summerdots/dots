
#include <stdio.h>
#include "instruction.h"
#include "interpreter.h"

int run_script(const struct Script* script) {
    for (int i = 0; i < script->line_count; i++) {
        int result = parse_command(script->lines[i]);
        if (result == 1) return 1; // exit triggered
    }
    return 0;
}
