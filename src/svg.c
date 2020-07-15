#include <stdio.h>
#include "svg.h"

void startSVG(char pathSVG[]) {
    FILE* arq = fopen(pathSVG, "w");
    fprintf(arq, "<svg>\n");
    printf("\nok");
    fclose(arq);
}

void endSVG(char pathSVG[]) {
    FILE* arq = fopen(pathSVG, "a");
    fprintf(arq, "</svg>");
    fclose(arq);
}