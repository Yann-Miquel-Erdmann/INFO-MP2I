#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void tri_insertion(int *t, int n) {
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        while (j >= 0 && t[j + 1] < t[j]) {
            int temp = t[j];
            t[j] = t[j + 1];
            t[j + 1] = temp;
            j--;
        }
    }
}

bool est_trie(int *t, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (t[i] > t[i + 1]) {
            return false;
        }
    }
    return true;
}

void affiche_tab(int *t, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", t[i]);
    }
    printf("\n");
}

int partition(int *t, int a, int b, int i) {
    if (i != a) {
        int temp = t[i];
        t[i] = t[a];
        t[a] = temp;
    }
    printf("start %d %d\n", a,b);
    int lo = a;
    int hi = b;

    bool up= true;
    while (hi - lo > 1){
        if (up){
            if (t[hi] >= t[lo] ){
                hi--;
            }else{
                int temp = t[hi];
                t[hi] = t[lo];
                t[lo] = temp;
                up == !up;
                lo++;
            }
        }else{
            if (t[lo] > t[hi]) {
                lo++;
            } else {
                int temp = t[hi];
                t[hi] = t[lo];
                t[lo] = temp;
                up == !up;
                hi--;
            }
        }
    }

    
    if (up){
        lo --;
        printf("1: j = %d t[j] %d\n",lo, t[lo] );
        exit(1);
        return lo;
    }else{
        hi++;
        printf("2: j = %d t[j] %d\n", hi, t[hi]);
        exit(1);

        return hi;
    }
}


void tri_rapide(int *t, int a, int b){
    if (a<b){
        int j = partition(t,a,b,a);
        affiche_tab(t, 4);
        printf("j = %d\n",j);
        tri_rapide(t,a,j-1);
        tri_rapide(t,j+1,b);
        
    }
}

int main(int argc, char const *argv[]) {
    int *t = malloc(4 * sizeof(int));
    t[0] = 2;
    t[1] = 3;
    t[2] = 5;
    t[3] = 1;

    affiche_tab(t, 4);
    tri_rapide(t,0,3);
    // tri_insertion(t, 4);

    affiche_tab(t, 4);

    // if (est_trie(t, 4)) {
    //     printf("trie\n");
    // } else {
    //     printf("n'est pas trie\n");
    // }

    return 0;
}
