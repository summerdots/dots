#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "introspect.h"
#include "behavior.h"  // For get_behavior_registry()

// Helper: cleanly strip surrounding double quotes from a string
char* strip_quotes(const char* s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    if (len >= 2 && s[0] == '"' && s[len - 1] == '"') {
        char* copy = malloc(len - 1);          // allocate for inner content + \0
        strncpy(copy, s + 1, len - 2);         // skip opening quote
        copy[len - 2] = '\0';                  // null-terminate
        return copy;
    } else {
        return strdup(s);  // if no quotes, duplicate as-is
    }
}

// Behavior: list()
void list_exec(Behavior* self, ExecutionContext* ctx) {
    const BehaviorRegistry* reg = get_behavior_registry();
    printf("[introspect] Registered behaviors:\n");
    for (int i = 0; i < reg->count; i++) {
        printf(" - %s\n", reg->list[i]->name);
    }
}

// Behavior: explain(name)
void explain_exec(Behavior* self, ExecutionContext* ctx) {
    const char* raw = get_value(ctx, self->param_names[0]);
    char* name = strip_quotes(raw);  // ✨ remove quotes if present

    const BehaviorRegistry* reg = get_behavior_registry();
    for (int i = 0; i < reg->count; i++) {
        Behavior* b = reg->list[i];
        if (strcmp(b->name, name) == 0) {
            printf("[explain] Behavior: %s\n", b->name);
            printf(" - Params (%d): ", b->param_count);
            for (int j = 0; j < b->param_count; j++) {
                printf("%s%s", j > 0 ? ", " : "", b->param_names[j]);
            }
            printf("\n - Type: %s\n", b->exec_fn ? "builtin" : "user-defined");
            free(name);
            return;
        }
    }

    printf("[explain] Behavior '%s' not found.\n", name);
    free(name);
}

// Register list() and explain(name)
void register_introspection_behaviors() {
    // list()
    Behavior* list_b = create_behavior("list", NULL, 0, NULL);
    list_b->exec_fn = list_exec;
    register_behavior(list_b);

    // explain(name)
    char* explain_params[] = { "name" };
    Behavior* explain_b = create_behavior("explain", explain_params, 1, NULL);
    explain_b->exec_fn = explain_exec;
    register_behavior(explain_b);
}