#ifndef _H_QRY
#define _H_QRY
#include "struct.h"

float max(float n1, float n2);

float min(float n1, float n2);

void internalCircle(FILE* txt, Node *figList, Circ c1, Circ c2, int j, int k);

void internalRectangle(FILE* txt, Node *figList, Rect r1, Rect r2, int j, int k);

void rectXcirc(FILE* txt, Node *figList, Circ circle, Rect rectangle, int j, int k);

void intersection(FILE* txt, Node *figList, int j, int k);

void isInternal(FILE* txt, Node *figList, float x, float y, int j);

void pnt(FILE* txt, Node *figList, int j, char borderC[], char fillC[]);

Node *delf(FILE* txt, Node *figList, int j);

#endif