#include "sound.h"

#if !defined(_WAVEFORM_H)
#define _WAVEFORM_H
// génère un son blanc de durée duree à une fréquence d'echantillonnage f_ech
sound_t* white(float duree, int f_ech);

// génère un son à partir d'une sinusoïde d'amplitude amplitude et de durée duree à une fréquence d'echantillonnage f_ech
sound_t* sine(float freq, int amplitude, float duree, int f_ech);

// génère un son à partir d'un signal créneau d'amplitude amplitude et de durée duree à une fréquence d'echantillonnage f_ech
sound_t * square( float freq , int amplitude , float duree , int f_ech );

// génère un son à partir d'un signal triangle d'amplitude amplitude et de durée duree à une fréquence d'echantillonnage f_ech
sound_t * triangle( float freq , int amplitude , float duree , int f_ech ) ;

// génère un son à partir d'un signal en dents de scie d'amplitude amplitude et de durée duree à une fréquence d'echantillonnage f_ech
sound_t * sawtooth ( float freq , int amplitude , float duree , int f_ech ) ;

typedef struct ADSR {  // enveloppe attack decay sustain release
    float A; // duree de l'attaque
    float D;  // duree du decay
    float S; // amplitude à l'équilibre entre 0 et 1
    float R;    // durée du release
    float peak;  // amplitude au max entre 0 et 1

} ADSR_t;

// génère un tableau d'amplitudes entre 0 et 1 correspondant à l'enveloppe adsr pour un son de durée duree et renvoie le nombre d'échantillons qui représenteront le son  
int compute_ADSR(ADSR_t * adsr, float** amplitudes,float duree, int freq_ech);  

// les fonctions ci desssous sont les mêmes que d'au-dessus mais elles appliquent l'enveloppe adsr au signal
sound_t* sine_ADSR(float freq, int amplitude, float duree, int f_ech, ADSR_t* adsr);
sound_t * square_ADSR( float freq , int amplitude , float duree , int f_ech, ADSR_t* adsr );
sound_t * triangle_ADSR( float freq , int amplitude , float duree , int f_ech, ADSR_t* adsr ) ;
sound_t * sawtooth_ADSR ( float freq , int amplitude , float duree , int f_ech, ADSR_t* adsr ) ;




#endif // _WAVEFORM_H
