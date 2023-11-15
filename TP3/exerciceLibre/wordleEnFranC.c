#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "listeDeMots.h"
#define NOMBRE_DE_MOTS 336530
unsigned char motsDe5Lettres[NOMBRE_DE_MOTS][10];  // NOMBRE_DE_MOTS correspond à la taille de la liste de mots français (peu importe le nommbre de lettres)
unsigned char motATrouver[11]; // mot à trouver
unsigned int NombreDeMots5L; // nombre de mots de 5 lettres

// prend une liste, un indice et une variable bouléenne et remplace l'indice par celui de la lettre suivante dans la liste, 
// la variable bouléenne est mise vraie si la lettre prend deux emplacements  
void next(unsigned char *liste, int * indice){  
    if( (liste[*indice]>>7) == 1){
        (*indice) += 2;
    }else{
        (*indice) +=1;
    }

}

// renvoie true si un mot fait 5 lettres, false sinon
bool estDeLongueur5(unsigned char liste[11]){
    int indice = 0;
    for(int a = 0; a<5; a++){
        if (liste[indice] == 0){ // le mot fait moins de 5 lettres
            return false;
        }
        next(liste, &indice);
    }
    if (liste[indice] != 0){ // le mot fait plus de 5 lettres
        return false;
    }
    return true;
}


// parcourt la liste de touts les mots de la langue française et copie ceux de 5 lettres dans une liste séparée
void filtreMots5L(){
    for(int i = 0; i< NOMBRE_DE_MOTS; i++){
        if (mots[i][4] == 0){ // le mot a moins de 5 lettres car le 4eme octet est nul
            continue;
        }
        if (mots[i][10] != 0){ // le mot a plus de 5 lettres même si chacune des lettres sont sur 2 octets
            continue;
        }

        if (estDeLongueur5(mots[i])){ 
            // le mot est de longueur 5, on le copie dans la liste motsDe5Lettres
            for (int a = 0; a<10;a++){
                motsDe5Lettres[NombreDeMots5L][a] = mots[i][a]; 
            }
            NombreDeMots5L++;
            
        }
        printf("\e[1A\e[2K");
        printf("%d%%\n", (int)(100*(i+1)/NOMBRE_DE_MOTS)); // affiche l'avancement de la recherche en % 
    }
}

// compare la lettre de mot1 à l'indice indice1 et la lettre de mot2 à l'indice indice2 
// prend en compte les lettres sur 1 ou 2 octets 
// revoie true si les lettres sont les mêmes, false sinon 
bool compareLettre(unsigned char *mot1, unsigned char *mot2, int indice1, int indice2){
    
    if ((mot2[indice2]>>7) != (mot1[indice1] >> 7)){ // comparaisson du bit de poids fort (0 si la lettre est sur 1 octet, 1 sinon)
        return false; // une lettre est codée sur deux octets, l'autre sur un seul: les lettres ne sont pas les mêmes
    }
    
    if (mot2[indice2] != mot1[indice1]){ // compare le premier octet
        return false; // les 1ers octets sont différents: les lettres sont différentes
    }

    if(mot2[indice2]>>7 == 1){ // si les lettres sont sur 2 octets
        if (mot2[indice2 + 1] != mot1[indice1 + 1]){ // compare le 2 eme octet
            return false; // les 2emes octets sont différents: les lettres sont différentes
        }
    }

    return true; // les lettres sont les mêmes
    
}

// affiche une la lettre à l'indice indice du mot mot
void afficheLettre(unsigned char *mot,int indice){
    printf("%c", mot[indice]);

    if(mot[indice]>>7 == 1){
        printf("%c", mot[indice+1]);
    }
}

// prend deux mots de 5 lettres et renvoit true si les mots sont les mêmes en comparant chaque lettre
bool compareMots5L(unsigned char *mot1,unsigned char *mot2){
    int indice1= 0; // indice d'une lettre de mot1
    int indice2 = 0;  // indice d'une lettre de mot2 
    for(int i = 0 ;i<5;i++){  // touve les lettres bien placées

        if (!compareLettre(mot1,mot2,indice1,indice2)){ 
            return false; // la i eme lettre n'est pas la même
        }

        next(mot1,&indice1);
        next(mot2,&indice2);
            
    }
    // les 5 lettres sont les mêmes donc les mots sont les mêmes
    return true;
}

// revoie true si mot appartient à la liste de mots de 5 lettres motsDe5Lettres
bool appratientAuDico(unsigned char *mot){
    for(int i = 0; i<NombreDeMots5L;i++){
        if (compareMots5L(mot,motsDe5Lettres[i])){
            return true; // mot est égal à un mot de la liste, il appartient donc à la liste
        }
    }   
    return false; // mot est égal à aucun mot de la liste, il n'appartient donc pas à la liste
}

// prend en entrée le mot écrit par l'utilisateur et le compare au mot à trouver, 
// affiche le mot de l'utilisateur avec les lettres en couleur (voir tuto), 
// revoie true si le mot donné par l'utilisateur est celui qu'il devait trouver, false sinon    
bool essai(unsigned char *guess){ 
    bool juste[5] = {false,false,false,false,false};
    bool utilisee[5] = {false,false,false,false,false}; // lettres utilisées dans le guess -> but: ne pas utilliser plusieurs fois la même lettre
    int indiceGuess= 0; // indice d'une lettre de guess
    int indiceMot = 0;  // iindice d'une lettre de mot 

    if (!estDeLongueur5(guess)){
        return false; // le mots donné par l'utilisateur ne fait pas 5 lettres
    }

    if (!appratientAuDico(guess)){
        return false; // le mot donné par l'utilisateur n'appartient pas à la liste de mots valides
    }
    

    for(int i = 0 ;i<5;i++){  // touve les lettres bien placées

        if (compareLettre(guess,motATrouver,indiceGuess,indiceMot)){
            juste[i] = true;
            utilisee[i] = true;
        }
        next(guess,&indiceGuess);
        next(motATrouver,&indiceMot);
        
    }


    indiceGuess = 0;
    for(int i = 0 ;i<5;i++){ // affiche les lettres avec les couleurs correspondantes
        if (juste[i] == true){ // la lettre est bien placée
            printf("\e[1;32m"); // vert
            afficheLettre(guess,indiceGuess);
            printf("\e[0m");
        }else{ // cherchons si la lettre essayée est dans le mot à touver et n'est pas déjà "utilisée"

            bool ecrit = false;
            indiceMot = 0;
            for(int j = 0; (!ecrit) && j<5;j++){
                if (utilisee[j]){ // la lettre du mot à trouver est déjà utilisée
                    next(motATrouver,&indiceMot);
                    continue;
                }


                if (compareLettre(guess,motATrouver,indiceGuess,indiceMot)){ // la lettre essayée appartient au mot à trouver (mais n'est pas bien placée)
                    utilisee[j] = true;
                    printf("\e[1;33m"); // jaune
                    afficheLettre(guess,indiceGuess);
                    printf("\e[0m");
                    ecrit = true;
                }

                next(motATrouver,&indiceMot);
            }


            if(ecrit == false){ // la lettre essayée n'est pas dans le mot ou est deja utilisée
                printf("\e[2;30m"); //gris
                afficheLettre(guess,indiceGuess);
                printf("\e[0m");
            }
        } 

        next(guess,&indiceGuess);

    }
    printf("\n");
    

    bool gagne = true; // revoie true si toutes le lettres sont justes 
    for (int i = 0; i<5; i++){
        gagne = gagne && juste[i];
    }
    return gagne;
}


void motAleatoire(){
    unsigned int indice = rand()%NombreDeMots5L;
    for(int i = 0; i<10;i++){
        motATrouver[i] = motsDe5Lettres[indice][i];
    }
}   

void tutoriel(){
    printf("Bienvenue sur Wordle en FranC\n");
    printf("Un mot de 5 lettres a été choisi au hasard dans le dictionnaire français, à vous de le retouver.");
    printf("Pour ce faire vous devez essayer des mots de 5 lettres et le programme vous indiquera pour chacune des lettres:\n");
    printf("    -Si elle est dans le mot à trouver et bien placée en la colorant en vert comme ceci: \e[1;32mx\e[0m\n");
    printf("    -Si elle est dans le mot à trouver mais mal placée en la colorant en jaune comme ceci: \e[1;33mx\e[0m\n");
    printf("    -Si elle n'est dans le mot à trouver en la colorant en gris comme ceci: \e[2;30mx\e[0m\n");
    printf("Le mot à trouver ne comporte que des lettres minuscules et peut contenir des accentuations\n");
    printf("Si votre mot n'appartient pas au dictionnaire ou ne commporte pas 5 lettres il sera éffacé et vous pourrez continuer la partie...\n");
    printf("De plus si le mot que vous avez écrit mot contient plusieurs fois la même lettre et que cette lettre apparait moins de fois dans le mot à trouver, cette lettre sera colorée en jaune ne nombre de fois où elle apparait dans le mot à trouver.\n");
    printf("Par exemple si le mot que vous devez trouver est chats et que vous ecrivez lamas, seul le premier des deux 'a' sera coloré en jaune et le 's' sera coloré en vert car il est bien placé comme montré ci dessous\n");
    printf("\e[1;31mchats\e[0m\n");
    printf("\e[2;30ml\e[0m\e[1;33ma\e[0m\e[2;30mma\e[0m\e[1;32ms\e[0m\n");
    printf("Enfin vous pouvez quitter le programme à tout moment en tappant '!' puis ENTRER\n\n");

}   

int main(){
    printf("Bienvenue sur Wordle en FranC\n");
    printf("Chargement des mots\n\n");

    filtreMots5L();
    printf("\e[2J");  // éfface la console 
 
    tutoriel();

    unsigned char buffer[20]; //10 suffit mais cela diminue le risque d'overflow
    srand(time(NULL));
    motAleatoire(); 
    printf("Un mot a été choisi, à vous de le retrouver!\n");
    do{
        scanf("%s", buffer);
        printf("\e[1A\e[2K");
        if (essai(buffer)){
            printf("Bravo! Vous avez trouvé le bon mot.\nUn nouveau mot de la liste a été choisi, à vous de le trouver!\nSinon quitez le programme en tapant '!' puis ENTRER\n");
            motAleatoire();
        }
    }while(buffer[0] != 33); // si la première lettre est un ! on on quitte la boucle de jeu et le programme se termine




}

