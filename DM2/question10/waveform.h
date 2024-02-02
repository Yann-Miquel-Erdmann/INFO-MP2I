#include "../src/wav.h"
#if !defined(_WAVEFORM_H)
#define _WAVEFORM_H
sound_t* white(float duree, int f_ech);
sound_t* sine(float freq, int amplitude, float duree, int f_ech);
#endif // _WAVEFORM_H
