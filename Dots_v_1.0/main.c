
#include "interpreter.h"
#include "scriptlist.h"
#include "memory.h"
#include "builtin.h"

int main() {
    init_scriptlist();
    load_keywords();
    register_builtin_keywords();
    start_interpreter();
    return 0;
}
