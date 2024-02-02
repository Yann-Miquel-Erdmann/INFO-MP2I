#include <stdio.h>

#include "../src/sound.h"

#if !defined(_WAV_H)
#define _WAV_H
#define Fech 44100
#define L 16

void write_int(FILE *f, int a, int b); // écrit un entier a sur b bits en petit-boutiste dans f 

void write_header(FILE *f, int n); // écrit l'entête d'un fichier wav de taille n

void save_soud(char *filename, sound_t *s); // écrit le son s dans le fichier wav filename

sound_t *reduce_track(track_t *t);  // superpose les sons de la piste t en un seul sound_t renvoyé

sound_t *reduce_mix(mix_t *m);  // superpose les sons du mix m en un seul sound_t renvoyé

void affiche_info(sound_t *s, char *f_name); // affiche des informations à propos du son s qui sera stocké dans f_name
#endif  // _WAV_H
