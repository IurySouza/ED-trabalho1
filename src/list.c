#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

Node *init() {
    return NULL;
}

Node *addCircle(Node *head, int id, char type, float x, float y, float radius, char borderC[], char fillC[]) {
    Node *new, *aux;
    if (head == NULL) {
        head = (Node*) malloc(sizeof(Node));
        head->id = id;
        head->type = type;
        head->shape = NULL;
        head->next = NULL;
        new = head;
    } else {
        aux = head;

        while(aux->next != NULL) {
            aux = aux->next;
        }

        new = (Node*) malloc(sizeof(Node));
        new->id = id;
        new->type = type;
        new->shape = NULL;
        new->next = NULL;
        aux->next = new;
    }

    new->shape = (Shape*) malloc(sizeof(Shape));
    new->shape->circle.x = x;
    new->shape->circle.y = y;
    new->shape->circle.radius = radius;
    strcpy(new->shape->circle.borderC, borderC);
    strcpy(new->shape->circle.fillC, fillC);
    return head;
}

Node *addRectangle(Node *head, int id, char type, float x, float y, float width, float height, char borderC[], char fillC[]) {
    Node *new, *aux;
    if (head == NULL) {
        head = (Node*) malloc(sizeof(Node));
        head->id = id;
        head->type = type;
        head->shape = NULL;
        head->next = NULL;
        new = head;
    } else {
        aux = head;

        while(aux->next != NULL) {
            aux = aux->next;
        }

        new = (Node*) malloc(sizeof(Node));
        new->id = id;
        new->type = type;
        new->shape = NULL;
        new->next = NULL;
        aux->next = new;
    }

    new->shape = (Shape*) malloc(sizeof(Shape));
    new->shape->rectangle.x = x;
    new->shape->rectangle.y = y;
    new->shape->rectangle.width = width;
    new->shape->rectangle.height = height;
    strcpy(new->shape->rectangle.borderC, borderC);
    strcpy(new->shape->rectangle.fillC, fillC);
    return head;
}

Node *addLine(Node *head, int id, char type, float x1, float y1, float x2, float y2, char fillC[]) {
    Node *new, *aux;
    if (head == NULL) {
        head = (Node*) malloc(sizeof(Node));
        head->id = id;
        head->type = type;
        head->shape = NULL;
        head->next = NULL;
        new = head;
    } else {
        aux = head;

        while(aux->next != NULL) {
            aux = aux->next;
        }

        new = (Node*) malloc(sizeof(Node));
        new->id = id;
        new->type = type;
        new->shape = NULL;
        new->next = NULL;
        aux->next = new;
    }

    new->shape = (Shape*) malloc(sizeof(Shape));
    new->shape->line.x1 = x1;
    new->shape->line.y1 = y1;
    new->shape->line.x2 = x2;
    new->shape->line.y2 = y2;
    strcpy(new->shape->line.fillC, fillC);
    return head;
}

Node *addText(Node *head, int id, char type, float x, float y, char paramText[], char borderC[], char fillC[]) {
    Node *new, *aux;
    if (head == NULL) {
        head = (Node*) malloc(sizeof(Node));
        head->id = id;
        head->type = type;
        head->shape = NULL;
        head->next = NULL;
        new = head;
    } else {
        aux = head;

        while(aux->next != NULL) {
            aux = aux->next;
        }

        new = (Node*) malloc(sizeof(Node));
        new->id = id;
        new->type = type;
        new->shape = NULL;
        new->next = NULL;
        aux->next = new;
    }

    new->shape = (Shape*) malloc(sizeof(Shape));
    new->shape->text.msg = (char*) malloc((strlen(paramText) + 1) * sizeof(char));
    new->shape->text.x = x;
    new->shape->text.y = y;
    strcpy(new->shape->text.msg, paramText);
    strcpy(new->shape->text.borderC, borderC);
    strcpy(new->shape->text.fillC, fillC);
    return head;
}

Node *deleteElement(Node *head, int id) {
    Node *current, *previous;
    current = head;
    previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("\nO elemento de id %d nao foi encontrado.", id);
        return head;
    }

    if (previous == NULL) {
        if (current->type == 't') {
            free(current->shape->text.msg);
        }
        free(current->shape);
        free(current);
        printf("\nO elemento de id %d foi deletado com sucesso.", id);
        head = head->next;
        return head;
    }

    else {
        previous->next = current->next;
        if (current->type == 't') {
            free(current->shape->text.msg);
        }
        free(current->shape);
        free(current);
        printf("\nO elemento de id %d foi deletado com sucesso.", id);
        return head;
    }
}

Node *search(Node *head, int id) {
    Node *aux = head;
    while(aux != NULL) {
        if (aux->id == id) {
            return aux;
        }
        aux = aux->next;
    }
    return NULL;
}

void printList(Node *head) {
    Node *aux = head;
    while(aux != NULL) {
        printf("\nid: %d\ttype: %c", aux->id, aux->type);
        if (aux->type == 't') {
            printf("\n%s", aux->shape->text.msg);
        }
        aux = aux->next;
    }
}

void deleteList(Node *head) {
    Node *aux = head;
    while (aux != NULL) {
        head = head->next;
        if (aux->type == 't') {
            free(aux->shape->text.msg);
        }
        free(aux->shape);
        free(aux);
        aux = head;
    }
}