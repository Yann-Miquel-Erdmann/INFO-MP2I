#include <assert.h>
#include <stdlib.h>

#include "liste.h"

void test() {
   liste_t* list = liste_vide();
   ajoute_avant(list, 3);
   print_liste(list);

   ajoute_avant(list, 2);
   print_liste(list);

   ajoute_avant(list, 1);
   print_liste(list);

   ajoute_arriere(list, 4);
   print_liste(list);

   ajoute_arriere(list, 5);
   print_liste(list);

   assert(taille_liste(list) == 5);

   assert(!est_sentinelle(premier_maillon(list)));
   assert(!est_sentinelle(dernier_maillon(list)));
   assert(!est_sentinelle(maillon_suivant(premier_maillon(list))));
   assert(!est_sentinelle(maillon_precedent(dernier_maillon(list))));

   assert(valeur_maillon(maillon_suivant(premier_maillon(list))) == 2);
   assert(valeur_maillon(maillon_precedent(dernier_maillon(list))) == 4);

   supprimer_maillon(dernier_maillon(list));
   supprimer_maillon(premier_maillon(list));

   assert(taille_liste(list) == 3);

   assert(valeur_maillon(maillon_suivant(premier_maillon(list))) == 3);
   assert(valeur_maillon(maillon_precedent(dernier_maillon(list))) == 3);

   print_liste(list);
   free_liste(list);
}

/* renvoie vrai si val est dans la liste l faux sinon */
bool recherce(liste_t* l, T val) {
   maillon_t* m = premier_maillon(l);
   unsigned int i = 0;
   do {
      if (valeur_maillon(m) == val){
         return true;
      }
      
   }
   for(i < taille_liste(l)) {
      m = maillon_suivant(m);
      i++;
   }

}
}

int main() {
   test();
   return 0;
}
