#pragma once
#include <stdbool.h>
/* Structure de données abstraite: Liste chaînée */

#define T int

typedef struct liste liste_t;
typedef struct maillon maillon_t;

/* Crée une liste vide */
liste_t* liste_vide();

/* Libère toute la mémoire allouée à l */
void free_liste(liste_t* l);

/* Affiche la liste de l'avant à l'arrière */
void print_liste(liste_t* l);

/* Renvoie vrai si le maillon m est un maillon sentinelle */
bool est_sentinelle(maillon_t* m);

/* ajoute un maillon avec la valeur val à l'avant de la liste l */
void ajoute_avant_v1(liste_t* l, T val);

/* ajoute un maillon avec la valeur val à l'arrière de la liste l */
void ajoute_arriere_v1(liste_t* l, T val);

/* renvoie la valeur du maillon m à condition qu'il ne soiot pas nul ou un maillon sentinelle */
T valeur_maillon(maillon_t* m);

/* renvoie un pointeur vers le premier maillon de l*/
maillon_t* premier_maillon(liste_t* l);

/* renvoie un pointeur vers le dernier maillon de l*/
maillon_t* dernier_maillon(liste_t* l);

/* renvoie un pointeur vers le maillon après m */
maillon_t* maillon_suivant(maillon_t* m);

/* renvoie un pointeur vers le maillon avant m */
maillon_t* maillon_precedent(maillon_t* m);

/* insère un maillon avec la valeur val après le maillon m */
void inserer(maillon_t* m, T val);

/* modifie la valeur du maillon m */
void modifier_maillon(maillon_t* m, T valeur);

/* supprime le maillon m de la liste*/
void supprimer_maillon(maillon_t* m);

/* ajoute un maillon avec la valeur val à l'avant de la liste l */
void ajoute_avant(liste_t* l, T val);

/* ajoute un maillon avec la valeur val à l'arrière de la liste l */
void ajoute_arriere(liste_t* l, T val);

/* renvoie la taille de la liste l */
unsigned int taille_liste(liste_t* l);