#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    char *paramEntryPath = NULL;
    char *paramGeoName = NULL;
    char *paramQryName = NULL;
    char *paramOutPath = NULL;
    int i = 1;

    while(i < argc) {
        if (strcmp(argv[i], "-e") == 0) {
            i++;
            paramEntryPath = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(paramEntryPath, argv[i]);
        }

        else if (strcmp(argv[i], "-f") == 0) {
            i++;
            paramGeoName = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(paramGeoName, argv[i]);
        }

        else if (strcmp(argv[i], "-q") == 0) {
            i++;
            paramQryName = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(paramQryName, argv[i]);
        }

        else if (strcmp(argv[i], "-o") == 0) {
            i++;
            paramOutPath = (char*) malloc((strlen(argv[i]) + 1) * sizeof(char));
            strcpy(paramOutPath, argv[i]);
        }
        i++;
    }

    manager(paramEntryPath, paramGeoName, paramOutPath, paramQryName);

    if (paramEntryPath != NULL) free(paramEntryPath);
    if (paramQryName != NULL) free(paramQryName);
    free(paramGeoName);
    free(paramOutPath);
    return 0;
}