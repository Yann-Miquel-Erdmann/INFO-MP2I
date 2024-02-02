#include "../src/sound.h"
#include "../src/melody.h"
#include "../src/wav.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[])
{
    long int time_start = clock();
    if (argc<3){
        fprintf(stderr, "Vous devez donner le fichier d'entrée et de sortie sous la forme: './wav_writer entrée.txt sortie.wav'\n");
        exit(1);
    }

    mix_t * mix = load_mix(argv[1]);
    sound_t* s_out = reduce_mix(mix);
    save_soud(argv[2], s_out);
    long int time_end = clock();

    

    affiche_info(s_out,argv[2]);
    printf("Temps écoulé: %.2fs\n", (float)(time_end - time_start) / CLOCKS_PER_SEC);

    free_mix_t(mix);
    free_sound_t(s_out);

    return 0;
}
