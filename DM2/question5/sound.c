#include "sound.h"
#include <stdlib.h>


// libère la mémoire allouée pour un élément de type sound_t.
void free_sound_t(sound_t * sound){
    free(sound->samples);
    free(sound);
}


int main(){
    
    
    sound_t * son = malloc(sizeof(sound_t));
    son->n_samples = 10;
    son->samples = malloc(10*sizeof(int16_t));


    free_sound_t(son);
}   