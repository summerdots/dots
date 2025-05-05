
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scriptlist.h"

int heart_mode() {
    char name[128];
    printf("[HEART] Enter new keyword name: ");
    if (!fgets(name, sizeof(name), stdin)) return 1;
    name[strcspn(name, "\n")] = 0;

    printf("[HEART] Enter behavior lines for '%s'. One per line. Type 'end' to finish.\n", name);

    char* lines[32];
    static char buffer[32][256];
    int count = 0;

    while (count < 32) {
        printf("... ");
        if (!fgets(buffer[count], sizeof(buffer[count]), stdin)) break;
        buffer[count][strcspn(buffer[count], "\n")] = 0;
        if (strcmp(buffer[count], "end") == 0) break;
        lines[count] = buffer[count];
        count++;
    }

    register_script_keyword(name, lines, count);
    printf("[HEART] Registered '%s' with %d instructions.\n", name, count);
    return 0;
}
