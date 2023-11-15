#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>



int bord_X = 72, bord_Y= 22; // taille du "terrain" 70px par 30px 

int ball_X, ball_Y, v_X,  v_Y; // position et vitess de la balle dans les deux directions 
// il serait préférable d'utiliser struct

// calcule la position de la balle pour l'image suivante ajoutant la vitesse à la position 
// et change de direction si la balle atteint un des bords 
void move(){
    assert(ball_X>0);
    assert(ball_X<bord_X-1);
    assert(ball_Y>0);
    assert(ball_Y<bord_Y-1);

    if (ball_X == 1 || ball_X == bord_X-2){
        v_X *= -1;
    }

    if (ball_Y == 1 || ball_Y == bord_Y-2){
        v_Y *= -1;
    }

    ball_X += v_X;
    ball_Y += v_Y;
}

// efface l'image précédente puis affiche la balle et les murs à l'écran
void draw(){
    printf("\33[H\33[J\r"); // efface l'écran

    for (int y = 0; y<bord_Y; y++){
        for (int x = 0; x<bord_X; x++){
            if (x == 0 || y == 0 || x == bord_X -1 || y == bord_Y-1){
                printf("#");
            }else{
                if (x == ball_X && y == ball_Y){
                    printf("\e[1mO\e[0m");
                }else{
                    printf(" ");
                }
            }
            
        }   
        printf("\n");
    }

}


void main(){
    draw();
    printf("Veillez à ce que le rectangle apparaisse en entier dans le terminal.\n Tapez ENTRER quand c'est le cas.\n");
    getchar();

    
    srand(clock());
    ball_X = 2 + rand()%(bord_X-3); // place la balle a des coordonnées aléatoires
    ball_Y = 2 + rand()%(bord_Y-3);

    // donne une direction aléatoire à la balle
    if (rand()%2){
        v_X = 1;
    }else{
        v_X = -1;
    }
    
    if (rand()%2){
        v_Y = 1;
    }else{
        v_Y = -1;
    }


    clock_t start,end,delta;
    float deltaSec, secToWait;
    long int nsToWait;
    struct timespec wait; 
    wait.tv_sec = 0;


    while (0 == 0){ // boucle infinie qui affiche les images rapidement pour donner l'illusion du mouvement
        start = clock();
        draw();
        move();
        end = clock();
        delta = end - start;
        deltaSec = ((float)delta)/CLOCKS_PER_SEC; // calcul du temps (en secondes) pris pour l'affichage

        secToWait = 0.1 - deltaSec; // calcul du temps (en secondes) à attendre pour faire 10 FPS
        
        nsToWait = secToWait * 1000000000;
        wait.tv_nsec = nsToWait;
        
        nanosleep(&wait,NULL); // attente

    }


}

