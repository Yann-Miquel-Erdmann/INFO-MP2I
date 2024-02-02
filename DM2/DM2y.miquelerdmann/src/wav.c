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
    unsigned int max_n_samples = 0;
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
        float sum = 0;

        for (unsigned int a = 0; a < m->n_tracks; a++) {
            if (sounds[a]->n_samples > i) {
                sum += m->vols[a] * sounds[a]->samples[i];
            }
        }

        s_out->samples[i] = (float) sum / m->n_tracks;
    }

    for (unsigned int i = 0; i < m->n_tracks; i++) {
        free_sound_t(sounds[i]);
    }
    free(sounds);

    return s_out;
}



void affiche_info(sound_t* s, char* f_name){
    printf("Fichier %s généré!\n", f_name);

    int taille = 44;  // header
    taille += s->n_samples * (L / 8);

    char prefixe[] = "KMGT";
    int i = 0;
    while (taille / 1024 > 0) {
        taille /= 1024;
        i++;
    }
    if (i > 0) {
        printf("Taille du fichier: %d%co\n", taille, prefixe[i - 1]);
    } else {
        printf("Taille du fichier: %do\n", taille);
    }

    printf("L'audio de %s a une durée de ", f_name);
    int duree = s->n_samples / Fech;
    if (duree/3600 > 0){
        printf("%dh", duree/3600);
    }

    duree = duree%3600;
    if (duree/60 > 0){
        printf("%dm", duree/60);
    }

    duree = duree%60;
    if (duree >= 0){
        printf("%ds.\n", duree);
    }
    
}