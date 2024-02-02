#include <inttypes.h>

#if !defined(_SOUND_H)
#define _SOUND_H

typedef struct sound {
    unsigned int n_samples;
    int16_t *samples;
} sound_t;
void free_sound_t(sound_t *sound);

typedef struct track {
    unsigned int n_sounds;
    sound_t **sounds;
} track_t;
void free_track_t(track_t *track);

typedef struct mix {
    unsigned int n_tracks;
    track_t **tracks;
    float *vols;
} mix_t;
void free_mix_t(mix_t *m);

#endif  // _SOUND_H
