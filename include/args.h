#ifndef FLAGS_H
#define FLAGS_H

#include "other.h"

// define all needed arg funcs
int append(const char *alias, const char *value, const char *kwicdP);
int copy(const char *alias, const char *kwicdP);
int print(const char *alias, const char *kwicdP);
int delAlias(const char *alias, const char *kwicdP, const char *tempKwicdP);
int ls(const char *kwicdP);

#endif