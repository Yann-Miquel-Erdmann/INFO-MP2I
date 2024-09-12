#include "tas.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Échange les noeuds i et j de t */
void swap(HEAP* t, int i, int j) {
    assert(0 <= i && 0 <= j && i < t->taille_max && j < t->taille_max);
    T tmp = t->tab[i];
    t->tab[i] = t->tab[j];
    t->tab[j] = tmp;
}

// parent du noeud i
int parent(int i) {
    return (i - 1) / 2;
}

// enfant gauche du noeud i
int gauche(int i) {
    return 2 * i + 1;
}

// enfant droit du noeud i
int droite(int i) {
    return 2 * i + 2;
}

HEAP* tas_vide(int taille) {
    HEAP* h = malloc(sizeof(HEAP));
    h->tab = malloc(taille * sizeof(int));
    assert(h->tab != NULL);
    h->taille_max = taille;
    h->taille_actuelle = 0;
    return h;
}

// tasse t en faisant remonter le noeud d'indice i vers la racine
void tasser(HEAP* h, int i) {
    while (i != 0 && h->tab[i] < h->tab[parent(i)]) {
        swap(h, i, parent(i));
        i = parent(i);
    }
}

void ajouter(HEAP* t, T x) {
    assert(t->taille_actuelle < t->taille_max);
    t->tab[t->taille_actuelle] = x;
    tasser(t, t->taille_actuelle);
    t->taille_actuelle++;
}

// tamise t en faisant descendre le noeud d'indie i vers les feuilles
void tamiser(HEAP* t, int i) {
    while (true) {
        if (gauche(i) < t->taille_actuelle && t->tab[i] >= t->tab[gauche(i)]) {
            if (droite(i) < t->taille_actuelle && t->tab[i] >= t->tab[droite(i)]) {
                if (t->tab[gauche(i)] < t->tab[droite(i)]) {
                    T temp = t->tab[i];
                    t->tab[i] = t->tab[gauche(i)];
                    t->tab[gauche(i)] = temp;
                    i = gauche(i);
                } else {
                    T temp = t->tab[i];
                    t->tab[i] = t->tab[droite(i)];
                    t->tab[droite(i)] = temp;
                    i = droite(i);
                }
            } else {
                T temp = t->tab[i];
                t->tab[i] = t->tab[gauche(i)];
                t->tab[gauche(i)] = temp;
                i = gauche(i);
            }
        } else if (droite(i) < t->taille_actuelle && t->tab[i] >= t->tab[droite(i)]) {
            T temp = t->tab[i];
            t->tab[i] = t->tab[droite(i)];
            t->tab[droite(i)] = temp;
            i = droite(i);

        } else {
            return;
        }
    }
}

T extraire_min(HEAP* t) {
    assert(t->taille_actuelle > 0);
    T temp = t->tab[0];
    t->taille_actuelle--;
    if (t->taille_actuelle > 0) {
        t->tab[0] = t->tab[t->taille_actuelle];
    }

    tamiser(t, 0);

    return temp;
}

HEAP* tasifier(int* t, int n) {
    HEAP* h = malloc(sizeof(HEAP));
    h->tab = t;
    h->taille_actuelle = 0;
    h->taille_max = n;
    for (int i = 0; i < n; i++) {
        h->taille_actuelle++;
        tasser(h, i);
    }
    return h;
}

void tri_par_tas(int* t, int n) {
    HEAP* h = tasifier(t, n);
    for (int i = 0; i < n; i++) {
        h->tab[n - i - 1] = extraire_min(h);
    }
    free(h);
}
