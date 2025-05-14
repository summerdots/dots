#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lazy.h"

// In-memory cache for lazy nodes (basic version)
typedef struct {
    BehaviorNode* node;
    char* result;
} LazyCacheEntry;

#define MAX_LAZY_CACHE 256
static LazyCacheEntry lazy_cache[MAX_LAZY_CACHE];
static int lazy_cache_count = 0;

// Helper: find cached value
const char* find_cached_result(BehaviorNode* node) {
    for (int i = 0; i < lazy_cache_count; i++) {
        if (lazy_cache[i].node == node) {
            return lazy_cache[i].result;
        }
    }
    return NULL;
}

// Helper: store result in cache
void cache_result(BehaviorNode* node, const char* value) {
    if (lazy_cache_count >= MAX_LAZY_CACHE) return; // basic limit
    lazy_cache[lazy_cache_count].node = node;
    lazy_cache[lazy_cache_count].result = strdup(value);
    lazy_cache_count++;
}

// Public function: evaluate a lazy node
const char* evaluate_lazy_node(BehaviorNode* node, ExecutionContext* ctx) {
    const char* cached = find_cached_result(node);
    if (cached) return cached;

    // Resolve node like a one-line behavior
    Behavior* called = find_behavior(node->name);
    if (!called) return "";

    // Build args
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

    ExecutionContext* subctx = create_context(called, resolved_args, node->arg_count, ctx);

    // Capture output only from print/math-style behavior
    // In real version, this should depend on behavior return system
    printf("[lazy] Executing lazy node: %s\n", node->name);

    run_behavior(called, subctx); // currently does not return value

    // For now just cache dummy result (placeholder for future return value system)
    cache_result(node, "[ok]");

    free_context(subctx);
    for (int i = 0; i < node->arg_count; i++) free(resolved_args[i]);
    free(resolved_args);

    return "[ok]";
}

// Initialize lazy system (not needed now, placeholder)
void register_lazy_support() {
    // Nothing for now
}