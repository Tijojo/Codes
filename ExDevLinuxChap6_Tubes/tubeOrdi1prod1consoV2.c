/********************************
 * Fichier tubeOrdi1prod1consoV2.c
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
	pid_t pid_fils;

	/* Creation du tube */
	if (pipe(tube) != 0) {
		perror("creation du tube impossible");
		exit(EXIT_FAILURE);
	}

	pid_fils = fork();

	if (pid_fils != 0) {	/* Code affecté au pere */
		/* Fermeture du descripteur en lecture puisque le pere veut écrire */
		close(tube[0]);
		sleep(10);	// <- Cette ligne seulement a été ajoutée
		/* Ecriture dans le tube */
		char *chapeaux = "Ils ont des chapeaux ronds, Vive la Bretagne !";
		write(tube[1], chapeaux, strlen(chapeaux));
		close(tube[1]);
		wait(NULL);	/* Attente de la terminaisonn du processus fils */
		exit(EXIT_SUCCESS);
	} else {		/* Code affecté au fils */
		/* Fermeture du descripteur en ecriture puisque le fils veut lire */
		close(tube[1]);
		/* Lecture du tube dans le tube, caractère par caractère avec écriture sur la sortie standard */
		while (read(tube[0], &buffer, 1) > 0)
		  fprintf(stdout, "%s", &buffer);
		fprintf(stdout, "\n");
		close(tube[0]);
		exit(EXIT_SUCCESS);
	}
}
