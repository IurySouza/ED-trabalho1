#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "struct.h"
#include "readings.h"

char *getFileName(char str[]) {
    char *aux = strrchr(str,'/');
    if (aux == NULL) {
        return strtok(str,".");
    }
	return strtok(&aux[1],".");
}

void manager(char paramEntryPath[], char paramGeoName[], char paramOutPath[], char paramQryName[]) {
    Node *figList = NULL;
    char *entryPathGeo = NULL;
    char *entryPathQry = NULL;
    char *filename = NULL;
    char *outPath = NULL;           // Esta variável possui o nome do arquivo sem extensão
    char *svgGeo = NULL;
    if (paramEntryPath) {
        if (paramEntryPath[strlen(paramEntryPath) - 1] != '/') {
            entryPathGeo = (char*) malloc((strlen(paramEntryPath) + strlen(paramGeoName) + 2) * sizeof(char));
            sprintf(entryPathGeo, "%s/%s", paramEntryPath, paramGeoName);
        } else {
            entryPathGeo = (char*) malloc((strlen(paramEntryPath) + strlen(paramGeoName) + 1) * sizeof(char));
            sprintf(entryPathGeo, "%s%s", paramEntryPath, paramGeoName);
        }
        if (paramQryName) {
            entryPathQry = (char*) malloc((strlen(paramEntryPath) + strlen(paramQryName) + 2) * sizeof(char));
            sprintf(entryPathQry, "%s/%s", paramEntryPath, paramQryName);
        }
    } else {
        entryPathGeo = (char*) malloc((strlen(paramGeoName) + 1) * sizeof(char));
        strcpy(entryPathGeo, paramGeoName);
        if (paramQryName) {
            entryPathQry = (char*) malloc((strlen(paramQryName) + 1) * sizeof(char));
            strcpy(entryPathQry, paramQryName);
        }
    }

    filename = getFileName(paramGeoName);

    if (paramOutPath[strlen(paramOutPath) - 1] != '/') {
        outPath = (char*) malloc((strlen(paramOutPath) + strlen(filename) + 2) * sizeof(char));
        sprintf(outPath, "%s/%s", paramOutPath, filename);
    } else {
        outPath = (char*) malloc((strlen(paramOutPath) + strlen(filename) + 1) * sizeof(char));
        sprintf(outPath, "%s%s", paramOutPath, filename);
    }

    svgGeo = (char*) malloc((strlen(outPath) + 5) * sizeof(char));
    sprintf(svgGeo, "%s.svg", outPath);
    printf("%s\n", svgGeo);

    figList = readGeo(entryPathGeo, svgGeo);

    free(entryPathGeo);
    free(outPath);
    free(svgGeo);
    if (entryPathQry) free(entryPathQry);
    deleteList(figList);
}