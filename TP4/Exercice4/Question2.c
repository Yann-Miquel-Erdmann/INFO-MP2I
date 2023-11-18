#include <assert.h>
#include <string.h>
#include <stdio.h>

// lit une ligne du fichier f si elle fait moins de n_max caractères et la stocke dans résulat
void lire_ligne(FILE* f,char* resultat, int n_max){
    ;
};

void main(){
    char ligne1[31] = "une ligne de 30 caracteres !!!";
    char ligne2[31] = "voici une autre ligne ^^:";
    char ligne3[31] = "et enfin une dernière";
    char ligne[31];
    
    FILE *f = fopen("texte.txt", "r");
    assert(f != NULL);

    lire_ligne(f,ligne, 30);
    assert(strcmp(ligne,ligne1) == 0);
    lire_ligne(f,ligne, 30);
    assert(strcmp(ligne,ligne2) == 0);
    lire_ligne(f,ligne, 30);
    assert(strcmp(ligne,ligne3) == 0);
}