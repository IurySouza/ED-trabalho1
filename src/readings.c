#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "struct.h"
#include "svg.h"
#include "utils.h"

Node *readGeo(char pathGeo[], char svgGeo[]) {
    Node *head = NULL;
    char type[3], borderC[20], fillC[20], buffer, *txt;
    int i = 0, max = 1000, id;
    float x, y, width, height, radius;
    FILE* geo = fopen(pathGeo, "r");

    if (geo == NULL) {
        printf("Um erro ocorreu.\n");
        exit(1);
    }
    
    while (!feof(geo) && i < max) {
        fscanf(geo, "%s", type);
        // printf("%s\n", type);
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