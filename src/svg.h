#ifndef _H_SVG
#define _H_SVG
#include "struct.h"

void drawCircle(FILE* svg, float x, float y, float radius, char borderC[], char fillC[]);

void drawRectangle(FILE* svg, float x, float y, float width, float height, char borderC[], char fillC[]);

void drawLine(FILE* svg, float x1, float y1, float x2, float y2, char fillC[]);

void drawText(FILE* svg, float x, float y, char borderC[], char fillC[], char text[]);

void drawDashedRectangle(FILE* svg, float x, float y, float width, float height, char color[]);

void drawSvg(Node *head, char svgGeo[]);

#endif