#include "graphe.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stoi.h"

void afficher(graphe_t* g) {
    for (int i = 0; i < g->n; ++i) {
        printf("%s -> ", g->sommets[i]);
        adj_t* maillon = g->voisins[i];
        while (maillon != NULL) {
            char* nom_voisin = g->sommets[maillon->dest];
            printf("(%s, %f), ", nom_voisin, maillon->poids);
            maillon = maillon->suiv;
        }
        printf("\n");
    }
}

bool est_arete(graphe_t* g, char* u, char* v) {
    assert(stoi_mem(g->indice, u));
    assert(stoi_mem(g->indice, v));

    // retrouver les indices des sommets
    int i = stoi_get(g->indice, u);
    int j = stoi_get(g->indice, v);

    // chercher j dans la liste des voisins de i
    adj_t* maillon = g->voisins[i];
    while (maillon != NULL && maillon->dest != j) {
        maillon = maillon->suiv;
    }
    // en sortie: soit maillon = NULL soit maillon représente une arête (i, j)
    return (maillon != NULL);
}

graphe_t* graphe_vide(char** sommets, int n) {
    graphe_t* g = malloc(sizeof(graphe_t));
    g->n = n;
    g->sommets = sommets;
    g->indice = stoi_vide();
    g->voisins = malloc(sizeof(adj_t) * n);
    for (int i = 0; i < n; i++) {
        stoi_set(g->indice, sommets[i], i);
        g->voisins[i] = NULL;
    }

    return g;
}

void ajouter_arete(graphe_t* g, char* u, char* v, float w) {
    int i_u = stoi_get(g->indice, u);
    printf("%d\n", i_u);

    adj_t* voisin = malloc(sizeof(adj_t));
    voisin->dest = stoi_get(g->indice, v);
    voisin->poids = w;

    voisin->suiv = g->voisins[i_u];
    g->voisins[i_u] = voisin;
}

free_graphe(graphe_t* g) {
    for (int i = 0; i < g->n; i++) {
        while (g->voisins[i] != NULL) {
            adj_t* a = g->voisins[i]->suiv;
            free(g->voisins[i]);
            g->voisins[i] = a;
        }
    }
	free(g->voisins);
	stoi_free(g->indice);
}