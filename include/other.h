#ifndef OTHER_H
#define OTHER_H

extern char renameValue[4096];

// define formatting ansii
#define reset "\e[0m"
#define bold  "\e[1m"
#define red   "\e[31m"

// define all needed functions
int scan(const char *alias, const char *kwicdP);

#endif