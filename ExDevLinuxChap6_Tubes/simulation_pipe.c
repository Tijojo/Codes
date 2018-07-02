/********************************
 * Fichier simulation_pipe.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int tube1[2], tube2[2];
	char *cmd1[3] = { argv[1], argv[2], NULL };
	char *cmd2[3] = { argv[3], argv[4], NULL };
	char *cmd3[3] = { argv[5], argv[6], NULL };

	if (argc != 7) {
		fprintf(stderr, "Usage : %s ...\n", argv[0]);
		exit(1);
	}

	/* appel à pipe(tube1) : consulter le manuel */
	/* appel à pipe(tube2) : consulter le manuel */

	if (fork() == 0) {	/* cmd 1 */
		/* appel à dup2(?) : consulter le manuel */
		/*   il faut rediriger la sortie (1) dans le tube1 */
		/* appels à close(?) sur les IO non utilisées des tubes */
		execvp(cmd1[0], cmd1);
	} else if (fork() == 0) {	/* cmd 2 */
		/* appels à dup2(?) : consulter le manuel */
		/*   il faut rediriger l'entrée (0) dans le tube1 */
		/*   il faut rediriger la sortie (1) dans le tube2 */
		/* appels à close(?) sur les IO non utilisées des tubes */
		execvp(cmd2[0], cmd2);
	} else if (fork() == 0) {	/* cmd 3 */
		/* appel à dup2(?) : consulter le manuel */
		/*   il faut rediriger l'entrée (0) dans le tube2 */
		/* appels à close(?) sur les IO non utilisées des tubes */
		execvp(cmd3[0], cmd3);
	} else {
		/* appels à close(?) sur les IO non utilisées des tubes */
		wait(NULL);
		wait(NULL);
		wait(NULL);
	}

	exit(0);
}
