#include <inttypes.h>

#if !defined(_SOUND_H)
#define _SOUND_H

typedef struct sound { // repésente un son comme une liste d'échantillons
    unsigned int n_samples;
    int16_t *samples;
} sound_t;
void free_sound_t(sound_t *sound);  // libère l'espace alloué à une structure sound

typedef struct track {  // repésente un ensemble de sons sound_t
    unsigned int n_sounds;
    sound_t **sounds;
} track_t;
void free_track_t(track_t *track);  // libère l'espace alloué à une structure track

typedef struct mix {  // repésente un ensemble de pistes track_t avec un volume associé
    unsigned int n_tracks;
    track_t **tracks;
    float *vols;
} mix_t;
void free_mix_t(mix_t *m);  // libère l'espace alloué à une structure mix

#endif  // _SOUND_H
