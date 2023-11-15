#include <string.h>
#include <stdio.h>


struct etudiant {
	char* prenom;
	unsigned int age;
};
typedef struct etudiant etu_t;

typedef struct equipe{
	unsigned int nb_membres;
	etu_t** membres; // tableaux de pointeurs vers les membres de l'equipe
	unsigned int indice_cpt; // indice du capitaine dans le tableau des membres
} equipe_t;


void print_etu(etu_t * e){
    printf("- %s, %d ans\n", e->prenom, e->age);
};

void print_equipe(equipe_t * e){
    printf("équipe de %d joueurs\n", e->nb_membres);
    printf("Le capitaine de l'équipe est %s\n",e->membres[e->indice_cpt]->prenom);
    for (unsigned int i = 0; i<e->nb_membres; i++){
        print_etu(e->membres[i]);
    }
    printf("\n");
}

int main(){
	etu_t camille = {
		.prenom = "Camille",
		.age = 23,
	};
	etu_t leila = {
		.prenom = "Leila",
		.age = 20,
	};
	etu_t thibault = {
		.prenom = "Thibault",
		.age = 22,
	};

	etu_t * T[3] = {&camille, &leila, &thibault };
	

	equipe_t team = {
		.nb_membres = 3,
		.membres = T, 
		.indice_cpt = 1,
	};

    print_equipe(&team);
}
