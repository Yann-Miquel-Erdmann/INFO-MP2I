#include <math.h>
#include "melody.h"

#include <stdio.h>
float pitch_to_freq(int i){
    return 440 * pow(2, (float)(i/12.0));
}


void main(){
    for (int i = -12; i <= 12; i++){
        printf("%i %f\n", i, pitch_to_freq(i));
    }
}