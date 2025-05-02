#include <stdio.h>
#include "start.h"
#include "interpreter.h"
#include "keywordlist.h"

// Entry point of Dots.
// Loads all memory-persisted keywords before interpreting the given script.
int start(int argc, char** argv) {
    // Clear previous compile errors
    FILE* errlog = fopen(".compile_error.log", "w");
    if (errlog) fclose(errlog);

    // Load remembered keywords from disk
    keywordlist_load_from_mem();

    // Check command-line args
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <source.dots>\n", argv[0]);
        return 1;
    }

    // Run interpreter on script
    interpret(argv[1]);
    return 0;
}

