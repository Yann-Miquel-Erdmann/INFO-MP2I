#include <string.h>
#include <stdio.h>
#include <assert.h>

// revoie la longueur de la chaine de caractères
int ma_strlen(char *chaine){
    int i = 0;
    while (chaine[i] != '\0'){
        i++;
    }
    return i;
}

// revoie 0 si les deux chaines sont égales 
// un entier positif si chaine1 est supérieure à chaine2 par comparaison lexicographique, un entier négatif sinon
// la valeur absolue de l'entier correspond à la différence entre les codes asciis du premier caractère différent
int ma_strcmp(char *chaine1,char* chaine2){
    int i = 0;
    
    while ((chaine1[i] != '\0') || (chaine2[i] != '\0')){
        if (chaine1[i] < chaine2[i]){
            return chaine1[i] - chaine2[i];
        }
        if (chaine1[i] > chaine2[i]){
            return chaine1[i] - chaine2[i];
        }
        i++;
    }
    return 0;
}

// copie la chaine2 dans la chaine1
void ma_strcpy(char *chaine1, char *chaine2){
    for (int i = 0; chaine2[i] != '\0'; i++){
        chaine1[i] = chaine2[i];
    }
}

// concatène la chaine 2 après la chaine1
void ma_strcat(char *chaine1, char *chaine2){
    int indice1 = 0;
    while (chaine1[indice1] != '\0'){
        indice1++;

    }
    int indice2 = 0;
    while (chaine2[indice2] != '\0'){
        chaine1[indice1+indice2] = chaine2[indice2];
        indice2++;
    }
    chaine1[indice1 + indice2 +1] = '\0';
}

void main(){
    char s1[50] = "Un test de strcpy";
    char s4[50] = "Un test de strcpl";

    char s2[50];
    char s3[50];
    strcpy(s2,s1);
    ma_strcpy(s3,s1);
    assert(strcmp(s2,s3) == 0);
    
    assert(ma_strcmp(s2,s3) == 0);
    assert(ma_strcmp(s1,s4) == strcmp(s1,s4));
    assert(ma_strcmp(s4,s1) == strcmp(s4,s1));
   
    assert(ma_strlen(s3) == strlen(s3)); 
    assert(ma_strlen(s4) == strlen(s4));

    ma_strcat(s1,s4);
    strcat(s2,s4);

    assert(strcmp(s1, s2) == 0);


}

