#include "melody.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

mix_t* load_mix(char* filename) {
    FILE* f_in = fopen(filename, "r");
    assert(f_in != NULL);
    mix_t* mix = malloc(sizeof(mix_t));

    fscanf(f_in, "%d", &mix->n_tracks);
    mix->tracks = malloc(mix->n_tracks * sizeof(track_t*));
    mix->vols = malloc(mix->n_tracks * sizeof(float));

    for (unsigned int i = 0; i < mix->n_tracks; i++) {
        fscanf(f_in, "%f", &(mix->vols[i]));
    }

    for (unsigned int i = 0; i < mix->n_tracks; i++) {
        mix->tracks[i] = read_track(f_in);
    }

    fclose(f_in);

    return mix;
}

void main() {
    char fname[] = "question18/test3.txt";
    mix_t* mix = load_mix(fname);
    sound_t* s_out = reduce_mix(mix);

    save_soud("question18/test3.wav", s_out);
    free_mix_t(mix);
    free_sound_t(s_out);
}