#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mathmod.h"

// Utility: convert string to double
double parse_double(const char* s) {
    return strtod(s, NULL);
}

// Utility: convert double to string
char* double_to_str(double d) {
    char* buf = malloc(32);
    snprintf(buf, 32, "%g", d);
    return buf;
}

// =======================
// add(x, y) → x + y
// =======================
void add_exec(Behavior* self, ExecutionContext* ctx) {
    const char* x = get_value(ctx, self->param_names[0]);
    const char* y = get_value(ctx, self->param_names[1]);
    double dx = parse_double(x);
    double dy = parse_double(y);
    char* result = double_to_str(dx + dy);
    printf("%s\n", result);
    free(result);
}

// =======================
// sub(x, y) → x - y
// =======================
void sub_exec(Behavior* self, ExecutionContext* ctx) {
    const char* x = get_value(ctx, self->param_names[0]);
    const char* y = get_value(ctx, self->param_names[1]);
    double dx = parse_double(x);
    double dy = parse_double(y);
    char* result = double_to_str(dx - dy);
    printf("%s\n", result);
    free(result);
}

// =======================
// gt(x, y) → "true"/"false"
// =======================
void gt_exec(Behavior* self, ExecutionContext* ctx) {
    const char* x = get_value(ctx, self->param_names[0]);
    const char* y = get_value(ctx, self->param_names[1]);
    double dx = parse_double(x);
    double dy = parse_double(y);
    printf("%s\n", dx > dy ? "true" : "false");
}

// =======================
// lt(x, y) → "true"/"false"
// =======================
void lt_exec(Behavior* self, ExecutionContext* ctx) {
    const char* x = get_value(ctx, self->param_names[0]);
    const char* y = get_value(ctx, self->param_names[1]);
    double dx = parse_double(x);
    double dy = parse_double(y);
    printf("%s\n", dx < dy ? "true" : "false");
}

// Register all math behaviors
void register_math_behaviors() {
    // add(x, y)
    char* add_params[] = { "x", "y" };
    Behavior* add_b = create_behavior("add", add_params, 2, NULL);
    add_b->exec_fn = add_exec;
    register_behavior(add_b);

    // sub(x, y)
    Behavior* sub_b = create_behavior("sub", add_params, 2, NULL);
    sub_b->exec_fn = sub_exec;
    register_behavior(sub_b);

    // gt(x, y)
    Behavior* gt_b = create_behavior("gt", add_params, 2, NULL);
    gt_b->exec_fn = gt_exec;
    register_behavior(gt_b);

    // lt(x, y)
    Behavior* lt_b = create_behavior("lt", add_params, 2, NULL);
    lt_b->exec_fn = lt_exec;
    register_behavior(lt_b);
}