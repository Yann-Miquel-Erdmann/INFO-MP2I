#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "tas.h"

bool est_tas(int* t, int n) {
    for (int i = 1; i < n; i++) {
        if (t[i] < t[(int)((i - 1) / 2)]) {
            return false;
        }
    }
    return true;
}

int* tableau_aleatoire(int n, int a, int b) {
    int* t = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        t[i] = a + (rand()) % (b - a + 1);
    }
    return t;
}

void print_tab(int* t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d  ", t[i]);
    }
    printf("\n");
}

void print_tas(HEAP* h) {
    print_tab(h->tab, h->taille_actuelle);
}

bool est_trie(int* t, int n) {
    for (int i = 1; i < n; i++) {
        if (t[i - 1] < t[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(time(NULL));

    int* t = tableau_aleatoire(10, 2, 7);
    print_tab(t, 10);
    free(t);
    
    HEAP* h = tas_vide(7);
    for (int i = 0; i<7; i++){
        ajouter(h,i+1);

        print_tas(h); 
        assert(est_tas(h->tab, i+1));
    }

    for (int i = 0; i < 7; i++) {
        extraire_min(h);

        print_tas(h);
        assert(est_tas(h->tab, 6-i));
    }

    int t2[6] = {5,2,7,3,4,1};
    print_tab(t2,6);
    tri_par_tas(t2,6);
    print_tab(t2,6);

    return 0;
}
