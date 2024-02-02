#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct maillon {
    int elem;
    struct maillon* suivant;
} maillon_t;

struct pile {
    maillon_t* sommet;
};
#include "./pile.h"

pile_t* pile_vide() {
    pile_t* p = malloc(sizeof(pile_t));
    p->sommet = NULL;
    return p;
};

bool est_vide(pile_t* p) {
    return p->sommet == NULL;
};

void empiler(pile_t* p, int x) {
    maillon_t* temp = p->sommet;

    p->sommet = malloc(sizeof(maillon_t));
    p->sommet->elem = x;
    p->sommet->suivant = temp;
};

int depiler(pile_t* p) {
    assert(p->sommet != NULL);
    
    maillon_t* temp = p->sommet;

    p->sommet = temp->suivant;
    int val = temp->elem;
    free(temp);

    return val;
};

void free_pile(pile_t* p) {
    while (p->sommet != NULL){
        maillon_t* temp = p->sommet;
        p->sommet = temp->suivant;
        free(temp);
    }
    free(p);
};

void print_pile(pile_t* p) {
    printf("###\n");
    maillon_t* temp = p->sommet;
    while (temp != NULL) {
        printf("%d\n", temp->elem);
        temp = temp->suivant;
    }

    printf("===\n");
};
