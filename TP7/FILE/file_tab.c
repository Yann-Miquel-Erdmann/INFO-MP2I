#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "./file.h"

#define Nmax 1000
struct file {
    int queue;
    int nb_elem;
    int tab[Nmax];
};

file_t* file_vide() {
    file_t* f = malloc(sizeof(file_t));
    f->queue = 0;
    f->nb_elem = 0;

    return f;
};

bool est_file_vide(file_t* f) {
    return f->nb_elem == 0;
};

void enfiler(file_t* f, int x) {
    assert(f->nb_elem < Nmax);

    f->tab[f->queue] = x;
    f->queue++;
    f->queue %= Nmax;
    f->nb_elem++;
};

int defiler(file_t* f) {
    assert(f->nb_elem != 0);
    int ind = (f->queue - f->nb_elem + Nmax) % Nmax;

    int val = f->tab[ind];
    f->nb_elem--;

    return val;
};

void free_file(file_t* f) {
    free(f);
};

void affiche_file(file_t* f) {
    for (int i = 0; i < f->nb_elem; i++) {
        if (i != 0) {
            printf(" <- ");
        }
        int ind = (f->queue - f->nb_elem + i + Nmax) % Nmax;
        printf("%d", f->tab[ind]);
    }
    printf("\n");
}

