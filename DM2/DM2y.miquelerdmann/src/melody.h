#include "../src/wav.h"

#if !defined(MELODY_H)
#define MELODY_H

float pitch_to_freq(int i); // convertit une numéro de note en fréquence

track_t* read_track(FILE* f);  // lit une piste

mix_t * load_mix(char * filename);  // lit un mélange de pistes du fichier filename
#endif // MELODY_H
