#ifndef FLAGS_H
#define FLAGS_H

#include "other.h"

// define all needed arg funcs
void append(const char *alias, const char *value, const char *kwicdP);
void copy(const char *alias, const char *kwicdP);
void print(const char *alias, const char *kwicdP);
void delAlias(const char *alias, const char *kwicdP, const char *tempKwicdP);
void ls(const char *kwicdP);

#endif