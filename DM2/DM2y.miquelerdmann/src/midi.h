#include <stdio.h>
#include <stdbool.h>
#include "../src/sound.h"

#if !defined(_MIDI_H)
#define _MIDI_H

typedef struct midi_note {  // repésente une note dans une piste midi
    unsigned int start;
    unsigned int end;
    unsigned char note;
    unsigned char force;

    sound_t* son;

} midi_note_t;

// libère l'espace alloué à une structure midi_note 
void free_midi_note_t(midi_note_t* n);

typedef struct notes_linked_list { // élément d'une listee chaînée de midi_note_t
    struct notes_linked_list* prev;
    struct notes_linked_list* next;
    midi_note_t* note;
} notes_linked_list_t;

// libère l'espace alloué à une structure notes_linked_list 
void free_notes_linked_list_t(notes_linked_list_t* l);

typedef struct midi_channel {  // cannal d'une piste midi  
    unsigned char instrument;
    int len_notes;
    midi_note_t** notes;
    notes_linked_list_t* linked_list;
    sound_t* son;
} midi_channel_t;

// libère l'espace alloué à une structure notes_linked_list
void free_midi_channel_t(midi_channel_t* c);

typedef struct mtrk_event {  // événement d'une piste midi 
    unsigned int delta_time;
    unsigned char prefixe;  // FF pour meta event F0 pour sysex par exemple
    unsigned char type;     // uniquement pour les meta-events (prefixe: FF)
    unsigned char channel;

    unsigned int length;  // 32bits
    unsigned char* data;
} mtrk_event_t;

// libère l'espace alloué à une structure mtrk_event
void free_mtrk_event_t(mtrk_event_t* e);

typedef struct midi_track {  // piste midi
    unsigned int length;  // 32bits
    unsigned int n_events;
    mtrk_event_t** mtrk_events;

    unsigned int* count_channel_notes;

    midi_channel_t** channels;

} midi_track_t;
// libère l'espace alloué à une structure midi_track
void free_midi_track_t(midi_track_t* t);

typedef struct midi { // structure repésentant le contenu du fichier midi
    unsigned int length;  // 32bits

    int format;    // 16b
    int division;  // 16b

    unsigned int ntrks;  // 16b
    midi_track_t** midi_tracks;
    sound_t* son;
} midi_t;

// libère l'espace alloué à une structure midi
void free_midi_t(midi_t* m);

// lit un entier de longueur variable dans f_in, incrémente count du nombre d'octets lus puis renvoie l'entier lu
int read_VLV(FILE* f_in, unsigned int* count);


// lit n bits dans f_in
int read_n_bytes(FILE* f_in, int n);

// lit un fichier midi f_name et renvoie son contennu sous la forme d'un pointeur midi_t
midi_t* read_midi(char f_name[]);

// lit une piste d'un fichier midi et renvoie son contennu sous la formee d'un pointeur midi_track_t
midi_track_t* read_midi_track(FILE* f_in);

// lit un événement d'une piste midi et renvoie son contennu sous la formee d'un pointeur mrtk_event_t
mtrk_event_t* read_mtrk_event(FILE* f_in, unsigned int* count, unsigned int* count_channel_notes);

// génère l'attribut son de type sound_t d'une note midi n
void midi_note_to_sound(midi_note_t* n);

// stocke les événements d'une piste t dans leurs cannaux respectifs 
int events_to_channels(midi_track_t* t, int division);

// superpose les sons de chaque note du cannal c en un seul sound_t
bool reduce_channel(midi_channel_t* c);

// superpose les sonds de chaque cannal de chaque piste du fichier midi m en un seul sound_t
void reduce_midi(midi_t* m);

// expxorte le son du midi vers un fichier wav nommé f_name 
void export_midi(char* f_name, midi_t* m);

#endif  // _MIDI_H
