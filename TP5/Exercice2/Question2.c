#include <stdlib.h>

struct maillon {
    struct maillon * suivant;
    int valeur;
};
typedef struct maillon maillon_t;

struct liste {
    unsigned int taille;
    maillon_t * tete;
};
typedef struct liste liste_t;

liste_t * range(int n){
    liste_t * list = malloc(sizeof(liste_t)); 
    list->taille = n;
    list->tete = malloc(sizeof(maillon_t*));

    maillon_t * temp = list->tete;
    for (int i = 0; i< n; i++){
        temp->valeur = i;
        temp->suivant = malloc(sizeof(maillon_t*));
        
        temp = temp->suivant;
    }

}

void main(){
    liste
    for (int i  = 0)
}