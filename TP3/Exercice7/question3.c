#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// remplit les n premières cases d'un tableau avec des entiers aléatoires entre -10 et 10 
void randomise(int* tab, int n){
    for (int i = 0; i<n;i++){
        tab[i] =  (rand()%21)-10;        
    }
}


int main(){
    srand(time(NULL));
    int t[6] = {2,3,5,1,-3,3};
    randomise(t,6);

}