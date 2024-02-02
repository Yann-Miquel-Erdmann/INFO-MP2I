#include <stdio.h>
#include <assert.h>

// écrit un entier a dans un fichier f, octet par octet, en little-endian sur b octets
void write_int(FILE* f, int a, int b){
    assert(f != NULL);
    assert((1<=b) && (b<=4));

    for (int i = 0; i< b; i++){
        fprintf(f,"%c", (a>>(i*8)) % 0x100);
    }
}

int main(){
    FILE * f = fopen("question4/out.bin","w");
    assert(f != NULL);

    write_int(f, *((int*)"RIFF"), 4);

    fclose(f);

}