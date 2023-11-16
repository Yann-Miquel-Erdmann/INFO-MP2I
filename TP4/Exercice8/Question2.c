// Je vais utiliser un tableau 2D de taille 8n/K x (8K +1) pour pouvoir afficher chaque ligne comme une string en mettant caractère nul à la fin de chaque ligne du tableau ce qui me permet de n'avoir qu'une boucle pour l'affichage

// itère sur la chaine de caractères phrase et retire les caractères de la chaîne in qui ne possèdent pas de format image et que l'on ne pourra pas afficher correctement. la nouvelle chaîne remplace celle en entrée
void check_phrase(char * phrase);


// Cette fontion est optionnelle
// modifie la chaîne de caratères phrase pour qu'un mot ne soit pas coupé par un retour à la ligne si c'est possible 
// (un mot de plus de K caractères sera forcément coupé). Si c'est possible elle ajoute des espaces avant le mot pour le décaler.
// retire un espace si c'est le premier ccaractère d'une ligne
// Stocke la nouvelle chaine à la place de l'ancienne (realloc si besoin) renvoie la taille de la nouvelle chaîne de caractères. 
int optimise_phrase(char ** phrase, unsigned int K);


// revoie le nom du fichier correspondant au char c (il existe forcément un fichier d'après check_phrase)
char * img_filename(char c);

// pour chaque caractère de phrase elle appelle img_filename, lit le fichier correspondant, met les pixels correspondants dans la matrice (vide et plein) et met un caractère nul après K "grandes" lettres puis retourne à la ligne et contine
void fill_matrix(char ** matrix, char * phrase, unsigned int K, char pixel);


// pour la matrice matrix de m linges, affiche chaque ligne comme une chaîne de caractères 
void print_matrix(char ** matrix, unsigned int m);

// prend comme paramètres caractère à utiliser comme le pixel à utiliser, le nombre K de caractères par ligne, et si elle doit optimiser l'affichage
// demande à l'utilisateur d'entrer une phrase de 64 caractères au maximum
// appelle la fonction check_phrase pour éliminer les potentiels caractères non supportés
// appelle la fonction optimise_phrase pour formatter la phrase
// crée la matrice matrix de taille 8n/K x (8K +1) ou n est la taille de la phrase formatée et K le nombre de lettres par ligne
// appelle la fonction fill_matrix pour remplir la maatrice matrix avec les images des lettres
// affiche la matrice matrix dans la console
void main(int argc, char** argv);