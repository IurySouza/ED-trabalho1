#ifndef _H_STRUCT
#define _H_STRUCT

typedef struct rect {
    float x, y, width, height;
    char borderC[20];
    char fillC[20];
} Rect;

typedef struct circ {
    float x, y, radius;
    char borderC[20];
    char fillC[20];
} Circ;

typedef struct line {
    float x1, y1, x2, y2;
    char fillC[20];
} Line;

typedef struct tex {
    float x, y;
    char *msg;
    char borderC[20];
    char fillC[20];
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