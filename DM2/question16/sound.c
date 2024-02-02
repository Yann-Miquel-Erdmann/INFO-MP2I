#include "sound.h"

#include <stdlib.h>

void free_sound_t(sound_t* sound) {
    free(sound->samples);
    free(sound);
}

void free_track_t(track_t* track) {
    for (int i = 0; i < track->n_sounds; i++) {
        free_sound_t(track->sounds[i]);
    }
    free(track->sounds);
    free(track);
}

void free_mix_t(mix_t* m) {
    for (int i = 0; i < m->n_tracks; i++) {
        free_track_t(m->tracks[i]);
    }
    free(m->tracks);
    free(m->vols);
    free(m);
}

void main() {
    mix_t* m = malloc(sizeof(mix_t));
    m->n_tracks = 1;
    m->tracks = malloc(sizeof(track_t*));
    m->tracks[0] = malloc(sizeof(track_t));
    m->tracks[0]->n_sounds = 1;
    m->tracks[0]->sounds = malloc(sizeof(sound_t*));
    m->tracks[0]->sounds[0] = malloc(sizeof(sound_t));
    m->tracks[0]->sounds[0]->n_samples = 1;
    m->tracks[0]->sounds[0]->samples = malloc(sizeof(int16_t));
    m->tracks[0]->sounds[0]->samples[0] = 0;
    m->vols = malloc(sizeof(float));
    m->vols[0] = 1;

    free_mix_t(m);
}
