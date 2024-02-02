#include "../src/wav.h"

#if !defined(MELODY_H)
#define MELODY_H
float pitch_to_freq(int i);

track_t* read_track(FILE* f);
#endif // MELODY_H
