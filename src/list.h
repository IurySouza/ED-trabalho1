#ifndef _H_LIST
#define _H_LIST
#include "struct.h"

Node *init();

Node *addCircle(Node *head, int id, char type, float x, float y, float radius, char borderC[], char fillC[]);

Node *addRectangle(Node *head, int id, char type, float x, float y, float width, float height, char borderC[], char fillC[]);

Node *addLine(Node *head, int id, char type, float x1, float y1, float x2, float y2, char fillC[]);

Node *addText(Node *head, int id, char type, float x, float y, char text[], char borderC[], char fillC[]);

Node *deleteElement(Node *head, int id);

Node *search(Node *head, int id);

Node *search(Node *head, int id);

void printList(Node *head);

void deleteList(Node *head);

#endif