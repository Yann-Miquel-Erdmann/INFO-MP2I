#include "../src/wav.h"

#if !defined(MELODY_H)
#define MELODY_H
float pitch_to_freq(int i);

track_t* read_track(FILE* f);

mix_t * load_mix(char * filename);
#endif // MELODY_H
