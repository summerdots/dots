#include <stdio.h>
#include <string.h>
#include "interpreter.h"
#include "keyword.h"
#include "photolist.h"

// Main interpreter logic
void interpret(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';  // Remove trailing newline
        if (line[0] == '\0' || line[0] == '#') continue;

        if (strncmp(line, "keyword ", 8) == 0) {
            process_keyword(fp, line);
        } else if (strncmp(line, "run_print(\"", 11) == 0) {
            char name[64];
            if (sscanf(line, "run_print(\"%63[^\"]\")", name) == 1) {
                typedef char* (*str_func_t)();
                str_func_t func = (str_func_t) photolist_resolve(name);
                if (!func) {
                    fprintf(stderr, "[run_print] unknown function: %s\n", name);
                } else {
                    printf("[run_print] %s() => %s\n", name, func());
                }
            }
        } else if (strcmp(line, "list()") == 0) {
            list_functions();
        }
    }

    fclose(fp);
}

