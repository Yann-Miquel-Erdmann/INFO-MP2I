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

sound_t* square(float freq, int amplitude, float duree, int f_ech) {
    sound_t* sound = malloc(sizeof(sound_t));
    sound->n_samples = (int)(duree * (float)f_ech);
    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    for (int i = 0; i < sound->n_samples; i++) {
        sound->samples[i] = amplitude * pow(-1, (int)(2 * freq * (i / (float)f_ech)) % 2);
    }

    return sound;
}

sound_t* sawtooth(float freq, int amplitude, float duree, int f_ech) {
    sound_t* sound = malloc(sizeof(sound_t));
    sound->n_samples = (int)(duree * (float)f_ech);
    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    for (float i = 0; i < sound->n_samples; i++) {
        float val = 2*(i / ((float)f_ech) * freq);
        float normalize = val - ((int)(val) / 1) - 1 * ((int)(val) % 2);
        sound->samples[(int)i] = amplitude * normalize;
    }

    return sound;
}

sound_t* triangle(float freq, int amplitude, float duree, int f_ech) {
    sound_t* sound = malloc(sizeof(sound_t));
    sound->n_samples = (int)(duree * (float)f_ech);
    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    int signe = 1;
    for (float i = 0; i < sound->n_samples; i++) {

        float val = 4 * (i / ((float)f_ech) * freq);
        float normalize = val - ((int)(val) / 1) - 1 * ((int)(val) % 2);
        
        float val_prec = 4 * ((i-1) / ((float)f_ech) * freq);
        float normalize_prec = val_prec - ((int)(val_prec) / 1) - 1 * ((int)(val_prec) % 2);

        if (normalize_prec - normalize > 1.5) {
            signe *= -1;
        }

        sound->samples[(int)i] = amplitude * normalize * signe;
    }

    return sound;
}

int main() {
    sound_t* son = square(440, 0x3FFF, 1, 44100);

    save_soud("question11/square.wav", son);
}