#include "wav.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// écrit un entier a dans un fichier f, octet par octet, en little-endian sur b octets
void write_int(FILE* f, int a, int b) {
    assert(f != NULL);
    assert((1 <= b) && (b <= 4));

    for (int i = 0; i < b; i++) {
        fprintf(f, "%c", (a >> (i * 8)) % 0x100);
    }
}

// écrit l’en-tête d’un fichier WAV f qui aura n echantillons
void write_header(FILE* f, int n) {
    //  *((int *) "string")  permet d'éviter que gcc donne un warning et économise des lignes donne l'entier qui représente "string" en petit-boutiste

    write_int(f, *((int*)"RIFF"), 4);

    write_int(f, 36 + (L / 8) * n, 4);

    write_int(f, *((int*)"WAVE"), 4);
    write_int(f, *((int*)"fmt "), 4);

    write_int(f, 16, 4);
    write_int(f, 1, 2);
    write_int(f, 1, 2);

    write_int(f, Fech, 4);

    write_int(f, (Fech * L) / 8, 4);
    write_int(f, L / 8, 2);
    write_int(f, L, 2);

    write_int(f, *((int*)"data"), 4);

    write_int(f, (L / 8) * n, 4);
}

void save_soud(char* filename, sound_t* s) {
    FILE* f_out = fopen(filename, "w");
    assert(f_out != NULL);

    write_header(f_out, s->n_samples);

    for (unsigned int i = 0; i < s->n_samples; i++) {
        write_int(f_out, s->samples[i], L / 8);
    }

    fclose(f_out);
}

sound_t* reduce_track(track_t* t) {
    sound_t* sound_out = malloc(sizeof(sound_t));

    sound_out->n_samples = 0;

    for (unsigned int i = 0; i < t->n_sounds; i++) {
        sound_out->n_samples += t->sounds[i]->n_samples;
    }

    sound_out->samples = malloc(sound_out->n_samples * sizeof(int16_t));
    int index = 0;
    for (unsigned int i = 0; i < t->n_sounds; i++) {
        for (unsigned int a = 0; a < t->sounds[i]->n_samples; a++) {
            sound_out->samples[index] = t->sounds[i]->samples[a];
            index++;
        }
    }

    return sound_out;
}

sound_t* reduce_mix(mix_t* m) {
    int max_n_samples = 0;
    sound_t** sounds = malloc(m->n_tracks * sizeof(sound_t*));
    for (unsigned int i = 0; i < m->n_tracks; i++) {
        sounds[i] = reduce_track(m->tracks[i]);
        if (sounds[i]->n_samples > max_n_samples) {
            max_n_samples = sounds[i]->n_samples;
        }
    }

    sound_t* s_out = malloc((sizeof(sound_t)));
    s_out->n_samples = max_n_samples;
    s_out->samples = malloc(max_n_samples * sizeof(int16_t));

    for (unsigned int i = 0; i < max_n_samples; i++) {
        float div = 0, sum = 0;

        for (unsigned int a = 0; a < m->n_tracks; a++) {
            if (sounds[a]->n_samples > i) {
                div += m->vols[a];
                sum += m->vols[a] * sounds[a]->samples[i];
            }
        }

        s_out->samples[i] = sum / div;
    }

    for (unsigned int i = 0; i < m->n_tracks; i++) {
        free(sounds[i]);
    }
    free(sounds);
    return s_out;
}

void main() {
    mix_t* m = malloc(sizeof(mix_t));
    m->n_tracks = 3;
    m->tracks = malloc(m->n_tracks*sizeof(track_t*));
    m->vols = malloc(3*sizeof(float));

    m->tracks[0] = malloc(sizeof(track_t));
    m->tracks[1] = malloc(sizeof(track_t));
    m->tracks[2] = malloc(sizeof(track_t));
    
    m->tracks[0]->n_sounds = 1;
    m->tracks[0]->sounds = malloc(sizeof(sound_t*));
    m->tracks[0]->sounds[0] = malloc(sizeof(sound_t));
    
    m->tracks[0]->sounds[0]->n_samples = 1;
    m->tracks[0]->sounds[0]->samples = malloc(sizeof(int16_t));
    m->tracks[0]->sounds[0]->samples[0] = 0;
    m->vols[0] = 1;

    m->tracks[1]->n_sounds = 1;
    m->tracks[1]->sounds = malloc(sizeof(sound_t*));
    m->tracks[1]->sounds[0] = malloc(sizeof(sound_t));

    m->tracks[1]->sounds[0]->n_samples = 1;
    m->tracks[1]->sounds[0]->samples = malloc(sizeof(int16_t));
    m->tracks[1]->sounds[0]->samples[0] = 0;
    m->vols[1] = 1;

    m->tracks[2]->n_sounds = 1;
    m->tracks[2]->sounds = malloc(sizeof(sound_t*));
    m->tracks[2]->sounds[0] = malloc(sizeof(sound_t));

    m->tracks[2]->sounds[0]->n_samples = 1;
    m->tracks[2]->sounds[0]->samples = malloc(sizeof(int16_t));
    m->tracks[2]->sounds[0]->samples[0] = 0;
    m->vols[2] = 1;

    free_mix_t(m);
}