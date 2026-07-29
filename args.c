/*
 * Copyright (c) 2026 Sam (sjbeaumont)
 * SPDX-License-Identifier: MIT
 * Distributed under the terms of the MIT License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/args.h"

void append(const char *alias, const char *value, const char *kwicdP) {
    FILE *kwicd;
    kwicd = fopen(kwicdP, "a");
    if (!kwicd) { printf("Kwicd file not found."); exit(1); };

    fprintf(kwicd, "%s:%s\n", alias, value);
    fflush(kwicd);
    fclose(kwicd);
}

void copy(const char *alias, const char *kwicdP) {
    FILE *kwicd;
    char line[4096];

    kwicd = fopen(kwicdP, "r");
    if (!kwicd) { printf("Kwicd file not found."); exit(1); }

    while (fgets(line, sizeof(line), kwicd)) {
        line[strcspn(line, "\r\n")] = '\0';

        char *colon = strchr(line, ':');
        if (!colon) continue;

        *colon = '\0';
        char *key = line; // alias
        char *val = colon + 1; // value


        if (strcmp(key, alias) != 0) continue; // doesn't match

        // matches:
        char cmd[8192];
        snprintf(cmd, sizeof(cmd), "wl-copy '%s'", val);
        system(cmd);
        break;
    }

    fclose(kwicd);
}

void delAlias(const char *alias, const char *kwicdP, const char *tempKwicdP) {
    FILE *kwicd;
    FILE *temp;

    char line[4096];
    int cur_ln = 1;
    int del_ln = scan(alias, kwicdP);

    if (del_ln == -2) { printf("Kwicd file not found.\n"); exit(1); }
    else if (del_ln == -1) { printf("Alias not found.\n"); exit(1); }
    
    kwicd = fopen(kwicdP, "r");
    temp = fopen(tempKwicdP, "w");

    if (!kwicd) { printf("Kwicd file not found."); exit(1); }
    if (!temp) {printf("Temporary Kwicd file could not be created."); exit(1); }

    while (fgets(line, sizeof(line), kwicd)) {
        if (cur_ln != del_ln) {
            fputs(line, temp);
        }
        cur_ln++;
    }

    fclose(kwicd);
    fclose(temp);

    remove(kwicdP);
    rename(tempKwicdP, kwicdP);
}

void ls(const char *kwicdP) {
    FILE *kwicd;

    char line[4096];
    kwicd = fopen(kwicdP, "r");

    if (!kwicd) { printf("Kwicd file not found."); exit(1); }

    while (fgets(line, sizeof(line), kwicd)) {
        printf("%s", line);
    }

    fclose(kwicd);
}