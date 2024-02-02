#if !defined(_SOUND_T)
#define _SOUND_T
#include <inttypes.h>

typedef struct sound{
    unsigned int n_samples;
    int16_t * samples;
} sound_t;

void free_sound_t(sound_t* sound);

#endif // _SOUND_T
