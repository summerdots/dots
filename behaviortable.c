
#include <string.h>
#include <stdio.h>
#include "behaviortable.h"

#define MAX_BUILTINS 32
#define NAME_LEN 64

struct Builtin {
    char name[NAME_LEN];
    int (*func)(const char*);
};

static struct Builtin table[MAX_BUILTINS];
static int count = 0;

void register_builtin(const char* name, int (*func)(const char* arg)) {
    if (count >= MAX_BUILTINS) return;
    strncpy(table[count].name, name, NAME_LEN - 1);
    table[count].name[NAME_LEN - 1] = '\0';
    table[count].func = func;
    count++;
}

int run_builtin(const char* name, const char* arg) {
    for (int i = 0; i < count; i++) {
        if (strcmp(name, table[i].name) == 0) {
            return table[i].func(arg);
        }
    }
    return -1;
}
