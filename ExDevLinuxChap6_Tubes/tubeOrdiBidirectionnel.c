/********************************
 * Fichier tubeOrdiBidirectionnel.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
/* Solution proposée par David Guennec, merci David */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int tube1[2]; // le fils 2 va y écrire et le fils 1 va y lire
	int tube2[2]; // le fils 1 va y écrire et le fils 2 va y lire
	char buffer1[50]; /* Attention à choisir une taille de buffer1 suffisament grande */
	char buffer2[50]; /* Attention à choisir une taille de buffer2 suffisament grande */
	ssize_t nb_lus;
	pid_t pidfils1 = -1;
	pid_t pidfils2 = -1;

	/* Creation des tubes */
	if (pipe(tube1) != 0) {
		printf("creation du tube1 impossible");
		return EXIT_FAILURE;
	}
	if (pipe(tube2) != 0) {
		printf("creation du tube2 impossible");
		return EXIT_FAILURE;
	}

	pidfils1 = fork();	// Création du premier fils

	if (pidfils1 == 0) {	/* Code affecté au premier fils */
		/* Fermeture du descripteur en ecriture sur tube 1 puisque le fils 1 veut lire dans le tube1 */
		close(tube1[1]);
		/* Fermeture du descripteur en lecture sur tube 2 puisque le fils 1 veut écrire dans le tube2 */
		close(tube2[0]);
		/* Ecriture dans tube2 */// Attention à commencer par ecrire chez l'un des deux fils sinon interblocage
		write(tube2[1], "Ils ont des chapeaux ronds, Vive la Bretagne", 44);
		fprintf(stdout,
			"Fils1 (pid:%d) : Ecriture de \"Ils ont des chapeaux ronds, Vive la Bretagne\" dans le tube2\n",
			getpid());
		/* Lecture du tube1 */
		fprintf(stdout, "Fils 1 (pid:%d) : Lecture 1 depuis le tube1\n", getpid());
		nb_lus = read(tube1[0], &buffer1, 44);
		printf("%s bien recu par le fils 1 (pid :%d, ppid :%d), %zu octets lus\n",
		       buffer1, getpid(), getppid(), nb_lus);
		/* Fermeture des descripteurs et sortie du programme */
		close(tube1[0]);
		close(tube2[1]);
		exit(EXIT_SUCCESS);
	}
	// Code executé par le pere

	pidfils2 = fork();	// Création du second fils

	if (pidfils2 == 0) {	/* Code affecté au second fils */
		/* Fermeture du descripteur en ecriture sur tube 2 puisque le fils 2 veut lire dans le tube2 */
		close(tube2[1]);
		/* Fermeture du descripteur en lecture sur tube 1 puisque le fils 2 veut écrire dans le tube1 */
		close(tube1[0]);
		/* Ecriture dans tube1 */ // Attention à commencer par ecrire chez l'un des deux fils sinon interblocage
		write(tube1[1], "Ils ont des tonneaux ronds, Vive les bretons", 44);
		fprintf(stdout,
			"Fils2 (pid:%d) : Ecriture de \"Ils ont des tonneaux ronds, Vive les bretons\" dans le tube1\n",
			getpid());
		/* Lecture du tube2 */
		fprintf(stdout, "Fils 2 (pid:%d) : Lecture 1 depuis le tube1\n", getpid());
		nb_lus = read(tube2[0], &buffer2, 44);
		printf("%s bien recu par le fils 2 (pid :%d, ppid :%d), %zu octets lus\n",
		       buffer2, getpid(), getppid(), nb_lus);
		/* Fermeture des descripteurs et sortie du programme */
		close(tube2[0]);
		close(tube1[1]);
		exit(EXIT_SUCCESS);
	}
	// Code executé par le pere

	wait(NULL);
	wait(NULL);
	exit(EXIT_SUCCESS);

}
