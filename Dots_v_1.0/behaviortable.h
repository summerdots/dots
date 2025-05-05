
#ifndef BEHAVIORTABLE_H
#define BEHAVIORTABLE_H

void register_builtin(const char* name, int (*func)(const char* arg));
int run_builtin(const char* name, const char* arg);

#endif
