#include <stdio.h>

#if !defined(_WAV_H)
#define _WAV_H
#define Fech 44100
#define L 16

void write_int(FILE *f, int a, int b);

void write_header(FILE *f, int n);

#endif // _WAV_H
