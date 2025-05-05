
#include <stdio.h>
#include <string.h>
#include "interpreter.h"
#include "scriptlist.h"
#include "instruction.h"
#include "behaviortable.h"

static int interactive_mode = 0;

void start_interpreter() {
    char input[256];
    interactive_mode = 1;
    while (1) {
        printf(">>> ");
        if (!fgets(input, sizeof(input), stdin)) break;
        input[strcspn(input, "\n")] = 0;
        if (parse_command(input)) break;
    }
    interactive_mode = 0;
}

int parse_command(const char* input) {
    char keyword[64];
    const char* arg = strchr(input, '(');
    if (!arg) {
        if (interactive_mode)
            printf("[error] Unknown command '%s'\n", input);
        return 0;
    }

    int len = arg - input;
    if (len >= (int)sizeof(keyword)) return 0;
    strncpy(keyword, input, len);
    keyword[len] = 0;

    const char* arg_start = arg + 1;
    const char* arg_end = strrchr(arg_start, ')');
    char param[256] = {0};
    if (arg_end && arg_end > arg_start) {
        strncpy(param, arg_start, arg_end - arg_start);
        param[arg_end - arg_start] = 0;
    }

    if (strcmp(keyword, "exit") == 0) return 1;

    const struct Script* script = find_script_keyword(keyword);
    if (script) {
        return run_script(script);
    }

    if (run_builtin(keyword, param)>=0) return 0;

    if (interactive_mode)
        printf("[error] Unknown command '%s'\n", keyword);

    return 0;
}
