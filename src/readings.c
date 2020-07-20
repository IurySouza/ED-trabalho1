#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "struct.h"
#include "svg.h"
#include "utils.h"
#include "qry.h"

Node *readGeo(char pathGeo[], char svgGeo[]) {
    Node *head = NULL;
    char type[3], borderC[30], fillC[30], buffer, *txt;
    int i = 0, max = 1000, id;
    float x, y, width, height, radius;
    FILE* geo = fopen(pathGeo, "r");

    if (geo == NULL) {
        printf("Um erro ocorreu ao abrir o arquivo GEO.\n");
        exit(1);
    }
    
    while (fscanf(geo, "%s", type) != EOF && i < max) {
        if (strcmp(type, "nx") == 0) {
            fscanf(geo, "%d\n", &max);
        }
        else if (strcmp(type, "c") == 0) {
            fscanf(geo, "%d %f %f %f %s %s\n", &id, &radius, &x, &y, borderC, fillC);
            head = addCircle(head, id, 'c', x, y, radius, borderC, fillC);
            i++;
        }
        else if (strcmp(type, "r") == 0) {
            fscanf(geo, "%d %f %f %f %f %s %s\n", &id, &x, &y, &width, &height, borderC, fillC);
            head = addRectangle(head, id, 'r', x, y, width, height, borderC, fillC);
            i++;
        }
        else if (strcmp(type, "t") == 0) {
            fscanf(geo, "%d %f %f %s %s", &id, &x, &y, borderC, fillC);
            buffer = getc(geo);
            int aux =  0;
            while (buffer != '\n' && buffer != EOF) {
                buffer = getc(geo);
                aux++;
            }
            fseek(geo, -aux, SEEK_CUR);
            txt = (char*) malloc(sizeof(char) * aux);
            fscanf(geo, "%[^\n]", txt);
            head = addText(head, id, 't', x, y, txt, borderC, fillC);
            free(txt);
        }
    }

    drawSvg(head, svgGeo);
    fclose(geo);
    return head;
}

Node *readQry(Node *figList, char entryPathQry[], char qryNoExtention[]) {
    char type[5], borderC[30], fillC[30], *pathSvg = NULL, *pathTxt = NULL;
    int j, k;
    float x, y;

    pathSvg = (char*) malloc((strlen(qryNoExtention) + 5) * sizeof(char));
    sprintf(pathSvg, "%s.svg", qryNoExtention);
    pathTxt = (char*) malloc((strlen(qryNoExtention) + 5) * sizeof(char));
    sprintf(pathTxt, "%s.txt", qryNoExtention);

    FILE* qry = fopen(entryPathQry, "r");
    FILE* txt = fopen(pathTxt, "w");

    if (qry == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo QRY.\n");
        exit(1);
    }

    if (txt == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo TXT.\n");
        exit(1);
    }

    while (fscanf(qry, "%s", type) != EOF) {
        if (strcmp(type, "o?") == 0) {
            fscanf(qry, "%d %d\n", &j, &k);
            fprintf(txt, "o? %d %d\n", j, k);
            intersection(txt, figList, j, k);
        }
        else if (strcmp(type, "i?") == 0) {
            fscanf(qry, "%d %f %f\n", &j, &x, &y);
            fprintf(txt, "i? %d %f %f\n", j, x, y);
            isInternal(txt, figList, x, y, j);
        }
        else if (strcmp(type, "pnt") == 0) {
            fscanf(qry, "%d %s %s\n", &j, borderC, fillC);
            fprintf(txt, "pnt %d %s %s\n", j, borderC, fillC);
            pnt(txt, figList, j, borderC, fillC);
        }
        else if (strcmp(type, "pnt*") == 0) {
            fscanf(qry, "%d %d %s %s", &j, &k, borderC, fillC);
            fprintf(txt, "pnt* %d %d %s %s\n", j, k, borderC, fillC);
            while (j <= k) {
                pnt(txt, figList, j, borderC, fillC);
                j++;
            }
        }
        else if (strcmp(type, "delf") == 0) {
            fscanf(qry, "%d", &j);
            fprintf(txt, "delf %d\n", j);
            figList = delf(txt, figList, j);
        }
        else if (strcmp(type, "delf*") == 0) {
            fscanf(qry, "%d %d", &j, &k);
            fprintf(txt, "delf* %d %d\n", j, k);
            while (j <= k) {
                figList = delf(txt, figList, j);
                j++;
            }
        }
    }
    printf("\n");

    drawSvg(figList, pathSvg);

    fclose(qry);
    fclose(txt);
    free(pathSvg);
    free(pathTxt);
    return figList;
}