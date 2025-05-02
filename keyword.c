// File: keyword.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "photolist.h"
#include "keywordlist.h"

// Process and register a new keyword block from a script
void process_keyword(FILE* file, const char* first_line) {
    char name[64], line[1024], code[4096] = {0};
    if (sscanf(first_line, "keyword %63s", name) != 1) return;

    // Generate source filename
    char filename[128];
    snprintf(filename, sizeof(filename), "%s.c", name);
    FILE* out = fopen(filename, "w");
    if (!out) {
        fprintf(stderr, "[keyword] failed to create %s\n", filename);
        return;
    }

    // Skip until `code: """`
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "code:") && strstr(line, "\"\"\"")) break;
    }

    // Read and store the code block
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "\"\"\"")) break;
        strcat(code, line);
        fputs(line, out);
    }
    fclose(out);

    // Compile to shared object
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "gcc -shared -fPIC -o %s.so %s.c 2>> .compile_error.log", name, name);
    if (system(cmd) != 0) {
        fprintf(stderr, "[keyword] failed to compile %s.c\n", name);
        return;
    }

    // Load compiled .so
    snprintf(filename, sizeof(filename), "./%s.so", name);
    void* handle = dlopen(filename, RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "[keyword] dlopen failed: %s\n", dlerror());
        return;
    }

    // Resolve function
    void* func = dlsym(handle, name);
    if (!func) {
        fprintf(stderr, "[keyword] dlsym failed: %s\n", dlerror());
        return;
    }

    photolist_register(name, func);         // register into photolist
    keywordlist_add(name, code, 0);            // store into keyword memory
    printf("[keyword] registered %s from %s.so\n", name, name);
}

