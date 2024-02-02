#include <assert.h>
#include <stdio.h>

#include "../src/sound.h"
#include "../src/wav.h"
#include "../src/waveform.h"
#include "../src/melody.h"




int main(int argc, char const* argv[]) {

    mix_t* m = load_mix("questions/test1.txt");
    assert(m->n_tracks == 2);
    assert(m->vols[0] == 1);
    assert(m->vols[1] == 1);

    // vérifie le nombre de sons par piste
    assert(m->tracks[0]->n_sounds == 34);
    assert(m->tracks[1]->n_sounds == 21);

    // vérifie la premère note de la piste 0
    assert(m->tracks[0]->sounds[0]->n_samples == 44100);
    assert(m->tracks[0]->sounds[0]->samples[0] == 0);
    assert(m->tracks[0]->sounds[0]->samples[44099] == 0);

    // vérifie la premère note de la piste 1

    assert(m->tracks[1]->sounds[8]->n_samples == 22050);
    assert(m->tracks[1]->sounds[8]->samples[0] == 0);
    assert(m->tracks[1]->sounds[8]->samples[22049] == 0);

    return 0;
}
