#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "executor.h"
#include "behavior.h"

// Retrieve variable value by name (e.g. $x → "3.14"), with parent fallback
const char* get_value(ExecutionContext* ctx, const char* name) {
    for (int i = 0; i < ctx->param_count; i++) {
        if (strcmp(ctx->param_names[i], name) == 0) {
            return ctx->param_values[i];
        }
    }
    // ⬇Inherit from parent context if exists
    if (ctx->parent) {
        return get_value(ctx->parent, name);
    }
    return NULL;
}

// Create execution context from parameters and arguments, with parent
ExecutionContext* create_context(Behavior* behavior, char** args, int arg_count, ExecutionContext* parent) {
    ExecutionContext* ctx = malloc(sizeof(ExecutionContext));
    ctx->param_count = behavior->param_count;
    ctx->param_names = malloc(sizeof(char*) * ctx->param_count);
    ctx->param_values = malloc(sizeof(char*) * ctx->param_count);
    ctx->parent = parent;  // link to parent

    for (int i = 0; i < ctx->param_count; i++) {
        ctx->param_names[i] = strdup(behavior->param_names[i]);
        ctx->param_values[i] = (i < arg_count) ? strdup(args[i]) : strdup("");
    }

    return ctx;
}

// Free memory used by execution context
void free_context(ExecutionContext* ctx) {
    for (int i = 0; i < ctx->param_count; i++) {
        free(ctx->param_names[i]);
        free(ctx->param_values[i]);
    }
    free(ctx->param_names);
    free(ctx->param_values);
    free(ctx);
}

// Execute a full behavior structure (either exec_fn or behavior chain)
void run_behavior(Behavior* behavior, ExecutionContext* ctx) {
    if (behavior->exec_fn) {
        behavior->exec_fn(behavior, ctx);
        return;
    }

    BehaviorNode* node = behavior->body;
    while (node) {
        Behavior* called = find_behavior(node->name);
        if (!called) {
            printf("[error] Behavior '%s' not found.\n", node->name);
        } else {
            //Resolve arguments with $ substitution
            char** resolved_args = malloc(sizeof(char*) * node->arg_count);
            for (int i = 0; i < node->arg_count; i++) {
                const char* raw = node->args[i].value;
                if (raw[0] == '$') {
                    const char* resolved = get_value(ctx, raw + 1);
                    resolved_args[i] = strdup(resolved ? resolved : "");
                } else {
                    resolved_args[i] = strdup(raw);
                }
            }

            //Inherit current context
            ExecutionContext* subctx = create_context(called, resolved_args, node->arg_count, ctx);
            run_behavior(called, subctx);
            free_context(subctx);

            for (int i = 0; i < node->arg_count; i++) free(resolved_args[i]);
            free(resolved_args);
        }

        node = node->next;
    }
}

// Entry point for executing a behavior by name
void execute_behavior(const char* name, char** args, int arg_count) {
    Behavior* b = find_behavior(name);
    if (!b) {
        printf("[error] Entry behavior '%s' not found.\n", name);
        return;
    }
    ExecutionContext* ctx = create_context(b, args, arg_count, NULL);
    run_behavior(b, ctx);
    free_context(ctx);
}