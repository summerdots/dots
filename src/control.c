#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "control.h"

// ==========================
// if(cond): if cond is "true" or non-zero, execute body
// ==========================
void if_exec(Behavior* self, ExecutionContext* ctx) {
    const char* val = get_value(ctx, self->param_names[0]);
    
    // Simple truthiness check: "false" or "0" → false; anything else → true
    int truthy = 0;
    if (val && (strcmp(val, "false") != 0) && (strcmp(val, "0") != 0) && strlen(val) > 0) {
        truthy = 1;
    }

    if (truthy && self->body) {
        run_behavior(self, ctx);  // run body in current context
    }
}

// ==========================
// Register all control behaviors
// ==========================
void register_control_behaviors() {
    // Define behavior: if(cond)
    char* if_params[] = { "cond" };
    Behavior* if_b = create_behavior("if", if_params, 1, NULL);
    if_b->exec_fn = if_exec;
    register_behavior(if_b);
}