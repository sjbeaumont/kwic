/*
 * Copyright (c) 2026 Sam (sjbeaumont)
 * SPDX-License-Identifier: MIT
 * Distributed under the terms of the MIT License.
 */

#include <stdio.h>
#include <string.h>
#include "include/other.h"

// search file for specific alias, and return the line number
int scan(const char *alias, const char *kwicdP) {  // -2 = file not found, -1 = alias not found
    FILE *kwicd;
    char line[4096];
    int ln = 1;

    kwicd = fopen(kwicdP, "r");
    if (!kwicd) return -2;

    while (fgets(line, sizeof(line), kwicd)) {
        line[strcspn(line, "\r\n")] = '\0';

        char *colon = strchr(line, ':');
        if (!colon) { ln++; continue; }

        *colon = '\0';
        char *key = line; // alias
        char *val = colon + 1; // value

        snprintf(renameValue, sizeof(renameValue), "%s", val); // save in case of renaming

        if (strcmp(key, alias) != 0) { ln++; continue; }

        fclose(kwicd);
        return ln;
    }

    fclose(kwicd);
    return -1;
}