#include <stdio.h>

// ecrit en toutes lettres un chiffre entre 0 et 9 entré par l'utilisateur 
void main(){
    int chiffre;
    while(chiffre != -1){
        printf("entrez un nombre entre 0 et 9 sinon tapez -1 pour quiter: \n");
        scanf("%i", &chiffre);


        if(chiffre == 0){
            printf("zéro\n");
        }
        
        if(chiffre == 1){
            printf("un\n");
        }
        if(chiffre == 2){
            printf("deux\n");
        }
        if(chiffre == 3){
            printf("trois\n");
        }
        if(chiffre == 4){
            printf("quatre\n");
        }
        if(chiffre == 5){
            printf("cinq\n");
        }
        if(chiffre == 6){
            printf("six\n");
        }
        if(chiffre == 7){
            printf("sept\n");
        }
        if(chiffre == 8){
            printf("huit\n");
        }
        if(chiffre == 9){
            printf("neuf\n");
        }

       
    }  

}       
