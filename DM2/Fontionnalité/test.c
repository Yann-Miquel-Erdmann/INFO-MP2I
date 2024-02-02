#include "../src/waveform.h"
#include "../src/wav.h"
#include "../src/sound.h"

#include <stdio.h>

int main(int argc, char const *argv[])
{
    ADSR_t adsr = {
        .A = 0.01,
        .D = 0.01,
        .S = 0.75,
        .R = 0.05,
        .peak = 1,

    } ;
    sound_t* s = sine_ADSR(440, 0x3FFF, 3, Fech, &adsr);
    save_soud("testADSR.wav", s);
    free_sound_t(s);
    

    return 0;
}
