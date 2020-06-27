#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char* paramEntryPath = NULL;
    char* paramGeoName = NULL;
    char* paramQryName = NULL;
    char* paramOutPath = NULL;
    char* pathGeo = NULL;
    char* pathQry = NULL;

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

    if (paramEntryPath != NULL) {
        pathGeo = (char*) malloc((strlen(paramEntryPath) + strlen(paramGeoName) + 2) * sizeof(char));
        sprintf(pathGeo, "%s/%s", paramEntryPath, paramGeoName);

        if (paramQryName != NULL) {
            pathQry = (char*) malloc((strlen(paramEntryPath) + strlen(paramQryName) + 2) * sizeof(char));
            sprintf(pathQry, "%s/%s", paramEntryPath, paramQryName);
        }
    } else {
        pathGeo = (char*) malloc((strlen(paramGeoName) + 1) * sizeof(char));
        strcpy(pathGeo, paramGeoName);

        if (paramQryName != NULL) {
            pathQry = (char*) malloc((strlen(paramQryName) + 1) * sizeof(char));
            strcpy(pathQry, paramQryName);
        }
    }

    if (paramEntryPath != NULL) free(paramEntryPath);
    if (paramQryName != NULL) free(paramQryName);
    if (pathQry != NULL) free(pathQry);
    free(paramGeoName);
    free(paramOutPath);
    free(pathGeo);

    return 0;
}