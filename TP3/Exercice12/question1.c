#include <string.h>
#include <stdio.h>


void main(){
    char phrase1[20] = "Ceci est une phrase";
    char phrase2[26] = "Ceci est une autre phrase";

    printf("La chaîne de carratères '%s' comporte %ld caratères\n", phrase1, strlen(phrase1));
    printf("%d\n", strcmp(phrase1, phrase2));
    strcpy(phrase1,phrase2);
    printf("%d\n", strcmp(phrase1, phrase2));
    strcat(phrase1,phrase2);
    printf("%s\n", phrase1));
}
