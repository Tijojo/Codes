/********************************
 * Fichier serveur-pipe-sol.c
 * Livre "Exercices corrigés de développement système sous Linux"
 *
 * (c) 2018 P. Alain, J. Chevelu, V. Thion
 *
 ********************************/
#include <stdio.h> // printf, perror
#include <stdlib.h> // EXIT_SUCCESS
#include <fcntl.h> // open, O_WRONLY et O_RONLY
#include <unistd.h> // read, write, close, 
#include <sys/types.h> // mkfifo
#include <sys/stat.h> // mkfifo

// PROCESSUS SERVEUR

int main(void)
{
  int tubeIn;
  int tubeOut;
  int nb1, nb2, res;
  int res_fifo;

  /* 1- MISE EN PLACE DE L'ENVIRONNEMENT POUR COMMUNICATION */
  unlink("tubeClientVersServeur"); // Supprime le tube si deja existant
  unlink("tubeServeurVersClient"); // Supprime le tube si deja existant

  /* Creation des tubes */
  res_fifo = mkfifo("tubeClientVersServeur", 0666);
  if (res_fifo != 0) {
    perror ("(serveur) Creation du tube client vers serveur impossible ");
    exit(EXIT_FAILURE);
  }
	
  res_fifo = mkfifo("tubeServeurVersClient", 0666);
  if (res_fifo != 0) {
    perror ("(serveur) Creation du tube serveur vers client impossible ");
    exit(EXIT_FAILURE);
  }

  /* Ouverture du tube client vers serveur en lecture */
  tubeIn = open("tubeClientVersServeur", O_RDONLY);
  if (tubeIn == -1){
    perror ("(serveur) Ouverture du tube client vers serveur impossible ");
    exit(EXIT_FAILURE);
  }
  /* Ouverture du tube serveur vers client en ecriture */
  tubeOut = open("tubeServeurVersClient", O_WRONLY);
  if (tubeOut == -1){
    perror ("(serveur) Ouverture du tube serveur vers client impossible ");
    exit(EXIT_FAILURE);
  }

  /* 2- TRAITEMENT */
  /* Lecture des nombres a additionner,
     dans le tube client vers serveur */
  read(tubeIn, &nb1, sizeof(int));
  read(tubeIn, &nb2, sizeof(int));
  /* Calcul du résultat */
  res = nb1 + nb2;
  sleep(3); // simule un traitement long, n'effectue aucune synchronisation
  /* Ecriture du resultat, 
     dans le tube serveur vers client */
  write(tubeOut, &res, sizeof(int));

  /* 3- NETTOYAGE DE L'ENVIRONNEMENT DE COMMUNICATION */
  close(tubeIn); // Fermeture des tubes
  close(tubeOut); // Fermeture des tubes

  exit(EXIT_SUCCESS);
}
