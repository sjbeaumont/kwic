#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

// declare global variables
char kwicdP[256];
char tempKwicdP[256];
char renameValue[4096];


#include "include/other.h"
#include "include/args.h"


// create `kwic` folder if not found
static int mkdir_if_missing(const char *dir) {
    if (mkdir(dir, 0755) == 0) return 0;
    if (errno == EEXIST) return 0;
    return -1;
}

// user usage error
static void usage(void) {
    printf("Usage error.\n");
    exit(1);
}



int main(int argc, char *argv[]) {
    const char *home = getenv("HOME"); // home (~) dir
    if (!home || !*home) return 1;

    char dir[256];
    snprintf(dir, sizeof(dir), "%s/.local/share/kwic", home);
    if (mkdir_if_missing(dir) != 0) return 1;

    // assign paths to kwicd files
    snprintf(kwicdP, sizeof(kwicdP), "%s/.local/share/kwic/kwicd.txt", home);
    snprintf(tempKwicdP, sizeof(tempKwicdP), "%s/.local/share/kwic/kwicd-temp.txt", home);

    for (int i = 1; i < argc; i++) {

        // make new entry
        if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "new") == 0) {
            if (i + 2 >= argc) { usage(); return 1; } // this ensures there are two extra arg for the entry alias and value
            append(argv[i + 1], argv[i + 2], kwicdP);
            i += 2;
        } 
        
        // copy entry to clipboard
        else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "copy") == 0) {
            if (i + 1 >= argc) { usage(); return 1; } // this does the same but for one extra arg
            copy(argv[i + 1], kwicdP);
            i += 1;
        }

        // rename an alias
        else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "rename") == 0) {
            if (i + 2 >= argc) { usage(); return 1; }

            delAlias(argv[i + 1], kwicdP, tempKwicdP);
            append(argv[i + 2], renameValue, kwicdP);
            i += 2;
        }

        // output value - see README.md for example usage
        else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "print") == 0) {
            if (i + 1 >= argc) { usage(); return 1; }
            print(argv[i + 1], kwicdP);
            i++;
        }

        // list all entries
        else if (strcmp(argv[i], "ls") == 0) { ls(kwicdP); }

        // delete entry
        else if (strcmp(argv[i], "rm") == 0) {
            if (i + 1 >= argc) { usage(); return 1; }
            delAlias(argv[i + 1], kwicdP, tempKwicdP);
            i += 1;
        }

        // clear clipboard
        else if (strcmp(argv[i], "clear") == 0) {
            if (system("printf '' | wl-copy") != 0) { // err clearing clipboard
                printf("Couldn't clear clipboard.");
                return 1;
            }
        } 


        else { usage(); }
    }
    return 0;
}
