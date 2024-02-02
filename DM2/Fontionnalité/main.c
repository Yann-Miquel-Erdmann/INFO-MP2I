#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../src/midi.h"
#include "../src/wav.h"
int main(int argc, char* argv[]) {
    long int t_start = clock();
    if (argc < 3) {
        fprintf(stderr, "Vous devez donner d'entrée et de sortie sous la forme: './midi entrée.mid sortie.wav'\n");
        exit(1);
    }

    midi_t* m = read_midi(argv[1]);

    printf("%s est dans le format %d. Il contient %d pistes.\n", argv[1], m->format, m->ntrks);

    printf("%s est en train d'être converti.\n", argv[1]);
    int max_ech = 0;
    for (unsigned int i = 0; i < m->ntrks; i++) {
        int r = events_to_channels(m->midi_tracks[i], m->division);
        if (r > max_ech) {
            max_ech = r;
        }
    }

    printf("%s a été converti en %s.\n", argv[1], argv[2]);

    printf("%s est en train d'être sauvegardé.\n", argv[2]);

    export_midi(argv[2], m);

    affiche_info(m->son, argv[2]);

    long int t_end = clock();
    printf("Temps écoulé: %.2fs\n", (float)(t_end - t_start) / CLOCKS_PER_SEC);

    free_midi_t(m);
    return 0;
}
