#include "builtin.h"
#include "control.h"
#include "mathmod.h"
#include "lazy.h"
#include "introspect.h"
#include "modio.h"

// Load all system modules and .dotmod files
void init_all_modules() {
    register_builtin_behaviors();
    register_control_behaviors();
    register_math_behaviors();
    register_lazy_support();
    register_introspection_behaviors();
    load_dotmod_folder("modules/");
}