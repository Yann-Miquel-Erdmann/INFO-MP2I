#include <stdio.h>
#include <assert.h>
#include "wav.h"

// écrit un entier a dans un fichier f, octet par octet, en little-endian sur b octets
void write_int(FILE* f, int a, int b){
    assert(f != NULL);
    assert((1<=b) && (b<=4));

    for (int i = 0; i< b; i++){
        fprintf(f,"%c", (a>>(i*8)) % 0x100);
    }
}

// écrit l’en-tête d’un fichier WAV f qui aura n echantillons
void write_header(FILE* f, int n) {
    //  *((int *) "string")  permet d'éviter que gcc donne un warning et économise des lignes donne l'entier qui représente "string" en petit-boutiste

    write_int(f, *((int*)"RIFF"), 4); 

    write_int(f, 36 + (L / 8) * n, 4);

    write_int(f, *((int*)"WAVE"), 4);  
    write_int(f, *((int*)"fmt "), 4);  

    write_int(f, 16, 4);
    write_int(f, 1, 2);
    write_int(f, 1, 2);

    write_int(f, Fech, 4);

    write_int(f, (Fech * L) / 8, 4);
    write_int(f, L / 8, 2);
    write_int(f, L, 2);

    write_int(f, *((int*)"data"), 4);  

    write_int(f, (L / 8) * n, 4);
}