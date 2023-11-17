#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>


// Je vais utiliser un tableau 2D de taille 8n/K x (8K +1) pour pouvoir afficher chaque ligne comme une string en mettant caractère nul à la fin de chaque ligne du tableau ce qui me permet de n'avoir qu'une boucle pour l'affichage

// itère sur la chaine de caractères phrase et retire les caractères de la chaîne in qui ne possèdent pas de format image et que l'on ne pourra pas afficher correctement. la nouvelle chaîne remplace celle en entrée. Renvoie la longueur de la nouvelle phrase
int check_phrase(char * phrase,int  len, int K){
    assert(phrase != NULL);
    char * temp = malloc(65*sizeof(char));
    int indice = 0;
    for (int i = 0; i< len; i++){
        //       espace            chiffre                          lettre majuscule            lettre minuscule             
        if (phrase[i] == 32 || (48<=phrase[i] && phrase[i]<=57) || (65<=phrase[i] && phrase[i]<=90) || (97<=phrase[i] && phrase[i]<=122)){
            temp[indice] = phrase[i];
            indice++;
        }
    }

    if (indice%K != 0){  // rajoute des espaces pour avoir une dernière ligne complète
        int ind = indice;
        for (int i = 0; i<(K-ind%K); i++){
            temp[indice] =  32;
            indice++;
        }
    }

    temp[indice] = '\0';
    strcpy(phrase,temp);
    free(temp);
    return indice;
}


// Cette fontion est optionnelle
// modifie la chaîne de len caratères phrase pour qu'un mot ne soit pas coupé par un retour à la ligne si c'est possible 
// (un mot de plus de K caractères sera forcément coupé). Si c'est possible elle ajoute des espaces avant le mot pour le décaler.
// retire un espace si c'est le premier ccaractère d'une ligne
// Stocke la nouvelle chaine à la place de l'ancienne (realloc si besoin)
// Renvoie la longueur de la nouvelle phrase 
int optimise_phrase(char ** phrase, int len, unsigned int K){
    int * charToSpace = malloc(len * sizeof(int));
    int countToSpace = 1;
    
    for (int i = len-1; i >= 0; i--){  
        if((*phrase)[i] != 32){
            charToSpace[i] = countToSpace;
            countToSpace ++;
        }else{
            charToSpace[i] = 1;
            countToSpace = 1;
        }
    }


    int * charCount = malloc(len * sizeof(int));
    int pos = 0;
    int i = 0;
    while(i<len){
        if (charToSpace[i] > K){
            for (int a = 0; a<charToSpace[i]; a++ ){
                charCount[i+a] = 1;
            }
            pos+= charToSpace[i];
            i+= charToSpace[i];
            pos = pos%K;
            printf("%d\n", pos);
        }else{
            if (charToSpace[i] + pos > K){
                charCount[i-1] += K-pos;
                printf("pos %d\n",pos);
                pos = 0;
            }else{
                if (pos ==0 && (*phrase)[i] == 32){ // premier de la phrase est un espace
                    charCount[i] = 0;
                    i++;
                }else{
                    for (int a = 0; a<charToSpace[i]; a++ ){
                        charCount[i+a] = 1;
                    }

                    pos+= charToSpace[i];
                    i+= charToSpace[i];
                    pos = pos% K;
                }

            }
        }
    }

    int sum = 0;
    for (int i = 0; i< len; i++){
        sum += charCount[i];
    }

    printf("sum %d\n", sum);

    char * temp = malloc((sum + (K-sum%K) +1)*sizeof(char));
    int indice = 0;
    for (int i = 0; i<len; i++){
        for (int a= 0; a< charCount[i]; a++){
            temp[indice] = (*phrase)[i];
            indice++;
        }
    } 

    if (sum%K != 0){ // rajoute des espaces pour avoir une dernière ligne complète
        for (int i = 0; i<(K-sum%K); i++){
            temp[indice] =  32;
            indice++;
        }
    }

    temp[indice] = '\0';
    
    
    free(*phrase);
    *phrase = temp;
    
    free(charCount);
    free(charToSpace);
    return indice;
}


// revoie le nom du fichier correspondant au char c (il existe forcément un fichier d'après check_phrase)
char * img_filename(char c)  {
    char * fileName = malloc(16*sizeof(char));
    fileName[0] = '\0';
    char dir[16] = "lettres/\0";
    char ext[5] = ".txt\0";
    strcat(fileName,dir);

    if (c == 32){ // espace
        strcat(fileName,ext);
        return fileName;
    }

    if (48<=c && c<=57) { // chiffre

        fileName[8] = c;
        fileName[9] = '\0';
        strcat(fileName,ext);
        return fileName;

    }

    if (65<=c && c<=90){ // lettre majuscule
        fileName[8] = c;
        fileName[9] = c;
        fileName[10] = '\0';
        strcat(fileName,ext);
        return fileName;
    }

    if (97<=c && c<=122){ // lettre minuscule
        fileName[8] = c;
        fileName[9] = '\0';
        strcat(fileName,ext);
        return fileName;

    }
}

// pour chaque caractère de phrase de longueur len elle appelle img_filename, lit le fichier correspondant, met les pixels correspondants dans la matrice (vide et plein) et met un caractère nul après K "grandes" lettres puis retourne à la ligne et contine
void fill_matrix(char ** matrix, char * phrase,int len, int K, char pixel){
    char* fileName;
    for (int i = 0; i<len; i++){
        fileName = img_filename(phrase[i]);
        printf("%s\n", fileName);
        FILE* f_in = fopen(fileName,"r");
        assert(f_in != NULL);
            
        for (int a = 0; a<8;a++){
            int val;
            fscanf(f_in,"%d\n",&val);
            for (int b = 0; b<8;b++){
                // printf("(%d %d _ %d) ",i%(K*8)+b, (i/K)*8+a, (val>>(8-b-1))%2);
                fflush(stdout);
                if ((val>>(8-b-1))%2 == 1){
                    (matrix[(i/K)*8+a])[(i*8)%(K*8)+b] = pixel;
                }else{
                    (matrix[(i/K)*8+a])[(i%K)*8+b] = 32;
                }

            }
        }

        free(fileName);
        fclose(f_in);

        if (i%K == K-1){
            for (int a = 0; a<8;a++){
                matrix[(i/K)*8+a][(i%K)*8+8] = '\0';
            }
        }
    } 
}
// pour la matrice matrix de m linges, affiche chaque ligne comme une chaîne de caractères 
void print_matrix(char ** matrix, int m){
    for (int i = 0; i< m; i++){
    
        printf("%s\n",matrix[i]);
        if (i%8 == 7){
            printf("\n");
        }
    }
}


// prend comme paramètres caractère à utiliser comme le pixel à utiliser, le nombre K de caractères par ligne, et si elle doit optimiser l'affichage
// demande à l'utilisateur d'entrer une phrase de 64 caractères au maximum
// appelle la fonction check_phrase pour éliminer les potentiels caractères non supportés
// appelle la fonction optimise_phrase pour formatter la phrase
// crée la matrice matrix de taille 8n/K x (8K +1) ou n est la taille de la phrase formatée et K le nombre de lettres par ligne
// appelle la fonction fill_matrix pour remplir la maatrice matrix avec les images des lettres
// affiche la matrice matrix dans la console
int main(int argc, char** argv){
    if (argc < 3){
        fprintf(stderr, "Vous devez donner un caractère qui faira office de pixel et le nommbre de caractères par ligne.\n");
    }

    char pixel = *(argv[1]);
    char K = (int) strtol(argv[2], NULL, 10);
    
    char optimize = 0;
    if (argc == 4){
        
        char t[11] = "optimiser\0";
        if (strcmp(t,argv[3]) == 0){
            printf("Optimisation enclanchée!\n");
            optimize = 1;
        }
    }


    char* phrase = malloc(64*sizeof(char));
    phrase[0] = '\0';
    
    printf("Entrez la phrase à afficher en grand: ");
    scanf("%[^\n]",phrase); // prend tout ce qui n'est pas un retour à la ligne.
    
    int len = 0;
    len = strlen(phrase);

    len = check_phrase(phrase,len, K);


    if (optimize){
        len = optimise_phrase(&phrase,len, K);
    }


    if (len <= 0 ){   //  n'affiche rien si la phrase n'est pas valide (une phrase ne contenant que des espaces n'est pas valide)
        fprintf(stderr,"Il faut donner une phrase à écrire!\n");
        free(phrase);
        exit(1);
    }


    int n = (K*8+1), m = ((len-1)/K + 1)*8;

    char ** matrix = malloc(m*sizeof(char*));
    for (int i = 0; i<((len-1)/K + 1)*8; i++ ){
        matrix[i] = malloc(n* sizeof(char));
        matrix[i][0] = '\0';
    }

    fill_matrix(matrix,phrase,len,K,pixel);
    print_matrix(matrix,m);


    free(phrase);

    for (int i = 0; i<m; i++){
        free(matrix[i]);
    }
    free(matrix);
}