#include "./file.h"

#include <stdio.h>

int main(int argc, char const *argv[])
{
    file_t* p = file_vide();

    enfiler(p,1);
    affiche_file(p);

    enfiler(p,2);
    affiche_file(p);

    enfiler(p,3);
    affiche_file(p);

    enfiler(p,4);
    affiche_file(p);

    printf("entier depilé: %d\n",defiler(p));
    affiche_file(p);
    defiler(p);
    defiler(p);
    defiler(p);

    affiche_file(p);

    printf("est vide: %d\n", est_file_vide(p));

    free_file(p);

    return 0;
}
