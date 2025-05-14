#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <stdbool.h>

// Represents a name-value argument pair (currently only value is used)
typedef struct {
    char* name;
    char* value;
} Argument;

// A node in a behavior's body (i.e., a single behavior call like print("hi"))
typedef struct BehaviorNode {
    char* name;                // Name of the behavior to call
    Argument* args;           // List of arguments
    int arg_count;            // Number of arguments
    bool is_lazy;             // Whether this node is lazily evaluated
    struct BehaviorNode* next; // Next node in the behavior sequence
} BehaviorNode;

// Forward declarations for context struct
struct ExecutionContext;

// A full behavior definition (i.e., one start* block)
typedef struct Behavior {
    char* name;                      // Behavior name
    char** param_names;             // Formal parameter names
    int param_count;                // Number of parameters
    BehaviorNode* body;             // Sequence of body instructions
    bool is_pure;                   // Optional: purity flag
    void (*exec_fn)(struct Behavior*, struct ExecutionContext*); // Executable C function (for builtins)
} Behavior;

// Global registry of all behaviors (both builtin and user-defined)
typedef struct {
    Behavior** list;
    int count;
    int capacity;
} BehaviorRegistry;

// Core API
Behavior* create_behavior(const char* name, char** params, int param_count, BehaviorNode* body);
BehaviorNode* create_behavior_node(const char* name, Argument* args, int arg_count, bool is_lazy);
void register_behavior(Behavior* behavior);
Behavior* find_behavior(const char* name);
void free_behavior(Behavior* behavior);
void free_behavior_node(BehaviorNode* node);
void init_behavior_registry();

// Accessor: get pointer to global behavior registry (read-only)
const BehaviorRegistry* get_behavior_registry();
#endif