#include "../src/midi.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../src/melody.h"
#include "../src/wav.h"
#include "../src/waveform.h"

void free_mtrk_event_t(mtrk_event_t* e) {
    free(e->data);
    free(e);
}

void free_midi_track_t(midi_track_t* t) { 
    for (unsigned int i = 0; i < t->n_events; i++) {
        free_mtrk_event_t(t->mtrk_events[i]);
    }
    free(t->mtrk_events);

    for (unsigned int i = 0; i < 128; i++) {
        free_midi_channel_t(t->channels[i]);
    }
    free(t->channels);

    free(t->count_channel_notes);
    free(t);
}

void free_midi_t(midi_t* m) {
    for (unsigned int i = 0; i < m->ntrks; i++) {
        free_midi_track_t(m->midi_tracks[i]);
    }
    free(m->midi_tracks);
    free_sound_t(m->son);
    free(m);
}

int read_n_bytes(FILE* f_in, int n) {
    int res = 0;
    for (int i = 0; i < n; i++) {
        unsigned char temp;
        char n = fscanf(f_in, "%c", &temp);
        assert(n == 1);
        res <<= 8;
        res += temp;
    }

    return res;
}

int read_VLV(FILE* f_in, unsigned int* count) {
    int res = 0;
    unsigned char temp = 0;

    do {
        res <<= 7;
        char n = fscanf(f_in, "%c", &temp);
        assert(n == 1);
        res += temp % 0x80;
        (*count)++;
    } while (temp & 0x80);

    return res;
}

mtrk_event_t* read_mtrk_event(FILE* f_in, unsigned int* count, unsigned int* count_channel_notes) {
    mtrk_event_t* e = malloc(sizeof(mtrk_event_t));

    e->delta_time = read_VLV(f_in, count);

    e->prefixe = read_n_bytes(f_in, 1);
    (*count)++;

    switch (e->prefixe & 0b11110000) {
        case 0xf0:
            if (e->prefixe == 0xf0 || e->prefixe == 0xf7) {
                e->length = read_VLV(f_in, count);
                e->data = malloc(e->length * sizeof(char));
                for (unsigned int i = 0; i < e->length; i++) {
                    e->data[i] = (char)read_n_bytes(f_in, 1);
                }
                (*count) += e->length;
                break;
            }

            if (e->prefixe == 0xff) {
                e->type = read_n_bytes(f_in, 1);
                e->length = read_VLV(f_in, count);

                e->data = malloc(e->length * sizeof(char));
                for (unsigned int i = 0; i < e->length; i++) {
                    e->data[i] = (char)read_n_bytes(f_in, 1);
                }

                (*count) += e->length + 1;
                break;
            }

            printf("erreur cas 0xF_ %04x %04x\n", e->prefixe, *count);
            break;

        case 0x80:  // Note Off
            e->length = 2;
            e->channel = e->prefixe & 0b00001111;
            e->prefixe = 0x80;
            e->data = malloc(e->length * sizeof(char));
            for (unsigned int i = 0; i < e->length; i++) {
                e->data[i] = (char)read_n_bytes(f_in, 1);
            }

            (*count) += e->length;
            break;

        case 0x90:  // Note On
            e->length = 2;
            e->channel = e->prefixe & 0b00001111;
            e->prefixe = 0x90;

            count_channel_notes[e->channel]++;
            e->data = malloc(e->length * sizeof(char));
            for (unsigned int i = 0; i < e->length; i++) {
                e->data[i] = (char)read_n_bytes(f_in, 1);
            }

            (*count) += e->length;

            if (e->data[1] == 0) {  // si velocity de la note est nulle alors c'est aquivalent à Note off
                e->prefixe = 128;
            }

            break;

        case 0xB0:
            e->length = 2;

            e->data = malloc(e->length * sizeof(char));
            for (unsigned int i = 0; i < e->length; i++) {
                e->data[i] = (char)read_n_bytes(f_in, 1);
            }

            (*count) += e->length;
            break;

        case 0xC0:  // program change
            e->length = 1;
            e->data = malloc(e->length * sizeof(char));
            for (unsigned int i = 0; i < e->length; i++) {
                e->data[i] = (char)read_n_bytes(f_in, 1);
            }

            (*count) += e->length;
            break;

        case 0xD0:  // Channel pressure/After touch
            e->length = 1;

            e->data = malloc(e->length * sizeof(char));
            for (unsigned int i = 0; i < e->length; i++) {
                e->data[i] = (char)read_n_bytes(f_in, 1);
            }

            (*count) += e->length;
            break;

        case 0xE0:  // pitch bend
            e->length = 2;

            e->data = malloc(e->length * sizeof(char));
            for (unsigned int i = 0; i < e->length; i++) {
                e->data[i] = (char)read_n_bytes(f_in, 1);
            }

            (*count) += e->length;
            break;

        default:
            printf("%x\n", e->prefixe & 0b11110000);
            printf("erreur cas default %04x\n", e->prefixe);
            exit(1);
            ;
    }
    return e;
};

midi_track_t* read_midi_track(FILE* f_in) {
    fscanf(f_in, "%*4s");  // lit les 4 caractères MTrk
    midi_track_t* t = malloc(sizeof(midi_track_t));
    t->length = read_n_bytes(f_in, 4);
    // je majore le nombre d'évenements par t->length/4 car c'est la taille du plus petit evènement possible
    t->mtrk_events = malloc(t->length / 4 * sizeof(mtrk_event_t*));
    t->n_events = 0;
    t->count_channel_notes = malloc(128 * sizeof(int));
    for (int i = 0; i < 128; i++) {
        t->count_channel_notes[i] = 0;
    }

    unsigned int i = 0;
    while (i < t->length) {
        t->mtrk_events[t->n_events] = read_mtrk_event(f_in, &i, t->count_channel_notes);
        t->n_events++;
    }

    return t;
};

midi_t* read_midi(char f_name[]) {
    FILE* f_in = fopen(f_name, "r");
    assert(f_in != NULL);

    midi_t* m = malloc(sizeof(midi_t));
    fscanf(f_in, "%*4s");  // lit les 4 caractères MThd

    m->length = read_n_bytes(f_in, 4);

    m->format = read_n_bytes(f_in, 2);
    m->ntrks = read_n_bytes(f_in, 2);
    m->division = read_n_bytes(f_in, 2);
    m->midi_tracks = malloc(m->ntrks * sizeof(midi_track_t*));

    for (unsigned int i = 0; i < m->ntrks; i++) {
        m->midi_tracks[i] = read_midi_track(f_in);
    }

    fclose(f_in);
    return m;
}

void free_midi_note_t(midi_note_t* n) {
    free_sound_t(n->son);
    free(n);
};

void free_notes_linked_list_t(notes_linked_list_t* l) {
    while (l != NULL) {
        notes_linked_list_t* temp = l;
        l = l->next;
        free_midi_note_t(temp->note);
        free(temp);
    }
};

void free_midi_channel_t(midi_channel_t* c) {
    free_notes_linked_list_t(c->linked_list);

    for (int i = 0; i < c->len_notes; i++) {
        free_midi_note_t(c->notes[i]);
    }
    free(c->notes);

    if (c->son->n_samples > 0) {
        free_sound_t(c->son);
    } else {
        free(c->son);
    }

    free(c);
};

int events_to_channels(midi_track_t* t, int division) {
    t->channels = malloc(128 * sizeof(midi_channel_t*));
    for (int i = 0; i < 128; i++) {
        t->channels[i] = malloc(sizeof(midi_channel_t));
        t->channels[i]->len_notes = 0;
        t->channels[i]->notes = malloc(t->count_channel_notes[i] * sizeof(midi_note_t*));
        t->channels[i]->son = malloc(sizeof(sound_t));
        t->channels[i]->son->n_samples = 0;
        t->channels[i]->linked_list = NULL;
    }

    unsigned int ticks = 0;
    double ech_par_tick = (double)0.5 / (division)*Fech;  // defaut 120Bpm
    for (unsigned int i = 0; i < t->n_events; i++) {
        ticks += t->mtrk_events[i]->delta_time;

        if (t->mtrk_events[i]->prefixe == 144) {  // note on
            notes_linked_list_t* elem = malloc(sizeof(notes_linked_list_t));
            elem->note = malloc(sizeof(midi_note_t));

            t->channels[t->mtrk_events[i]->channel]->notes[t->channels[t->mtrk_events[i]->channel]->len_notes] = elem->note;
            t->channels[t->mtrk_events[i]->channel]->len_notes++;

            elem->note->force = t->mtrk_events[i]->data[1];
            elem->note->note = t->mtrk_events[i]->data[0];
            elem->note->start = ticks * ech_par_tick;

            elem->next = t->channels[t->mtrk_events[i]->channel]->linked_list;
            if (t->channels[t->mtrk_events[i]->channel]->linked_list != NULL) {
                t->channels[t->mtrk_events[i]->channel]->linked_list->prev = elem;
            }
            elem->prev = NULL;
            t->channels[t->mtrk_events[i]->channel]->linked_list = elem;
        } else if (t->mtrk_events[i]->prefixe == 128) {  // note off

            notes_linked_list_t* elem = t->channels[t->mtrk_events[i]->channel]->linked_list;

            while (elem->note->note != t->mtrk_events[i]->data[0]) {
                elem = elem->next;
            }

            if (elem->next != NULL) {
                elem->next->prev = elem->prev;
            }
            if (elem->prev != NULL) {
                elem->prev->next = elem->next;
            } else {
                t->channels[t->mtrk_events[i]->channel]->linked_list = elem->next;
            }

            elem->note->end = ticks * ech_par_tick;

            midi_note_to_sound(elem->note);

            if (t->channels[t->mtrk_events[i]->channel]->son->n_samples < elem->note->start + elem->note->son->n_samples) {
                t->channels[t->mtrk_events[i]->channel]->son->n_samples = elem->note->start + elem->note->son->n_samples;
            }

            free(elem);
        } else if (t->mtrk_events[i]->prefixe == 0xff) {
            if (t->mtrk_events[i]->type == 0x51) {
                int micro_sec_par_noire = t->mtrk_events[i]->data[0];
                micro_sec_par_noire = micro_sec_par_noire << 8;
                micro_sec_par_noire += t->mtrk_events[i]->data[1];
                micro_sec_par_noire = micro_sec_par_noire << 8;
                micro_sec_par_noire += t->mtrk_events[i]->data[2];

                double sec_par_noire = (double)micro_sec_par_noire / 1000000;

                ech_par_tick = (double)sec_par_noire / (division)*Fech;
            }
        }
    }
    return ticks * ech_par_tick;
};

bool reduce_channel(midi_channel_t* c) {
    if (c->son->n_samples == 0) {
        return false;
    }

    int indice = 0;

    c->son->samples = malloc(c->son->n_samples * sizeof(int16_t));
    for (unsigned int i = 0; i < c->son->n_samples; i++) {
        int sum = 0;
        int div = 0;

        while (indice < c->len_notes && c->notes[indice]->start == i) {  // ajoute toutes les notes qui commencent à l'échantillon i à la liste chainée
            notes_linked_list_t* elem = malloc(sizeof(notes_linked_list_t));
            elem->note = c->notes[indice];
            elem->next = c->linked_list;
            elem->prev = NULL;
            if (elem->next != NULL) {
                elem->next->prev = elem;
            }
            c->linked_list = elem;
            indice++;
        }

        notes_linked_list_t* elem = c->linked_list;
        while (elem != NULL) {
            sum += elem->note->son->samples[i - elem->note->start];
            div++;

            if (elem->note->start + elem->note->son->n_samples - 1 == i) {
                if (elem->next != NULL) {
                    elem->next->prev = elem->prev;
                }
                if (elem->prev != NULL) {
                    elem->prev->next = elem->next;
                } else {
                    c->linked_list = elem->next;
                }

                notes_linked_list_t* temp = elem;
                elem = elem->next;
                free(temp);

            } else {
                elem = elem->next;
            }
        }

        if (div != 0) {
            c->son->samples[i] = sum / div;
        } else {
            c->son->samples[i] = 0;
        }
    }

    return true;
}

void midi_note_to_sound(midi_note_t* n) {
    float duree = (float)(n->end - n->start) / Fech;
    ADSR_t dafault_adsr = {
        // ceci est arbitraire mais les valeurs de A, D ne peurvent pas etre nulles
        .A = 0.003,
        .D = 0.003,
        .S = 0.75,
        .R = 0.01,
        .peak = 1,

    };

    n->son = sine_ADSR(pitch_to_freq(n->note - 69), n->force * 128, duree, Fech, &dafault_adsr);
};

void reduce_midi(midi_t* m) {
    m->son = malloc(sizeof(sound_t));
    m->son->n_samples = 0;

    float count = 0;
    unsigned char* nb_channels = malloc(m->ntrks * sizeof(char));
    midi_channel_t*** track_channels = malloc(m->ntrks * sizeof(midi_channel_t**));

    for (unsigned int i = 0; i < m->ntrks; i++) {
        track_channels[i] = malloc(128 * sizeof(midi_channel_t*));
        nb_channels[i] = 0;
        for (int a = 0; a < 128; a++) {
            bool res = reduce_channel(m->midi_tracks[i]->channels[a]);
            if (res) {
                track_channels[i][nb_channels[i]] = m->midi_tracks[i]->channels[a];
                nb_channels[i]++;
                count += 1;
            }

            if (m->midi_tracks[i]->channels[a]->son->n_samples > m->son->n_samples) {
                m->son->n_samples = m->midi_tracks[i]->channels[a]->son->n_samples;
            }
        }
    }

    m->son->samples = malloc(m->son->n_samples * sizeof(int16_t));

    for (unsigned int i = 0; i < m->son->n_samples; i++) {
        int sum = 0;

        for (unsigned int a = 0; a < m->ntrks; a++) {
            for (int b = 0; b < nb_channels[a]; b++) {
                if (i < track_channels[a][b]->son->n_samples) {
                    sum += track_channels[a][b]->son->samples[i];
                }
            }
        }

        if (count != 0) {
            m->son->samples[i] = sum / count;
        } else {
            m->son->samples[i] = 0;
        }
    }

    for (unsigned int i = 0; i < m->ntrks; i++) {
        free(track_channels[i]);
    }
    free(track_channels);
    free(nb_channels);
};

void export_midi(char* f_name, midi_t* m) {
    reduce_midi(m);
    save_soud(f_name, m->son);
};
