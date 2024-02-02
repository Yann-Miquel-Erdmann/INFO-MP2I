### DM2
## dossier source
Le dossier source scr contient l'ensemble des fichiers source du DM, les fichiers main sont dans des dossiers respectifs avec un fichier de tests

## Questions 
le fichier main dans le dossier questions est la réponse à la question 19. Il permet de transformer un fichier texte comprennant des informations sur un ensemble de sons en un fichier audio wav.

Il se compile de la façon suivante

    gcc questions/main.c src/* -o questions.out -lm

et s'exécute avec la commande

    ./questions.out entrée.txt sortie.wav



## Fontionnalité additionnelle
Comme fonctionnalité addictionnelle j'ai fait un programme qui lit des fichiers midi et qui les convertit en fichier wav.
Il supporte les fichiers midi de type 0 et 1.
Il lit les notes du fichier midi et génère les sons corresspondant, pour l'instant les sons ne sont que des fonctions sinusoïdales mais il serait possible d'asssigner un type de fonction à chaque instrument.
Les sons générés avec une enveloppe pour enlever les chocs en début et en fin de note.

La fontionnalité additionnelle se compile de la manière suivante

    gcc midi/main.c src/* -o convertisseur_midi.out -lm

et s'execute de la mmanière suivante

    ./convertisseur_midi.out entrée.mid sortie.wav