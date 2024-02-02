#include "melody.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/sound.h"
#include "../src/wav.h"
#include "../src/waveform.h"

float pitch_to_freq(int i) {
    return 440 * pow(2, (float)(i / 12.0));
}

track_t* read_track(FILE* file) {
    assert(file != NULL);

    track_t* track = malloc(sizeof(track_t));
    track->n_sounds = 0;

    fscanf(file, "%i", &track->n_sounds);

    track->sounds = malloc(track->n_sounds * sizeof(sound_t*));

    char* type = malloc(20 * sizeof(char));

    fscanf(file, "%s", type);
    printf("%s\n", type);
    assert(strcmp(type, "sawtooth") == 0 || strcmp(type, "sine") == 0 || strcmp(type, "square") == 0 || strcmp(type, "triangle") == 0);



    for (unsigned int i = 0; i < track->n_sounds; i++) {
        int pitch = 0;
        float time = 0, amp_normalse = 0;
        fscanf(file, "%i %f %f", &pitch, &time, &amp_normalse);

        float freq = pitch_to_freq(pitch);
        int amplitude = amp_normalse * 0x8000;

        switch (type[1]) {
            case 'a':  // sawtooth
                track->sounds[i] = sawtooth(freq, amplitude, time, Fech);
                break;
            case 'i':  // sine
                track->sounds[i] = sine(freq, amplitude, time, Fech);
                break;
            case 'r':  // triangle
                track->sounds[i] = triangle(freq, amplitude, time, Fech);
                break;
            case 'q':  // square
                track->sounds[i] = square(freq, amplitude, time, Fech);
                break;

            default:
                fprintf(stderr, "Une erreur est survenue, le type de courbe ( %s ) demandé n'est pas supporté.\n", type);
                exit(1);
                break;
        }
    }

    free(type);
    return track;
}

void main() {
    FILE* f_in = fopen("question15/chromatique.txt", "r");

    track_t* t = read_track(f_in);
    sound_t* out = reduce_track(t);
    save_soud("question15/ma_chromatique.wav", out);
    free_track_t(t);
    free_sound_t(out);
    fclose(f_in);
}
