#include <assert.h>
#include <stdio.h>

#include "../src/midi.h"
#include "../src/sound.h"
#include "../src/wav.h"
#include "../src/waveform.h"

int main(int argc, char const* argv[]) {
    midi_t* m = read_midi("midi/b5open.mid");
    printf("%d %d %d %d\n", m->division, m->format, m->length, m->ntrks);
    assert(m->division == 120);
    assert(m->format == 1);
    assert(m->length == 6);
    assert(m->ntrks == 6);

    for (unsigned int i = 0; i < m->ntrks; i++) {
       events_to_channels(m->midi_tracks[i], m->division);
    }


    // vérifie que la note la première note de la piste 1 dans le cannal 2 est un sol5 avec une vitesse de 55
    assert(m->midi_tracks[1]->channels[2]->notes[0]->note == 67);
    assert(m->midi_tracks[1]->channels[2]->notes[0]->force == 55);
    assert(m->midi_tracks[1]->channels[2]->notes[0]->start == 11025);

    // vérifie que la note la première note de la piste 1 dans le cannal 2 est un sol5 avec une vitesse de 99
    assert(m->midi_tracks[2]->channels[7]->notes[0]->note == 67);
    assert(m->midi_tracks[2]->channels[7]->notes[0]->force == 99);
    assert(m->midi_tracks[2]->channels[7]->notes[0]->start == 11025);


    return 0;
}
