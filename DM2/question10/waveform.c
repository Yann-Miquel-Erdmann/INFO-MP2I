#include "waveform.h"

#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "../src/wav.h"
#include "math.h"

#define PI 3.14159
// renvoie un son de durée duree et de fréquence d'échantillonnage f_ech tous les échantillons ont une valeur aléatoire
sound_t* white(float duree, int f_ech) {
    srand(time(NULL));

    sound_t* sound = malloc(sizeof(sound_t));
    sound->n_samples = (int)(duree * (float)f_ech);

    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    for (int i = 0; i < sound->n_samples; i++) {
        sound->samples[i] = rand() - RAND_MAX / 2;
    }

    return sound;
}

sound_t* sine(float freq, int amplitude, float duree, int f_ech) {
    sound_t* sound = malloc(sizeof(sound_t));
    sound->n_samples = (int)(duree * (float)f_ech);

    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    for (int i = 0; i < sound->n_samples; i++) {
        sound->samples[i] = amplitude * sin(2 * PI * freq * (i / (float)f_ech));
    }

    return sound;
}

int main() {
    sound_t* son = sine(440, 30000, 1, 44100);

    save_soud("question10/myLa440.wav", son);
}