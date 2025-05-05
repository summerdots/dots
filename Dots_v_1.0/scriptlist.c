
#include <string.h>
#include "scriptlist.h"

static struct Script script_table[MAX_KEYWORDS];
static int script_count = 0;

void init_scriptlist() {
    script_count = 0;
}

void register_script_keyword(const char* name, char* lines[], int count) {
    if (script_count >= MAX_KEYWORDS) return;
    struct Script* s = &script_table[script_count++];
    strncpy(s->name, name, MAX_NAME_LENGTH - 1);
    s->name[MAX_NAME_LENGTH - 1] = '\0';
    s->line_count = count;
    for (int i = 0; i < count && i < MAX_LINES_PER_SCRIPT; i++) {
        strncpy(s->lines[i], lines[i], MAX_LINE_LENGTH - 1);
        s->lines[i][MAX_LINE_LENGTH - 1] = '\0';
    }
}

const struct Script* find_script_keyword(const char* name) {
    for (int i = 0; i < script_count; i++) {
        if (strcmp(script_table[i].name, name) == 0) {
            return &script_table[i];
        }
    }
    return NULL;
}

int delete_script_keyword(const char* name) {
    for (int i = 0; i < script_count; i++) {
        if (strcmp(script_table[i].name, name) == 0) {
            for (int j = i; j < script_count - 1; j++) {
                script_table[j] = script_table[j + 1];
            }
            script_count--;
            return 0;
        }
    }
    return 1;
}

int get_script_count() {
    return script_count;
}

const char* get_script_name(int index) {
    if (index >= 0 && index < script_count) {
        return script_table[index].name;
    }
    return NULL;
}

const char* get_script_line(int index, int line) {
    if (index >= 0 && index < script_count) {
        struct Script* s = &script_table[index];
        if (line >= 0 && line < s->line_count) {
            return s->lines[line];
        }
    }
    return NULL;
}
