#ifndef _H_STRUCT
#define _H_STRUCT

typedef struct Rect {
    float x, y, width, height;
    char borderC[20];
    char fillC[20];
} rect;

typedef struct Circ {
    float x, y, radius;
    char borderC[20];
    char fillC[20];
} circ;

typedef struct Tex {
    float x, y;
    char text[255];
    char borderC[20];
    char fillC[20];
} tex;

typedef union Shape {
    rect rectangle;
    circ circle;
    tex text;
} Shape;

typedef struct Node {
    char type;
    int id;
    Shape* shape;
    struct Node* next;
} node;

#endif