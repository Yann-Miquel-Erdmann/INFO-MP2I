#include <stdio.h>
#include <time.h>

// ecrit le mois et l'année actuelle dans la console
void main(){
    const unsigned int jour = 24*60*60;
    const float mois = 30.44*jour;
    const float annee = 365.24*jour;

    int time_actuelle = time(NULL);

    int annee_actuelle = time_actuelle / annee;
    time_actuelle -= annee_actuelle * jour * 365.24;
    int mois_actuel = time_actuelle/mois + 1;
    
    printf("Nous sommes en %d/%d \n", mois_actuel , annee_actuelle + 1970);
}