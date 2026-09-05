#ifndef OTHER_H
#define OTHER_H

extern char renameValue[4096];

// define formatting ansii
#define RESET "\e[0m"
#define BOLD  "\e[1m"
#define RED   "\e[31m"

// define all needed functions
int scan(const char *alias, const char *kwicdP);

#endif