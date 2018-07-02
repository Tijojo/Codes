/********************************
 * Fichier named_pipe_writer.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
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

	unlink("my_named_pipe"); // Suppression du tube dsi déjà existant
	
	/* Creation du tube nomme */
	if (mkfifo("my_named_pipe", 0666) == -1) {
		perror("tube probablement déjà existant (on travaille avec ce tube existant)\n");
		exit(EXIT_FAILURE);
	}
	
	// A ce  niveau, si lance la commande ls, on s'appercoit de la creation d'un fichier 
	// my_named_pipe de type fifo dans le repertoire courant

	/* Ouverture du tube pour ecriture */
	tub_nomme = open("my_named_pipe", O_WRONLY);
	if (tub_nomme == -1) {
		perror("Ouverture du tube impossible dans le processus ecrivain\n");
		return 1;
	}

	/* Ecriture dans le tube */
	printf("ecriture de \"Ils ont des chapeaux ronds, vive la Bretagne\"\n");
	write(tub_nomme, "Ils ont des chapeaux ronds, Vive la Bretagne", 44);
	sleep(4);
	printf("ecriture de \"Ils ont des tonneaux ronds, vive les bretons\"\n");
	write(tub_nomme, "Ils ont des tonneaux ronds, Vive les Bretons", 44);

	/* Fermeture du tube */
	close(tub_nomme);

	return 0;
}
