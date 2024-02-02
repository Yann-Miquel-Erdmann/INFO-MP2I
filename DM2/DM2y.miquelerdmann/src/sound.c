#include "sound.h"

#include <stdlib.h>

void free_sound_t(sound_t* sound) {
    
    free(sound->samples);
    free(sound);
}

void free_track_t(track_t* track) {
    for (unsigned int i = 0; i < track->n_sounds; i++) {
        free_sound_t(track->sounds[i]);
    }
    free(track->sounds);
    free(track);
}

void free_mix_t(mix_t* m) {
    for (unsigned int i = 0; i < m->n_tracks; i++) {
        free_track_t(m->tracks[i]);
    }
    free(m->tracks);
    free(m->vols);
    free(m);
}
