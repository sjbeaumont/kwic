/*
 * Copyright (c) 2026 Sam (sjbeaumont)
 * SPDX-License-Identifier: MIT
 * Distributed under the terms of the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

char kwicdP[256]; // used to store kwicd.txt path
char tempKwicdP[256]; // used to store kwicd-temp.txt path
char renameValue[4096]; // used to store value when renaming


#include "include/other.h"
#include "include/args.h"



static int mkdir_if_missing(const char *dir) {
    if (mkdir(dir, 0755) == 0) return 0;
    if (errno == EEXIST) return 0;
    return -1;
}

static void usage(void) {
    printf("Usage error.\n");
    exit(1);
}



int main(int argc, char *argv[]) {
    const char *home = getenv("HOME");
    if (!home || !*home) return 1;

    char dir[256];
    snprintf(dir, sizeof(dir), "%s/.local/share/kwic", home); // data dir
    if (mkdir_if_missing(dir) != 0) return 1;

    snprintf(kwicdP, sizeof(kwicdP), "%s/.local/share/kwic/kwicd.txt", home); // data file
    snprintf(tempKwicdP, sizeof(tempKwicdP), "%s/.local/share/kwic/kwicd-temp.txt", home);

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) { // make entry
            if (i + 2 >= argc) { usage(); return 1; }
            append(argv[i + 1], argv[i + 2], kwicdP);
            i += 2;
        } 
        
        else if (strcmp(argv[i], "-c") == 0) { // copy to clipboard
            if (i + 1 >= argc) { usage(); return 1; }
            copy(argv[i + 1], kwicdP);
            i += 1;
        }

        else if (strcmp(argv[i], "-r") == 0) { // rename
            if (i + 2 >= argc) { usage(); return 1; }

            delAlias(argv[i + 1], kwicdP, tempKwicdP);
            append(argv[i + 2], renameValue, kwicdP);
            i += 2;
        }

        else if (strcmp(argv[i], "ls") == 0) { ls(kwicdP); }

        else if (strcmp(argv[i], "rm" ) == 0) { // delete entry
            if (i + 1 >= argc) { usage(); return 1; }
            delAlias(argv[i + 1], kwicdP, tempKwicdP);
            i += 1;
        }

        else if (strcmp(argv[i], "clear") == 0) { // clear clipboard
            system("printf '' | wl-copy");
        } 


        else { usage(); }
    }
    return 0;
}
