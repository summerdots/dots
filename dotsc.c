#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

#define MAX_LINES 1024
#define MAX_LINE_LENGTH 512

typedef struct {
    char name[128];
    char* lines[MAX_LINES];
    int line_count;
} Behavior;

// Trim leading and trailing whitespace (used only for name parsing)
char* trim(char* s) {
    while (isspace(*s)) s++;
    if (*s == 0) return s;
    char* end = s + strlen(s) - 1;
    while (end > s && isspace(*end)) *end-- = '\0';
    return s;
}

// Write a compiled behavior block into a .dotmod file
void save_behavior(const Behavior* b) {
    char path[256];
    snprintf(path, sizeof(path), "modules/%s.dotmod", b->name);
    FILE* out = fopen(path, "w");
    if (!out) {
        printf("[dotsc] Failed to write: %s\n", path);
        return;
    }

    for (int i = 0; i < b->line_count; i++) {
        fprintf(out, "%s", b->lines[i]);  // Keep original line formatting (with newline)
        free(b->lines[i]);
    }

    fclose(out);
    printf("[dotsc] Compiled: %s → %s\n", b->name, path);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <input.dots>\n", argv[0]);
        return 1;
    }

    struct stat st = {0};
    if (stat("modules", &st) == -1) {
        mkdir("modules", 0700);
    }

    FILE* in = fopen(argv[1], "r");
    if (!in) {
        printf("[dotsc] Cannot open %s\n", argv[1]);
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    Behavior current;
    int inside = 0;

    while (fgets(line, sizeof(line), in)) {
        // Copy a trimmed version for parsing (but keep original line)
        char namebuf[512];
        strcpy(namebuf, line);
        char* trimmed = trim(namebuf);

        // Skip comments or empty lines
        if (strncmp(trimmed, "//", 2) == 0 || trimmed[0] == '\0') continue;

        if (strncmp(trimmed, "start*:", 7) == 0) {
            // New behavior block starts
            if (inside) {
                save_behavior(&current);
            }
            memset(&current, 0, sizeof(Behavior));
            sscanf(trimmed, "start*: %127[^ (:{\n]", current.name);
            current.lines[current.line_count++] = strdup(line);  // Keep original line
            inside = 1;
        } else if (inside) {
            // Add all inner lines as-is (with original formatting)
            current.lines[current.line_count++] = strdup(line);
        }
    }

    // Save the last block if open
    if (inside) {
        save_behavior(&current);
    }

    fclose(in);
    printf("[dotsc] Compilation finished.\n");
    return 0;
}