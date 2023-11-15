#include <stdio.h>

int main(){
	// créer une variable x, initialement nulle
	int x =  0 ;
	
	// créer une variable y, valant 5 initialement
	
	int y = 5;


	// modifier x en lui assignant x+y
	
	x = x+y;

	// modifier y en lui assignant y+x
	
	y = y+x;

	// répéter les deux dernières étapes une fois de plus

	x = x+y;

	// modifier y en lui assignant y+x
	
	y = y+x;
	
	// afficher x et y
	printf("x vaut %d, y vaut %d\n", x, y);
	return 0;
}
