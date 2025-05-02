// File: keywordlist.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "keywordlist.h"
#include "photolist.h"

#define MAX_KEYWORDS 256

typedef struct {
    char name[64];
    char* code;
} KeywordEntry;

static KeywordEntry table[MAX_KEYWORDS];
static int keyword_count = 0;
static int is_loading = 0;  // Flag to prevent saving during loading phase

// Register keyword and optionally suppress printing
void keywordlist_add(const char* name, const char* code, int silent) {
    if (keyword_count >= MAX_KEYWORDS) return;

    strncpy(table[keyword_count].name, name, 63);
    table[keyword_count].code = strdup(code);
    keyword_count++;

    if (!is_loading) {
        FILE* f = fopen(".keywords.mem", "a");
        if (!f) return;
        fprintf(f, "###%s###\n%s\n\n", name, code);
        fclose(f);
    }

    // Write to .c file for compilation
    char src_path[128], so_path[128], cmd[512];
    snprintf(src_path, sizeof(src_path), "%s.c", name);
    FILE* fp = fopen(src_path, "w");
    if (!fp) return;
    fputs(code, fp);
    fclose(fp);

    snprintf(so_path, sizeof(so_path), "./%s.so", name);
    snprintf(cmd, sizeof(cmd), "gcc -shared -fPIC -o %s %s 2>> .compile_error.log", so_path, src_path);
    if (system(cmd) != 0) return;

    void* handle = dlopen(so_path, RTLD_LAZY);
    if (!handle) return;

    void* func = dlsym(handle, name);
    if (!func) return;

    photolist_register(name, func);

    if (!silent) {
        printf("[keyword] registered %s from %s\n", name, so_path);
    }
}

// Load keywords from memory file and register them silently
void keywordlist_load_from_mem() {
    is_loading = 1;

    FILE* f = fopen(".keywords.mem", "r");
    if (!f) {
        is_loading = 0;
        return;
    }

    char line[4096];
    char name[64] = "";
    char code[8192] = "";
    int in_block = 0;

    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "###", 3) == 0) {
            if (in_block) {
                keywordlist_add(name, code, 1);  // silent = true
                code[0] = '\0';
            }
            sscanf(line, "###%63[^#]###", name);
            in_block = 1;
        } else if (in_block) {
            strncat(code, line, sizeof(code) - strlen(code) - 1);
        }
    }

    if (in_block) {
        keywordlist_add(name, code, 1);  // silent = true
    }

    fclose(f);
    is_loading = 0;
}


