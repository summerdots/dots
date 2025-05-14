#ifndef LAZY_H
#define LAZY_H

#include "behavior.h"
#include "executor.h"

// Register internal lazy support (no user-level function needed)
void register_lazy_support();

// Evaluate a lazy node if not yet executed, and cache result
const char* evaluate_lazy_node(BehaviorNode* node, ExecutionContext* ctx);

#endif