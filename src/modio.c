#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "modio.h"
#include "behavior.h"

// Trim leading/trailing whitespace
char* trim(char* s) {
    while (*s == ' ' || *s == '\t' || *s == '\n') s++;
    char* end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\t' || *end == '\n')) *end-- = '\0';
    return s;
}

// Load and parse a single .dotmod file
void load_dotmod_file(const char* filepath) {
    FILE* f = fopen(filepath, "r");
    if (!f) {
        printf("[modio] Failed to open file: %s\n", filepath);
        return;
    }

    char line[512];
    char* name = NULL;
    char* params[16];
    int param_count = 0;
    BehaviorNode* body_head = NULL;
    BehaviorNode* body_tail = NULL;

    while (fgets(line, sizeof(line), f)) {
        char* l = trim(line);

        if (strncmp(l, "start*:", 7) == 0) {
            // Reset for new behavior
            name = NULL;
            param_count = 0;

            char* def = trim(l + 7);
            char* paren = strchr(def, '(');
            if (!paren) continue;
            *paren = '\0';
            name = strdup(trim(def));

            char* args_raw = paren + 1;
            char* closing = strchr(args_raw, ')');
            if (closing) *closing = '\0';

            char* token = strtok(args_raw, ",");
            while (token && param_count < 16) {
                params[param_count++] = strdup(trim(token));
                token = strtok(NULL, ",");
            }

        } else if (strlen(l) > 0 && name) {
            char* paren = strchr(l, '(');
            if (!paren) continue;
            *paren = '\0';
            char* behavior_name = trim(l);
            char* args_raw = paren + 1;
            char* closing = strchr(args_raw, ')');
            if (closing) *closing = '\0';

            Argument* args = malloc(sizeof(Argument) * 8);
            int ac = 0;

            char* token = strtok(args_raw, ",");
            while (token && ac < 8) {
                args[ac].name = strdup("");
                args[ac].value = strdup(trim(token));
                ac++;
                token = strtok(NULL, ",");
            }

            BehaviorNode* node = create_behavior_node(behavior_name, args, ac, false);
            for (int i = 0; i < ac; i++) {
                free(args[i].name);
                free(args[i].value);
            }
            free(args);

            if (!body_head) {
                body_head = node;
                body_tail = node;
            } else {
                body_tail->next = node;
                body_tail = node;
            }
        }
    }

    if (name) {
        Behavior* b = create_behavior(name, params, param_count, body_head);
        register_behavior(b);
        printf("[modio] Loaded: %s\n", name);

        // free param names
        for (int i = 0; i < param_count; i++) {
            free(params[i]);
        }
    }

    fclose(f);
}

// Load all .dotmod files from directory
void load_dotmod_folder(const char* folder) {
    DIR* dir = opendir(folder);
    if (!dir) {
        printf("[modio] Cannot open module folder: %s\n", folder);
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir))) {
        if (strstr(entry->d_name, ".dotmod")) {
            char path[512];
            snprintf(path, sizeof(path), "%s/%s", folder, entry->d_name);
            load_dotmod_file(path);
        }
    }

    closedir(dir);
}