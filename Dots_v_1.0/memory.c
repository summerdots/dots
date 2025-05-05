
#include <stdio.h>
#include <string.h>
#include "memory.h"
#include "scriptlist.h"

void save_keywords() {
    FILE* f = fopen(".keywords.mem", "w");
    if (!f) return;
    int count = get_script_count();
    for (int i = 0; i < count; i++) {
        const char* name = get_script_name(i);
        fprintf(f, "%s\n", name);
        for (int j = 0; j < 32; j++) {
            const char* line = get_script_line(i, j);
            if (!line) break;
            fprintf(f, "%s\n", line);
        }
        fprintf(f, "@\n");
    }
    fclose(f);
}

void load_keywords() {
    FILE* f = fopen(".keywords.mem", "r");
    if (!f) return;

    char name[128];
    char* lines[32];
    static char buffer[32][256];
    int count = 0;
    int reading = 0;

    while (fgets(buffer[count], sizeof(buffer[count]), f)) {
        buffer[count][strcspn(buffer[count], "\n")] = 0;

        if (strcmp(buffer[count], "@") == 0) {
            register_script_keyword(name, lines, count);
            count = 0;
            reading = 0;
        } else if (!reading) {
            strncpy(name, buffer[count], sizeof(name));
            name[sizeof(name) - 1] = 0;
            count = 0;
            reading = 1;
        } else {
            lines[count] = buffer[count];
            count++;
        }
    }

    fclose(f);
}
