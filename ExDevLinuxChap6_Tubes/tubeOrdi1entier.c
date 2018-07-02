/********************************
 * Fichier tubeOrdi1entier.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// printf, scanf
#include <stdlib.h>		// EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>		// fork, exit, pipe, close, write, read
#include <sys/wait.h>		// wait

int main(void)
{
	int tube[2];
	pid_t pid_fils;
	int entier = 0;

	/* Creation du tube */
	if (pipe(tube) != 0) {
		perror("creation du tube impossible");
		exit(EXIT_FAILURE);
	}

	pid_fils = fork();

	if (pid_fils != 0) {
	        /* Code affecté au pere */
		close(tube[0]);	/* Fermeture du descripteur en lecture puisque le pere veut écrire */
		/* Attente entier */
		printf("Veuillez entrer un entier : \n");
		scanf("%d", &entier);
		/* Ecriture dans le tube */
		write(tube[1], &entier, sizeof(int));
		close(tube[1]); /* Fermeture du descripteur en ecriture */
		wait(NULL);	/* Attente de la terminaisonn du processus fils */
		exit(EXIT_SUCCESS);
	} else {
	        /* Code affecté au fils */
		close(tube[1]);	/* Fermeture du descripteur en ecriture puisque le fils veut lire */
		/* Lecture du tube dans le tube, calcul du carré */
		read(tube[0], &entier, sizeof(int));  /* Lecture de l'entier */
		printf("Entier : %d\n", entier);  /* Affichage sur stdout */
		printf("Carré : %d\n", entier * entier);  /* Affichage sur stdout */
		close(tube[0]); /* Fermeture du descripteur en lecture */
		exit(EXIT_SUCCESS);
	}
}
