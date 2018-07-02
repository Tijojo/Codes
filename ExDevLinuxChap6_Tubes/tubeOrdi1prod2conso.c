/********************************
 * Fichier tubeOrdi1prod2conso.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>		// printf
#include <stdlib.h>		// EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>		// fork, exit, pipe, close, write, read
#include <string.h>		// strlen
#include <sys/wait.h>		// wait

int main(void)
{
	int tube[2];
	char buffer;
	pid_t pid_fils1, pid_fils2;

	/* Creation du tube */
	if (pipe(tube) != 0) {
		perror("creation du tube impossible");
		return EXIT_FAILURE;
	}

	pid_fils1 = fork();	// Création du premier fils

	if (pid_fils1 == 0) {	/* Code affecté au premier fils */
		/* Fermeture du descripteur en ecriture puisque le fils veut lire */
		close(tube[1]);
		/* Lecture du tube dans le tube, caractère par caractère avec écriture sur la sortie standard */
		while (read(tube[0], &buffer, 1) > 0) {
			fprintf(stdout, "fils 1 : %c\n", buffer);
		}
		fprintf(stdout, "\n");
		close(tube[0]);
		exit(EXIT_SUCCESS);
	}

	/* Code affecté au père */

	pid_fils2 = fork();	// Création du second fils

	if (pid_fils2 == 0) {	/* Code affecté au second fils */
		/* Fermeture du descripteur en ecriture puisque le fils veut lire */
		close(tube[1]);
		/* Lecture du tube dans le tube, caractère par caractère avec écriture sur la sortie standard */
		while (read(tube[0], &buffer, 1) > 0) {
			fprintf(stdout, "fils 2 : %c\n", buffer);
		}
		fprintf(stdout, "\n");
		close(tube[0]);
		exit(EXIT_SUCCESS);
	}

	/* Fermeture du descripteur en lecture puisque le pere veut écrire */
	close(tube[0]);
	/* Ecriture dans le tube */
	char *chapeaux = "Ils ont des chapeaux ronds, Vive la Bretagne !";
	write(tube[1], chapeaux, strlen(chapeaux));
	close(tube[1]);
	wait(NULL);		/* Attente de la terminaison du premier des deux fils se terminant */
	wait(NULL);		/* Attente de la terminaison du second des deux fils se terminant */
	exit(EXIT_SUCCESS);
}
