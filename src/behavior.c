#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "behavior.h"

// Static global behavior registry
static BehaviorRegistry registry;

// Provide read-only access to the behavior registry
const BehaviorRegistry* get_behavior_registry() {
    return &registry;
}

// Initialize the behavior registry
void init_behavior_registry() {
    registry.count = 0;
    registry.capacity = 10;
    registry.list = malloc(sizeof(Behavior*) * registry.capacity);
}

// Add a behavior to the registry
void register_behavior(Behavior* behavior) {
    if (registry.count >= registry.capacity) {
        registry.capacity *= 2;
        registry.list = realloc(registry.list, sizeof(Behavior*) * registry.capacity);
    }
    registry.list[registry.count++] = behavior;
}

// Look up a behavior by name
Behavior* find_behavior(const char* name) {
    for (int i = 0; i < registry.count; i++) {
        if (strcmp(registry.list[i]->name, name) == 0) {
            return registry.list[i];
        }
    }
    return NULL;
}

// Create a new behavior definition
Behavior* create_behavior(const char* name, char** params, int param_count, BehaviorNode* body) {
    Behavior* b = malloc(sizeof(Behavior));
    b->name = strdup(name);
    b->param_count = param_count;
    b->param_names = malloc(sizeof(char*) * param_count);
    for (int i = 0; i < param_count; i++) {
        b->param_names[i] = strdup(params[i]);
    }
    b->body = body;
    b->is_pure = false;
    b->exec_fn = NULL; // Default: no bound function (user-defined)
    return b;
}

// Create a behavior node (an instruction line)
BehaviorNode* create_behavior_node(const char* name, Argument* args, int arg_count, bool is_lazy) {
    BehaviorNode* node = malloc(sizeof(BehaviorNode));
    node->name = strdup(name);
    node->args = malloc(sizeof(Argument) * arg_count);
    for (int i = 0; i < arg_count; i++) {
        node->args[i].name = strdup(args[i].name);
        node->args[i].value = strdup(args[i].value);
    }
    node->arg_count = arg_count;
    node->is_lazy = is_lazy;
    node->next = NULL;
    return node;
}

// Free an entire behavior chain
void free_behavior_node(BehaviorNode* node) {
    if (!node) return;
    free(node->name);
    for (int i = 0; i < node->arg_count; i++) {
        free(node->args[i].name);
        free(node->args[i].value);
    }
    free(node->args);
    free_behavior_node(node->next);
    free(node);
}

// Free a full behavior definition
void free_behavior(Behavior* b) {
    if (!b) return;
    free(b->name);
    for (int i = 0; i < b->param_count; i++) {
        free(b->param_names[i]);
    }
    free(b->param_names);
    free_behavior_node(b->body);
    free(b);
}