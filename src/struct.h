#ifndef _H_STRUCT
#define _H_STRUCT

typedef struct rect {
    float x, y, width, height;
    char borderC[30];
    char fillC[30];
} Rect;

typedef struct circ {
    float x, y, radius;
    char borderC[30];
    char fillC[30];
} Circ;

typedef struct line {
    float x1, y1, x2, y2;
    char fillC[30];
} Line;

typedef struct tex {
    float x, y;
    char *msg;
    char borderC[30];
    char fillC[30];
} Tex;

typedef union shape {
    Rect rectangle;
    Circ circle;
    Line line;
    Tex text;
} Shape;

typedef struct node {
    char type;
    int id;
    Shape *shape;
    struct node *next;
} Node;

#endif