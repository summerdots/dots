#ifndef DOTS_PHOTOLIST_H
#define DOTS_PHOTOLIST_H

// Register a function with a given name
void photolist_register(const char* name, void* func);

// Resolve function pointer by name
void* photolist_resolve(const char* name);

// Print all registered function names
void list_functions(void);

#endif
