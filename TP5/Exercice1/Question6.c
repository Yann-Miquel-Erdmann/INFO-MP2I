#include <string.h>
#include <stdio.h>
#include <stdlib.h>


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


void free_etu(etu_t * e){
    free(e);
}

void free_equipe(equipe_t * e){
    for (unsigned int i = 0; i< e->nb_membres; i++){
        free_etu(e->membres[i]);
    }

    free(e->membres);
    free(e);
}



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


void agrandir_equipe(equipe_t * dst, equipe_t* src){
    dst->membres = realloc(dst->membres, (dst->nb_membres+ src->nb_membres)*sizeof(etu_t *));
    if (src->nb_membres > dst->nb_membres){
        dst->indice_cpt = src->indice_cpt + dst->nb_membres;
    } 
    for (unsigned int i = 0; i< src->nb_membres ; i++){
        dst->membres[dst->nb_membres] = src->membres[i];
        dst->nb_membres++;
    }
    free(src->membres);
    free(src);
}

int main(){
	etu_t *camille = malloc(sizeof(etu_t));
    camille->prenom = "Camille";
    camille->age = 23;

	etu_t *leila = malloc(sizeof(etu_t));
    leila->prenom = "Leila";
    leila->age = 20;

	etu_t *thibault = malloc(sizeof(etu_t));
    thibault->prenom = "Thibault";
    thibault->age = 22;

    etu_t** membres = malloc(3*sizeof(etu_t *));
    membres[0] = camille;
    membres[1] = leila;
    membres[2] = thibault;	

    equipe_t * team = malloc(sizeof(equipe_t));
    team->nb_membres = 3;
    team->membres = membres;
    team->indice_cpt=1 ;


    // ------ equipe 2
    etu_t *jean = malloc(sizeof(etu_t));
    jean->prenom = "Jean";
    jean->age = 23;

	etu_t *pierre = malloc(sizeof(etu_t));
    pierre->prenom = "Pierre";
    pierre->age = 20;

    etu_t** membres2 = malloc(2*sizeof(etu_t *));
    membres2[0] = jean;
    membres2[1] = pierre;

    equipe_t * team2 = malloc(sizeof(equipe_t));
    team2->nb_membres = 2;
    team2->membres = membres2;
    team2->indice_cpt=1 ;

    print_equipe(team);

    print_equipe(team2);

    agrandir_equipe(team2,team);
    print_equipe(team2);

    free_equipe(team2);
}
