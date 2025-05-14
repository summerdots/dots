#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "behavior.h"
#include "executor.h"
#include "builtin.h"

// Replace $var with value from context
char* replace_variables(const char* input, ExecutionContext* ctx) {
    char* result = malloc(1024);
    result[0] = '\0';

    const char* p = input;
    while (*p) {
        if (*p == '$') {
            p++;
            char var[64];
            int vi = 0;

            while ((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') ||
                   (*p >= '0' && *p <= '9') || *p == '_') {
                var[vi++] = *p;
                p++;
            }
            var[vi] = '\0';

            const char* val = get_value(ctx, var);
            strcat(result, val ? val : "");
        } else {
            char ch[2] = {*p, '\0'};
            strcat(result, ch);
            p++;
        }
    }

    return result;
}

// Builtin: print(x)
void print_exec(Behavior* self, ExecutionContext* ctx) {
    // Retrieve the raw parameter value from context
    const char* raw = get_value(ctx, self->param_names[0]);

    if (!raw) {
        // If null, just print a newline
        printf("\n");
        return;
    }

    // Replace $variables in the string (e.g. "Hello, $name!")
    char* resolved = replace_variables(raw, ctx);

    // If the result is quoted (starts and ends with "), remove the quotes
    size_t len = strlen(resolved);
    if (len >= 2 && resolved[0] == '"' && resolved[len - 1] == '"') {
        resolved[len - 1] = '\0';      // Remove ending quote
        printf("%s\n", resolved + 1);  // Skip opening quote and print
    } else {
        // Otherwise, print as-is
        printf("%s\n", resolved);
    }

    free(resolved);
}

// Set variable in context
void set_value(ExecutionContext* ctx, const char* name, const char* value) {
    for (int i = 0; i < ctx->param_count; i++) {
        if (strcmp(ctx->param_names[i], name) == 0) {
            free(ctx->param_values[i]);
            ctx->param_values[i] = strdup(value);
            return;
        }
    }
    // If not found, add new variable
    ctx->param_names = realloc(ctx->param_names, sizeof(char*) * (ctx->param_count + 1));
    ctx->param_values = realloc(ctx->param_values, sizeof(char*) * (ctx->param_count + 1));
    ctx->param_names[ctx->param_count] = strdup(name);
    ctx->param_values[ctx->param_count] = strdup(value);
    ctx->param_count++;
}

// Builtin: set(name, value)
void set_exec(Behavior* self, ExecutionContext* ctx) {
    const char* varname = get_value(ctx, self->param_names[0]);
    const char* raw = get_value(ctx, self->param_names[1]);
    if (!varname || !raw) return;

    char* resolved = replace_variables(raw, ctx);

    // Handle outer quotes (e.g. "Hello, $name!")
    size_t len = strlen(resolved);
    if (len >= 2 && resolved[0] == '"' && resolved[len - 1] == '"') {
        resolved[len - 1] = '\0';
        memmove(resolved, resolved + 1, len - 1);
    }

    set_value(ctx, varname, resolved);
    free(resolved);
}

// Builtin: exit()
void exit_exec(Behavior* self, ExecutionContext* ctx) {
    printf("[Dots] Program exited.\n");
    exit(0);
}

// Register all builtin behaviors
void register_builtin_behaviors() {
    // print(x)
    char* print_params[] = { "x" };
    Behavior* print_b = create_behavior("print", print_params, 1, NULL);
    print_b->exec_fn = print_exec;
    register_behavior(print_b);

    // exit()
    Behavior* exit_b = create_behavior("exit", NULL, 0, NULL);
    exit_b->exec_fn = exit_exec;
    register_behavior(exit_b);

    // set(name, value)
    char* set_params[] = { "name", "value" };
    Behavior* set_b = create_behavior("set", set_params, 2, NULL);
    set_b->exec_fn = set_exec;
    register_behavior(set_b);
}