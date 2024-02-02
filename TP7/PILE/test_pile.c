#include "./pile.h"

#include <stdio.h>

int main(int argc, char const *argv[])
{
    pile_t* p = pile_vide();

    empiler(p,1);
    print_pile(p);

    empiler(p,2);
    print_pile(p);

    empiler(p,3);
    print_pile(p);

    empiler(p,4);
    print_pile(p);

    printf("entier depilé: %d\n",depiler(p));
    print_pile(p);
    depiler(p);
    depiler(p);
    depiler(p);

    print_pile(p);

    printf("est vide: %d\n", est_vide(p));

    free_pile(p);

    return 0;
}
