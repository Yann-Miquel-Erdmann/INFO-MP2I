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

    for (unsigned int i = 0; i < sound->n_samples; i++) {
        sound->samples[i] = rand() - RAND_MAX / 2;
    }

    return sound;
}

sound_t* sine(float freq, int amplitude, float duree, int f_ech) {
    sound_t* sound = malloc(sizeof(sound_t));
    sound->n_samples = (int)(duree * (float)f_ech);

    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    for (unsigned int i = 0; i < sound->n_samples; i++) {
        sound->samples[i] = amplitude * sin(2 * PI * freq * (i / (float)f_ech));
    }

    return sound;
}

sound_t* square(float freq, int amplitude, float duree, int f_ech) {
    sound_t* sound = malloc(sizeof(sound_t));
    sound->n_samples = (int)(duree * (float)f_ech);
    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    for (unsigned int i = 0; i < sound->n_samples; i++) {
        sound->samples[i] = amplitude * pow(-1, (int)(2 * freq * (i / (float)f_ech)) % 2);
    }

    return sound;
}

sound_t* sawtooth(float freq, int amplitude, float duree, int f_ech) {
    sound_t* sound = malloc(sizeof(sound_t));
    sound->n_samples = (int)(duree * (float)f_ech);
    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    for (float i = 0; i < sound->n_samples; i++) {
        float val = 2 * (i / ((float)f_ech) * freq);
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

        float val_prec = 4 * ((i - 1) / ((float)f_ech) * freq);
        float normalize_prec = val_prec - ((int)(val_prec) / 1) - 1 * ((int)(val_prec) % 2);

        if (normalize_prec - normalize > 1.5) {
            signe *= -1;
        }

        sound->samples[(int)i] = amplitude * normalize * signe;
    }

    return sound;
}

int compute_ADSR(ADSR_t* adsr, float** amplitudes, float duree, int freq_ech) {
    assert(duree > adsr->A + adsr->D);
    int len = (int)((duree + adsr->R) * freq_ech);
    *amplitudes = malloc(len * sizeof(float));

    float mult;

    mult = (adsr->peak / (adsr->A * freq_ech - 1));  // attack
    for (int i = 0; i < (int)(adsr->A * freq_ech); i++) {
        (*amplitudes)[i] = (float)i * mult;
    }

    mult = (float)((adsr->S - adsr->peak) / (adsr->D * freq_ech - 1));  // decay
    for (int i = (int)(adsr->A * freq_ech); i < (int)((adsr->A + adsr->D) * freq_ech); i++) {
        (*amplitudes)[i] = (float)(i - (int)(adsr->A * freq_ech)) * mult + adsr->peak;
    }

    // sustain
    for (int i = (int)((adsr->A + adsr->D) * freq_ech); i < (int)(duree * freq_ech); i++) {
        (*amplitudes)[i] = adsr->S;
    }

    mult = (float)((-adsr->S) / (adsr->R * freq_ech - 1));  // decay
    for (int i = (int)(duree * freq_ech); i < len; i++) {
        (*amplitudes)[i] = (float)(i - (int)(duree * freq_ech)) * mult + adsr->S;
    }

    return len;
};

sound_t* sine_ADSR(float freq, int amplitude, float duree, int f_ech, ADSR_t* adsr) {
    sound_t* sound = malloc(sizeof(sound_t));

    float* amplitudes_adsr;
    int n_samples = compute_ADSR(adsr, &amplitudes_adsr, duree, f_ech);
    sound->n_samples = n_samples;

    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    float mult = (2 * PI * freq) / (float)f_ech;

    for (unsigned int i = 0; i < sound->n_samples; i++) {
        sound->samples[i] = amplitudes_adsr[i] * amplitude * sin((float)i * mult);
    }

    free(amplitudes_adsr);
    return sound;
}

sound_t* square_ADSR(float freq, int amplitude, float duree, int f_ech, ADSR_t* adsr) {
    sound_t* sound = malloc(sizeof(sound_t));

    float* amplitudes_adsr;
    int n_samples = compute_ADSR(adsr, &amplitudes_adsr, duree, f_ech);
    sound->n_samples = n_samples;

    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    for (unsigned int i = 0; i < sound->n_samples; i++) {
        sound->samples[i] = amplitudes_adsr[i] * amplitude * pow(-1, (int)(2 * freq * (i / (float)f_ech)) % 2);
    }
    free(amplitudes_adsr);

    return sound;
}

sound_t* sawtooth_ADSR(float freq, int amplitude, float duree, int f_ech, ADSR_t* adsr) {
    sound_t* sound = malloc(sizeof(sound_t));
    float* amplitudes_adsr;
    int n_samples = compute_ADSR(adsr, &amplitudes_adsr, duree, f_ech);
    sound->n_samples = n_samples;
    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    for (float i = 0; i < sound->n_samples; i++) {
        float val = 2 * (i / ((float)f_ech) * freq);
        float normalize = val - ((int)(val) / 1) - 1 * ((int)(val) % 2);
        sound->samples[(int)i] = amplitudes_adsr[(int)i] * amplitude * normalize;
    }
    free(amplitudes_adsr);

    return sound;
}

sound_t* triangle_ADSR(float freq, int amplitude, float duree, int f_ech, ADSR_t* adsr) {
    sound_t* sound = malloc(sizeof(sound_t));

    float* amplitudes_adsr;
    int n_samples = compute_ADSR(adsr, &amplitudes_adsr, duree, f_ech);
    sound->n_samples = n_samples;

    sound->samples = malloc(sound->n_samples * sizeof(int16_t));

    int signe = 1;
    for (float i = 0; i < sound->n_samples; i++) {
        float val = 4 * (i / ((float)f_ech) * freq);
        float normalize = val - ((int)(val) / 1) - 1 * ((int)(val) % 2);

        float val_prec = 4 * ((i - 1) / ((float)f_ech) * freq);
        float normalize_prec = val_prec - ((int)(val_prec) / 1) - 1 * ((int)(val_prec) % 2);

        if (normalize_prec - normalize > 1.5) {
            signe *= -1;
        }

        sound->samples[(int)i] = amplitudes_adsr[(int)i] * amplitude * normalize * signe;
    }
    free(amplitudes_adsr);

    return sound;
}