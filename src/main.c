#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "svg.h"
#include "struct.h"

int main(int argc, char *argv[]) {
    char *paramEntryPath = NULL;
    char *paramGeoName = NULL;
    char *paramQryName = NULL;
    char *paramOutPath = NULL;
    char *pathGeo = NULL;
    char *pathQry = NULL;
    Node *head;
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

    head = init();
    head = addCircle(head, 0, 'c', 1, 1, 5, "a", "b");
    head = addRectangle(head, 1, 'r', 5, 4, 2, 7, "s", "c");
    head = addLine(head, 2, 'l', 5, 5, 7, 7, "as", "sa");
    head = addText(head, 3, 't', 12, 13, "msg msg", "oi", "casada");
    head = deleteElement(head, 0);
    printList(head);
    deleteList(head);

    if (paramEntryPath != NULL) free(paramEntryPath);
    if (paramQryName != NULL) free(paramQryName);
    if (pathQry != NULL) free(pathQry);
    free(paramGeoName);
    free(paramOutPath);
    free(pathGeo);

    return 0;
}