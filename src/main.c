#include <stdio.h>
#include "behavior.h"
#include "executor.h"
#include "modules.c"  // Unified module loader

int main() {
    printf("[Dots] Booting Dots 2.0 Runtime...\n");

    // Initialize global behavior registry
    init_behavior_registry();

    // Register all internal and external modules
    init_all_modules();

    // Execute entry behavior "start"
    printf("[Dots] Executing entry: start()\n");
    execute_behavior("start", NULL, 0);

    printf("[Dots] Program finished.\n");
    return 0;
}