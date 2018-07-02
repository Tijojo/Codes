/********************************
 * Fichier client-pipe-sol.c
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

//
// PROCESSUS CLIENT
//

int main(void)
{
	int tub1;
	int tub2;
	int nb1, nb2, res;
	char ent[5];

	tub1 = open("tube1", O_WRONLY);

	tub2 = open("tube2", O_RDONLY);

	printf("Entrez les nombres de maximum 3 chiffres a additionner\n");
	scanf("%d %d", &nb1, &nb2);

	printf("Nombres lus : %d et %d\n", nb1, nb2);

	sprintf(ent, "%d", nb1);
	write(tub1, ent, 5);

	sprintf(ent, "%d", nb2);
	write(tub1, ent, 5);

	read(tub2, ent, 5);
	res = atoi(ent);

	printf("%d\n", res);

	close(tub1);
	close(tub2);
	unlink("tube1");
	unlink("tube2");

	exit(EXIT_SUCCESS);
}
