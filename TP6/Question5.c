#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void tri_insertion(int *t, int n) {
    for (int i = 1; i < n; i++) {
        int j = i-1;
        while (j >= 0 && t[j+1] < t[j]) {
            int temp = t[j];
            t[j] = t[j+1];
            t[j+1] = temp;
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

int main(int argc, char const *argv[]) {
    int *t = malloc(4 * sizeof(int));
    t[0] = 4;
    t[1] = 0;
    t[2] = 0;
    t[3] = 0;
    affiche_tab(t,4);
    tri_insertion(t, 4);

    affiche_tab(t, 4);

    if (est_trie(t, 4)) {
        printf("trie\n");
    } else {
        printf("n'est pas trie\n");
    }

    return 0;
}
