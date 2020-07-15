#ifndef _H_SVG
#define _H_SVG

void startSVG(char pathSVG[]);

void endSVG(char pathSVG[]);

void drawCircle(char pathSVG[], float x, float y, float radius, char borderC[], char fillC[]);

void drawRectangle(char pathSVG[], float x, float y, float width, float height, char borderC[], char fillC[]);

void drawLine(char pathSVG[], float x1, float y1, float x2, float y2, char borderC[], char fillC[]);

char drawText(char pathSVG[], float x, float y, char borderC[], char fillC[], char text[]);

#endif