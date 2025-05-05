
#ifndef BUILTIN_H
#define BUILTIN_H

int builtin_print(const char* arg);
int builtin_shell(const char* arg);
int builtin_save(const char* arg);
int builtin_define(const char* arg);
int builtin_exit(const char* arg);

void register_builtin_keywords();

#endif
