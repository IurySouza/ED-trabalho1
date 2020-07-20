#include <stdio.h>
#include <stdlib.h>
#include "svg.h"
#include "struct.h"
#include "list.h"

void drawCircle(FILE* svg, float x, float y, float radius, char fillC[], char borderC[]) {
    fprintf(svg, "\t<circle cx=\"%f\" cy=\"%f\" r=\"%f\" fill=\"%s\" stroke=\"%s\" />\n", x, y, radius, fillC, borderC);
}

void drawRectangle(FILE* svg, float x, float y, float width, float height, char fillC[], char borderC[]) {
    fprintf(svg, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"%s\" stroke=\"%s\" />\n", x, y, width, height, fillC, borderC);
}

void drawLine(FILE* svg, float x1, float y1, float x2, float y2, char fillC[]) {
    fprintf(svg, "\t<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke=\"%s\" />\n", x1, y1, x2, y2, fillC);
}

void drawText(FILE* svg, float x, float y, char text[], char fillC[], char borderC[]) {
    fprintf(svg, "\t<text x=\"%f\" y=\"%f\" stroke=\"%s\" stroke-width=\"0.3\" fill=\"%s\">%s</text>\n", x, y, borderC, fillC, text);
}

void drawDashedRectangle(FILE* svg, float x, float y, float width, float height, char color[]) {
    fprintf(svg, "\t<rect x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\" fill=\"transparent\" stroke=\"%s\" stroke-width =\"1\" stroke-dasharray=\"1\" />\n", x, y, width, height, color);
}

void drawSvg(Node *head, char svgGeo[]) {
    Node *aux = head;
    FILE *svg = fopen(svgGeo, "w");
    if (svg == NULL) {
        printf("Ocorreu um erro ao abrir o arquivo SVG.\n");
        exit(1);
    }
    fprintf(svg, "<svg>\n");

    while (aux != NULL) {
        switch (aux->type) {
        case 'c':
            drawCircle(svg, aux->shape->circle.x, aux->shape->circle.y, aux->shape->circle.radius, aux->shape->circle.fillC, aux->shape->circle.borderC);
            break;
        case 'r':
            drawRectangle(svg, aux->shape->rectangle.x, aux->shape->rectangle.y, aux->shape->rectangle.width, aux->shape->rectangle.height, aux->shape->rectangle.fillC, aux->shape->rectangle.borderC);
            break;
        case 't':
            drawText(svg, aux->shape->text.x, aux->shape->text.y, aux->shape->text.msg, aux->shape->text.fillC, aux->shape->text.borderC);
            break;
        case 'l':
            drawLine(svg, aux->shape->line.x1, aux->shape->line.y1, aux->shape->line.x2, aux->shape->line.y2, aux->shape->line.fillC);
            break;
        case 'o':
            drawDashedRectangle(svg, aux->shape->rectangle.x, aux->shape->rectangle.y, aux->shape->rectangle.width, aux->shape->rectangle.height, aux->shape->rectangle.fillC);
            break;
        }
        aux = aux->next;
    }
    fprintf(svg, "</svg>");
    fclose(svg);
}