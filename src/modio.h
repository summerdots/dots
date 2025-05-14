#ifndef MODIO_H
#define MODIO_H

#include "behavior.h"

// Load all .dotmod files in given folder (e.g., "modules/")
void load_dotmod_folder(const char* folder);

// Load a single .dotmod file and register the behavior
void load_dotmod_file(const char* filepath);

#endif