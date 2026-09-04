#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/args.h"

// write a new entry with given alias and value
int append(const char *alias, const char *value, const char *kwicdP) {
    FILE *kwicd;
    kwicd = fopen(kwicdP, "a");
    if (!kwicd) { printf("Kwicd file not found.\n"); return 1; };

    fprintf(kwicd, "%s:%s\n", alias, value);
    fflush(kwicd);
    fclose(kwicd);
    
    return 0;
}

// copy a value to keyboard
int copy(const char *alias, const char *kwicdP) {
    FILE *kwicd;
    char line[4096];

    kwicd = fopen(kwicdP, "r");
    if (!kwicd) { printf("Kwicd file not found.\n"); return 1; }

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
        if(system(cmd) != 0) {
            printf("Couldn't copy to clipboard.\n");
            fclose(kwicd);
            return 1;
        }
        fclose(kwicd);
        return 0;
    }

    fclose(kwicd);
    printf("Alias not found.\n");
    return 1;
}

// output value
int print(const char *alias, const char *kwicdP) {
    FILE *kwicd;
    char line[4096];

    kwicd = fopen(kwicdP, "r");
    if (!kwicd) { printf("Kwicd file not found.\n"); return 1; }
    
    while (fgets(line, sizeof(line), kwicd)) {
        line[strcspn(line, "\r\n")] = '\0';

        char *colon = strchr(line, ':');
        if (!colon) continue;

        *colon = '\0';
        char *key = line; // alias
        char *val = colon + 1; // value

        if (strcmp(key, alias) != 0) continue; // doesn't match

        // matches
        printf("%s\n", val);
        fclose(kwicd);
        return 0;
    }

    fclose(kwicd);
    printf("Alias not found\n");
    return 1;
}

// delete an entry
int delAlias(const char *alias, const char *kwicdP, const char *tempKwicdP) {
    FILE *kwicd;
    FILE *temp;

    char line[4096];
    int cur_ln = 1;
    int del_ln = scan(alias, kwicdP);

    if (del_ln == -2) { printf("Kwicd file not found.\n"); return 1; }
    else if (del_ln == -1) { printf("Alias not found.\n"); return 1; }
    
    kwicd = fopen(kwicdP, "r");
    temp = fopen(tempKwicdP, "w");

    if (!kwicd) { printf("Kwicd file not found.\n"); return 1; }
    if (!temp) {printf("Temporary Kwicd file could not be created.\n"); fclose(kwicd); return 1; }

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

    return 0;
}

// print each line of the kwicd file
int ls(const char *kwicdP) {
    FILE *kwicd;

    char line[4096];
    kwicd = fopen(kwicdP, "r");

    if (!kwicd) { printf("Kwicd file not found.\n"); return 1; }

    while (fgets(line, sizeof(line), kwicd)) {
        printf("%s", line);
    }

    fclose(kwicd);

    return 0;
}