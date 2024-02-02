#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "./file.h"

typedef struct maillon {
    int elem;
    struct maillon* suivant;

} maillon_t;

struct file {
    maillon_t* tete;
    maillon_t* queue;
};

file_t* file_vide() {
    file_t* f = malloc(sizeof(file_t));
    f->tete = NULL;
    f->queue = NULL;
    return f;
};

bool est_file_vide(file_t* f) {
    return f->tete == NULL;
};

void enfiler(file_t* f, int x) {
    if (f->tete == NULL) {
        f->tete = malloc(sizeof(maillon_t));
        f->tete->elem = x;
        f->queue = f->tete;
        f->queue->suivant = NULL;

    } else {
        f->queue->suivant = malloc(sizeof(maillon_t));
        f->queue = f->queue->suivant;
        f->queue->elem = x;
        f->queue->suivant = NULL;

    }
};

int defiler(file_t* f) {
    assert(f->tete != NULL);

    int val = f->tete->elem;

    maillon_t* temp = f->tete;
    f->tete = f->tete->suivant;
    free(temp);

    return val;
};

void free_file(file_t* f) {
    while (f->tete != NULL) {
        maillon_t* temp = f->tete;
        f->tete = temp->suivant;
        free(temp);
    }
    free(f);
};

void affiche_file(file_t* f) {
    maillon_t* temp = f->tete;
    while (temp != NULL) {
        printf("%d", temp->elem);
        temp = temp->suivant;

        if (temp != NULL) {
            printf(" <- ");
        }
    }
    printf("\n");
};
