#include "graphe.h"
// #include "dijkstra.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

int main(int argc, char const* argv[]) {
    // graphe exemple du sujet
    int n = 4;
    char** sommets = malloc(n * sizeof(char*));
    sommets[0] = strdup("CHAT");  // strdup alloue une nouvelle zone et y copie la chaîne
    sommets[1] = strdup("CHIEN");
    sommets[2] = strdup("OISEAU");
    sommets[3] = strdup("VACHE");

    graphe_t* g = graphe_vide(sommets, n);

    ajouter_arete(g, "CHAT", "CHIEN", 1);

    ajouter_arete(g, "CHIEN", "OISEAU", 7);
    ajouter_arete(g, "CHIEN", "VACHE", 3);

    ajouter_arete(g, "OISEAU", "CHAT", 1);

    ajouter_arete(g, "VACHE", "OISEAU", 2);

    assert(est_arete(g, "CHIEN", "OISEAU"));
    assert(!est_arete(g, "OISEAU", "CHIEN"));

    afficher(g);
	free_graphe(g);
}