
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include "scriptlist.h"
#include "memory.h"

// External behavior registration table (to be added later)
void register_builtin(const char* name, int (*func)(const char* arg));

int builtin_print(const char* arg) {
    if (arg) {
        printf("%s\n", arg);
        fflush(stdout);
    }
    return 0;
}

int builtin_shell(const char* arg) {
    if (arg) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "/bin/bash -c \"%s\"", arg);
        FILE* fp = popen(cmd, "r");
        if (fp) {
            char buffer[256];
            while (fgets(buffer, sizeof(buffer), fp)) {
                printf("%s", buffer);
            }
            pclose(fp);
        }
    }
    return 0;
}

int builtin_save(const char* arg) {
    (void)arg;
    save_keywords();
    return 0;
}

int builtin_exit(const char* arg) {
    (void)arg;
    return 1;
}

int builtin_define(const char* arg) {
    (void)arg;
    extern int heart_mode();
    return heart_mode();
}

void register_builtin_keywords() {
    register_builtin("print", builtin_print);
    register_builtin("shell", builtin_shell);
    register_builtin("save", builtin_save);
    register_builtin("define", builtin_define);
    register_builtin("exit", builtin_exit);
}
