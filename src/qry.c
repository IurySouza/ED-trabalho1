#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "struct.h"

float max(float n1, float n2) {
    if (n1 > n2) {
        return n1;
    }
    return n2;
}

float min(float n1, float n2) {
    if (n1 > n2) {
        return n2;
    }
    return n1;
}

void internalCircle(FILE* txt, Node *figList, Circ c1, Circ c2, int j, int k) {
    float distance, x, y, width, height;
    distance = sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y, 2));
    x = min(c1.x - c1.radius, c2.x - c2.radius);
    width = max(c1.x + c1.radius, c2.x + c2.radius) - x;
    y = min(c1.y - c1.radius, c2.y - c2.radius);
    height = max(c1.y + c1.radius, c2.y + c2.radius) - y;
    if (distance <= c2.radius + c1.radius) {
        fprintf(txt, "%d: circle %d: circle sim\n", j, k);
        addRectangle(figList, -1, 'r', x, y, width, height, "black", "transparent");
    } else{
        fprintf(txt, "%d: circle %d: circle nao\n", j, k);
        addRectangle(figList, -1, 'o', x, y, width, height, "black", "transparent");
    }
}

void internalRectangle(FILE* txt, Node *figList, Rect r1, Rect r2, int j, int k) {
    float x, width, y, height;
    x = min(r1.x, r2.x);
    width = max(r1.x + r1.width, r2.x + r2.width) - x;
    y = min(r1.y, r2.y);
    height = max(r1.y + r1.height, r2.y + r2.height) - y;
    if (width <= r1.width + r2.width && height <= r1.height + r2.height) {
        fprintf(txt, "%d: rectangle %d: rectangle sim\n", j, k);
        addRectangle(figList, -1, 'r', x, y, width, height, "black", "transparent");
    } else {
        fprintf(txt, "%d: rectangle %d: rectangle nao\n", j, k);
        addRectangle(figList, -1, 'o', x, y, width, height, "black", "transparent");
    }
}

void rectXcirc(FILE* txt, Node *figList, Circ circle, Rect rectangle, int j, int k) {
    float deltaX, deltaY, x, y, width, height;
    if(circle.x > rectangle.x){
        deltaX = pow(rectangle.x + rectangle.width - circle.x, 2);
    } else {
        deltaX = pow(rectangle.x - circle.x, 2);
    }

    if(circle.y > rectangle.y){
        deltaY = pow(rectangle.y + rectangle.height - circle.y, 2);
    } else {
        deltaY = pow(rectangle.y - circle.y, 2);
    }

    x = min(rectangle.x, circle.x - circle.radius);
    width = max(rectangle.x + rectangle.width, circle.x + circle.radius) - x;
    y = min(rectangle.y, circle.y - circle.radius);
    height = max(rectangle.y + rectangle.height, circle.y + circle.radius) - y;

    if (sqrt(deltaX + deltaY) <= circle.radius){
        fprintf(txt, "%d: circulo %d: retangulo sim\n", j, k);
        addRectangle(figList, -1, 'r', x, y, width, height, "black", "transparent");
    } else {
        fprintf(txt, "%d: circulo %d: retangulo nao\n", j, k);
        addRectangle(figList, -1, 'o', x, y, width, height, "black","transparent");
    }
}

void intersection(FILE* txt, Node *figList, int j, int k) {
    Node *fig1 = search(figList, j);
    Node *fig2 = search(figList, k);

    if (fig1->type == 'c' && fig2->type == 'c') {
        internalCircle(txt, figList, fig1->shape->circle, fig2->shape->circle, j, k);
    } else if (fig1->type == 'r' && fig2->type == 'r') {
        internalRectangle(txt, figList, fig1->shape->rectangle, fig2->shape->rectangle, j, k);
    } else if (fig1->type == 'c' && fig2->type == 'r') {
        rectXcirc(txt, figList, fig1->shape->circle, fig2->shape->rectangle, j, k);
    } else {
        rectXcirc(txt, figList, fig2->shape->circle, fig1->shape->rectangle, j, k);
    }
}

void isInternal(FILE* txt, Node *figList, float x, float y, int j) {
    Node *aux = search(figList, j);
    char color[10];
    if (aux->type == 'c') {
        float distance = sqrt(pow(x - aux->shape->circle.x, 2) + pow(y - aux->shape->circle.y, 2));
        if (aux->shape->circle.radius > distance) {
            fprintf(txt, "%d: circle interno\n", j);
            strcpy(color, "blue");
        } else {
            fprintf(txt, "%d: circle nao interno\n",j);
            strcpy(color, "magenta");
        }
        addLine(figList, -1, 'l', x, y, aux->shape->circle.x, aux->shape->circle.y, color);
    } else {
        float deltaX = x - aux->shape->circle.x;
        float deltaY = y - aux->shape->circle.y;
        if (deltaX > 0 && deltaX < aux->shape->rectangle.width && deltaY > 0 && deltaY < aux->shape->rectangle.height) {
            fprintf(txt, "%d: rectangle interno\n",j);
            strcpy(color,"blue");
        } else {
            fprintf(txt, "%d: rectangle nao interno\n",j);
            strcpy(color,"magenta");
        }
        addLine(figList, -1, 'l', x, y, aux->shape->rectangle.x + aux->shape->rectangle.width/2, aux->shape->rectangle.y + aux->shape->rectangle.height/2, color);    
    }
    addCircle(figList, -1, 'c', x, y, 1, color, color);
}

void pnt(FILE* txt, Node *figList, int j, char borderC[], char fillC[]) {
    Node *aux = search(figList, j);
    if (aux->type == 'c') {
        strcpy(aux->shape->circle.borderC, borderC);
        strcpy(aux->shape->circle.fillC, fillC);
        fprintf(txt, "%f %f\n", aux->shape->circle.x, aux->shape->circle.y);
    } else if (aux->type == 'r') {
        strcpy(aux->shape->rectangle.borderC, borderC);
        strcpy(aux->shape->rectangle.fillC, fillC);
        fprintf(txt, "%f %f\n", aux->shape->rectangle.x, aux->shape->rectangle.y);
    } else {
        strcpy(aux->shape->text.borderC, borderC);
        strcpy(aux->shape->text.fillC, fillC);
        fprintf(txt, "%f %f\n", aux->shape->text.x, aux->shape->text.y);
    }
}

Node *delf(FILE* txt, Node *figList, int j) {
    Node *aux = search(figList, j);
    if (aux != NULL) {
        if (aux->type == 'c') {
            fprintf(txt, "circle x: %f y: %f r: %f borda: %s preeenchimento: %s\n", aux->shape->circle.x, aux->shape->circle.y, aux->shape->circle.radius, aux->shape->circle.borderC, aux->shape->circle.fillC);
        } else if (aux->type == 'r') {
            fprintf(txt, "rectangle x: %f y: %f largura: %f altura: %f borda: %s preenchimento: %s\n", aux->shape->rectangle.x, aux->shape->rectangle.y, aux->shape->rectangle.width, aux->shape->rectangle.height, aux->shape->rectangle.borderC, aux->shape->rectangle.fillC);
        } else {
            fprintf(txt, "texto x: %f y: %f borda: %s preenchimento: %s texto: %s\n", aux->shape->text.x, aux->shape->text.y, aux->shape->text.borderC, aux->shape->text.fillC, aux->shape->text.msg);
        }
        figList = deleteElement(figList, j);
    }
    return figList;
}