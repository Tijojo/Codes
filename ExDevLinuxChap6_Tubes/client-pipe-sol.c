/********************************
 * Fichier client-pipe-sol.c
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

// PROCESSUS CLIENT

int main(void)
{
  int tubeOut;
  int tubeIn;
  int nb1, nb2, res;

  /* Ouverture du tube client vers serveur en ecriture */
  tubeOut = open("tubeClientVersServeur", O_WRONLY);
  if (tubeOut == -1){
    perror ("(client) Ouverture du tube client vers serveur impossible ");
    exit(EXIT_FAILURE);
  }

  /* Ouverture du tube serveur vers client en lecture */
  tubeIn = open("tubeServeurVersClient", O_RDONLY);
  if (tubeIn == -1){
    perror ("(client) Ouverture du tube serveur vers client impossible ");
    exit(EXIT_FAILURE);
  }

  /* Demande d'entree de l'utilisateur */
  printf("(client) Entrez les nombres de maximum deux nombres a additionner\n");
  scanf("%d %d", &nb1, &nb2);

  /* Envoi des donnees au serveur pour traitement, 
     dans le tube client vers serveur */
  write(tubeOut, &nb1, sizeof(int));
  write(tubeOut, &nb2, sizeof(int));

  /* Recuperation du resultat du traitement,
     dans le tube serveur vers client */
  read(tubeIn, &res, sizeof(int));
  /* Restitution a l'utilisateur */
  printf("Le resultat est : %d\n", res);

  close(tubeOut);
  close(tubeIn);
  unlink("tubeClientVersServeur");
  unlink("tubeServeurVersClient");

  exit(EXIT_SUCCESS);
}
