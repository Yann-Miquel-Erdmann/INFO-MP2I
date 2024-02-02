#include "waveform.h"

#include <stdlib.h>
#include <time.h>

#include "../src/wav.h"

// renvoie un son de durée duree et de fréquence d'échantillonnage f_ech tous les échantillons ont une valeur aléatoire
sound_t* white(float duree, int f_ech){
    srand(time(NULL));

    sound_t* sound = malloc(sizeof(sound_t));
    sound->n_samples = (int)(duree * (float)f_ech);

    sound->samples = malloc(sound->n_samples*sizeof(int16_t));

    for(int i = 0; i< sound->n_samples; i++){
        sound->samples[i] = rand() - RAND_MAX/2 ;
    }

    return sound;
}

int main() {
    sound_t* son = white(1, 44100);

    save_soud("question9/out.wav", son);
}