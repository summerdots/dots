#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "behavior.h"

// Stores parameter name → value mapping for a behavior execution
typedef struct ExecutionContext {
    char** param_names;
    char** param_values;
    int param_count;
    struct ExecutionContext* parent;
} ExecutionContext;

// Build a context from formal params + actual args
ExecutionContext* create_context(Behavior* behavior, char** args, int arg_count, ExecutionContext* parent);

// Look up value of a variable from the context
const char* get_value(ExecutionContext* ctx, const char* name);

// Clean up context memory
void free_context(ExecutionContext* ctx);

// Execute entry behavior by name
void execute_behavior(const char* name, char** args, int arg_count);

// Execute a behavior (core function)
void run_behavior(Behavior* behavior, ExecutionContext* context);

#endif