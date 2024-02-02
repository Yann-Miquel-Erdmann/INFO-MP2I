#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define Nmax 1000

struct pile {
    int nb_elm;
    int tab[Nmax];
};

#include "./pile.h"

pile_t* pile_vide() {
    pile_t* p = malloc(sizeof(pile_t));
    p->nb_elm = 0;
    return p;
};

bool est_vide(pile_t* p) {
    return p->nb_elm == 0;
};

void empiler(pile_t* p, int x) {
    assert(p->nb_elm < Nmax);
    p->tab[p->nb_elm] = x;
    p->nb_elm++;
};

int depiler(pile_t* p) {
    assert(p->nb_elm > 0);
    p->nb_elm--;
    return p->tab[p->nb_elm];
};

void free_pile(pile_t* p) {
    free(p);
};

void print_pile(pile_t* p) {
    printf("###\n");

    for (int i = p->nb_elm; i > 0; i--) {
        printf("%d\n", p->tab[i - 1]);
    }

    printf("===\n");
};
