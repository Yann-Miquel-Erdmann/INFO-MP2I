// #include "graphe.h"
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

typedef struct g {
  int n;
  float** adj;
} graphe_t;

float min(float x, float y){
    if (x<=y){
        return x;
    }
    return y;
}


float** floyd_warshall(graphe_t* g){
    float** out = malloc(sizeof(float*)* g->n);
    for (int i = 0; i < g->n; i++){
        out[i] = malloc(sizeof(float)*g->n);
        for (int j = 0; j < g->n; j++){
            out[i][j] = g->adj[i][j];
        }
    }

    for (int k = 0; k< g->n; k++){
        for (int i = 0; i < g->n; i++) {
            for (int j = 0; j < g->n; j++) {
                out[i][j] = min(out[i][j], out[i][k]+out[k][j]);
            }
        }
    }

    return out;
}


graphe_t* lire(char* filename){
    FILE* f = fopen(filename, "r");
    graphe_t* g = malloc(sizeof(graphe_t));

    fscanf(f,"%d", &(g->n));
    g->adj = malloc(sizeof(float*)*g->n);
    for (int i = 0; i < g->n; i++) {
        g->adj[i] = malloc(sizeof(float)* g->n);
        for (int j = 0; j < g->n; j++) {
            printf("%d %d\n", i,j);
            fscanf(f, "%f", &(g->adj)[i][j]);
            if (g->adj[i][j] == -1){
                g->adj[i][j] = INFINITY;
            }
        }

    }
    fclose(f);
    return g;
}

int main(){
    
    // graphe_t* g = lire("graphe1.txt");
    float A1[5] = {0, 2,INFINITY,-1,INFINITY};
    float A2[5] = {INFINITY, 0, 2,INFINITY,INFINITY};
    float A3[5] = {INFINITY, INFINITY, 0, -1, INFINITY};
    float A4[5] = {2, INFINITY, INFINITY,0,2};
    float A5[5] = {INFINITY, INFINITY, 1, INFINITY,0};
    
    graphe_t* g = malloc(sizeof(graphe_t));
    g->n = 5;
    g->adj = malloc(sizeof(float*)*g->n);
    // g->adj[0] = 
    g->adj[0] = A1;
    g->adj[1] = A2;
    g->adj[2] = A3;
    g->adj[3] = A4;
    g->adj[4] = A5;

    for (int i = 0; i<g->n; i++){
        for (int j = 0; j<g->n; j++){
            printf("%f ", g->adj[i][j]);
        }
        printf("\n");
    }

    
    float** dist = floyd_warshall(g);
    

    for (int i = 0; i<g->n; i++){
        for (int j = 0; j<g->n; j++){
            printf("%f ", dist[i][j]);
        }
        printf("\n");
    }

}