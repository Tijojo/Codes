/********************************
 * Fichier serveur-pipe-sol.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h>
#include <stdlib.h>		// EXIT_SUCCESS
#include <fcntl.h>		// O_WRONLY et O_RONLY
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>		// tubes

//!
// PROCESSUS SERVEUR
//

int main(void)
{
	int tub1;
	int tub2;
	int nb1, nb2, res;
	char ent[5];
	int res_fifo = 0;

	unlink("tube1");
	unlink("tube2");

	/* Creation des tubes */
	res_fifo = mkfifo("tube1", 0666);

	if (res_fifo != 0) {
		printf
		    ("Creation du tube impossible du premier tube (tube existant peut-etre?) \n");
		exit(EXIT_FAILURE);
	}
	res_fifo = mkfifo("tube2", 0666);
	if (res_fifo != 0) {
		printf
		    ("Creation du tube impossible du second tube (tube existant peut-etre?) \n");
		exit(EXIT_FAILURE);
	}

	/* Ouverture du tube 1 en lecture */
	tub1 = open("tube1", O_RDONLY);

	/* Ouverture du tube 2 en ecriture */
	tub2 = open("tube2", O_WRONLY);

	/* Lecture des nombres a additionner dans le tube */
	read(tub1, ent, 5);
	nb1 = atoi(ent);
	read(tub1, ent, 5);
	nb2 = atoi(ent);

	res = nb1 + nb2;
	sprintf(ent, "%d", res);

	write(tub2, ent, 5);

	/* Fermeture des tubes */
	close(tub1);
	close(tub2);

	exit(EXIT_SUCCESS);
}
