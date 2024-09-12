#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// liste chainée pour stocker les voisins d'un sommet
struct adj{
    unsigned int voisin;
    struct adj* suiv;
};
typedef struct adj adj_t;

struct graphe {
    int n;
    adj_t** lv; // listes des voisins        
};
typedef struct graphe graphe_t;

void print_graphe(graphe_t* g){
    for(int i = 0 ; i<  g->n ; i++){
        printf("%d -> ", i);
        adj_t* v = g->lv[i];
        while (v != NULL){
            printf("%d", v->voisin);
            if (v->suiv != NULL){
                printf(", ");
            }
                v = v->suiv;
        }
        printf("\n");
    }
}

void free_graphe(graphe_t* g){
    for(int i = 0 ; i<  g->n ; i++){
        adj_t* v = g->lv[i];
        while (v != NULL){
            adj_t* temp = v;
            v = v->suiv;
            free(temp);
        }
    }
    free(g->lv);
    free(g);
}

graphe_t* graphe_vide(int n){
    graphe_t* g = malloc(sizeof(graphe_t));
    g->n = n;
    g->lv = malloc(n*sizeof(adj_t*));
    for (int i = 0; i<n; i++) {
        g->lv[i] = NULL;
    }
    return g;
}

int main(int argc, char const *argv[])
{    
    graphe_t* g = malloc(sizeof(graphe_t));
    g->n = 4;
    g->lv = malloc(4*sizeof(adj_t*));
    
    // successeurs de 0: [1]
    g->lv[0] = malloc(sizeof(adj_t));
    g->lv[0]->voisin = 1;
    g->lv[0]->suiv = NULL;

    // successeurs de 1: [2, 3]
    g->lv[1] = malloc(sizeof(adj_t));
    g->lv[1]->voisin = 2;
    g->lv[1]->suiv = malloc(sizeof(adj_t));
    g->lv[1]->suiv->voisin = 3;
    g->lv[1]->suiv->suiv = NULL;

    //successeurs de 2: [0, 3]
    g->lv[2] = malloc(sizeof(adj_t));
    g->lv[2]->voisin = 0;
    g->lv[2]->suiv = malloc(sizeof(adj_t));
    g->lv[2]->suiv->voisin = 3;
    g->lv[2]->suiv->suiv = NULL;

    // successeurs de 3: []
    g->lv[3] = malloc(sizeof(adj_t));
    g->lv[3]->voisin = 0;
    g->lv[3]->suiv = NULL;

    // Libérer la mémoire: A COMPLETER QUESTION

    print_graphe(g);
    free_graphe(g);
    return 0;
}