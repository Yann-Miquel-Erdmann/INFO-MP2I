#include "liste.h"
/* Implémentation par liste à sentinelle
La liste contient toujours deux maillons, un
à la tête et un à la queue, appelés les
sentinelles. Ces maillons sont invisibles du
point de vue de l'utilisateur. */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct liste {
   struct maillon* tete;
   struct maillon* queue;
   unsigned int taille;
} liste_t;

typedef struct maillon {
   T val;
   struct maillon* suiv;
   struct maillon* prec;
   liste_t* mere;
} maillon_t;

liste_t* liste_vide() {
   liste_t* l = malloc(sizeof(liste_t));
   l->tete = malloc(sizeof(maillon_t));
   l->queue = malloc(sizeof(maillon_t));

   // TETE <-> QUEUE
   l->tete->suiv = l->queue;
   l->tete->prec = NULL;
   l->queue->prec = l->tete;
   l->queue->suiv = NULL;
   
   l->taille = 0;
   l->tete->mere = l;
   l->queue->mere = l;
   return l;
}

void print_liste(liste_t* l) {
   // itérer sur les vrais maillons, i.e. en partant après la sentinelle de tête
   maillon_t* m = l->tete->suiv;
   // jusqu'à atteindre la sentinelle de queue
   while (m->suiv != NULL) {
      printf("%d", m->val);
      // mettre une double flèche s'il reste un vrai maillon à afficher
      if (m->suiv->suiv != NULL) {
         printf(" <-> ");
      }
      m = m->suiv;
   }
   printf("\n");
}

void free_liste(liste_t* l) {
   maillon_t* m = l->tete;
   while (m != NULL) {
      maillon_t* prochain = m->suiv;
      free(m);
      m = prochain;
   }
   free(l);
}

bool est_sentinelle(maillon_t* m) {
   return m->prec == NULL || m->suiv == NULL;
}

void ajoute_avant_v1(liste_t* l, T val) {
   maillon_t* m = malloc(sizeof(maillon_t));
   m->mere = l;
   m->val = val;

   l->tete->suiv->prec = m;
   m->suiv = l->tete->suiv;
   m->prec = l->tete;
   l->tete->suiv = m;
   m->mere->taille++;
}

void ajoute_arriere_v1(liste_t* l, T val) {
   maillon_t* m = malloc(sizeof(maillon_t));
   m->mere = l;
   m->val = val;

   l->queue->prec->suiv = m;
   m->suiv = l->queue;
   m->prec = l->queue->prec;
   l->queue->prec = m;
   m->mere->taille++;
}

T valeur_maillon(maillon_t* m) {
   assert(m != NULL);
   assert(!est_sentinelle(m));
   return m->val;
}

maillon_t* premier_maillon(liste_t* l) {
   if (!est_sentinelle(l->tete->suiv)) {
      return l->tete->suiv;
   }
   return NULL;
};

maillon_t* dernier_maillon(liste_t* l) {
   if (!est_sentinelle(l->queue->prec)) {
      return l->queue->prec;
   }
   return NULL;
};

maillon_t* maillon_suivant(maillon_t* m) {
   assert(!est_sentinelle(m));

   if (!est_sentinelle(m->suiv)) {
      return m->suiv;
   }
   return NULL;
};

maillon_t* maillon_precedent(maillon_t* m) {
   assert(!est_sentinelle(m));

   if (!est_sentinelle(m->prec)) {
      return m->prec;
   }
   return NULL;
};

void inserer(maillon_t* m, T val){

   maillon_t* m1 = malloc(sizeof(maillon_t));
   m1->mere = m->mere;
   m1->val = val;

   m1->suiv = m->suiv;
   m1->prec = m;
   m1->suiv->prec = m1;
   m1->prec->suiv = m1;
   m->mere->taille++;
};

void modifier_maillon(maillon_t* m, T valeur) {
   m->val = valeur;
};

void supprimer_maillon(maillon_t* m){
   assert(!est_sentinelle(m));

   m->suiv->prec = m->prec;
   m->prec->suiv = m->suiv;
   m->mere->taille--;

   free(m);
}

void ajoute_avant(liste_t* l, T val){
   inserer(l->tete, val);
};

void ajoute_arriere(liste_t* l, T val){
   inserer(l->queue->prec, val);
};

unsigned int taille_liste(liste_t* l){
   return l->taille;
};
