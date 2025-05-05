
#ifndef SCRIPTLIST_H
#define SCRIPTLIST_H

#define MAX_KEYWORDS 128
#define MAX_LINES_PER_SCRIPT 16
#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 64

struct Script {
    char name[MAX_NAME_LENGTH];
    char lines[MAX_LINES_PER_SCRIPT][MAX_LINE_LENGTH];
    int line_count;
};

void init_scriptlist();
void register_script_keyword(const char* name, char* lines[], int count);
const struct Script* find_script_keyword(const char* name);
int delete_script_keyword(const char* name);
int get_script_count();
const char* get_script_name(int index);
const char* get_script_line(int index, int line);

#endif
