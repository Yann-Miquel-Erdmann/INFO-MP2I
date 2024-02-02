#include <stdio.h>

#include "../src/sound.h"

#if !defined(_WAV_H)
#define _WAV_H
#define Fech 44100
#define L 16
void write_int(FILE* f, int a, int b);

void write_header(FILE* f, int n);

void save_soud(char* filename, sound_t* s);

#endif  // _WAV_H
