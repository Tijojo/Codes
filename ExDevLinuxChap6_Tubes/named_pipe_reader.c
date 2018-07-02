/********************************
 * Fichier named_pipe_reader.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thionl
 *
 ********************************/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	int tub_nomme;
	char buf[44];

	/* Ouverture du tube pour lecture */
	tub_nomme = open("my_named_pipe", O_RDONLY);
	if (tub_nomme == -1) {
		perror("ouverture du tube impossible dans le processus lecteur\n");
		return EXIT_FAILURE;
	}

	/* Lecture dans le tube */
	while (read(tub_nomme, buf, 44)) {
		printf("Je viens de lire : %s\n", buf);
	}

	/* Fermeture du tube */
	close(tub_nomme);

	/* Suppression du tube */
	unlink("my_named_pipe");

	return EXIT_SUCCESS;
}
