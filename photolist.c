#include <stdio.h>
#include <string.h>

#define MAX_FUNCS 128

typedef struct {
    char name[64];
    void* func;
} Entry;

static Entry table[MAX_FUNCS];
static int func_count = 0;

void photolist_register(const char* name, void* func) {
    if (func_count >= MAX_FUNCS) {
        fprintf(stderr, "[photolist] max limit reached\n");
        return;
    }
    strncpy(table[func_count].name, name, 63);
    table[func_count].func = func;
    func_count++;
}

void* photolist_resolve(const char* name) {
    for (int i = 0; i < func_count; ++i) {
        if (strcmp(table[i].name, name) == 0) {
            return table[i].func;
        }
    }
    return NULL;
}

void list_functions(void) {
    printf("[list] available functions:\n");
    for (int i = 0; i < func_count; i++) {
        printf("  - %s\n", table[i].name);
    }
}

