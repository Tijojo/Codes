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
#include <signal.h> // kill

// PROCESSUS SERVEUR

int main(void)
{
  int tube;
  int nb1, nb2, res;
  int res_fifo;
  pid_t pid_client;

  /* 1- MISE EN PLACE DE L'ENVIRONNEMENT POUR COMMUNICATION */
  unlink("tubeBiDirection"); // Supprime le tube si deja existant

  /* Creation des tubes */
  res_fifo = mkfifo("tubeBiDirection", 0666);
  if (res_fifo != 0) {
    perror ("(serveur) Creation du tube de communication impossible ");
    exit(EXIT_FAILURE);
  }
	
  /* Ouverture du tube client vers serveur en lecture */
  tube = open("tubeBiDirection", O_RDWR);
  if (tube == -1){
    perror ("(serveur) Ouverture du tube de communication impossible ");
    exit(EXIT_FAILURE);
  }

  /* 2- TRAITEMENT */
  /* Lecture du pid du processus client */
  read(tube, &pid_client, sizeof(pid_t));
  /* Lecture des nombres a additionner,
     dans le tube client vers serveur */
  read(tube, &nb1, sizeof(int));
  read(tube, &nb2, sizeof(int));
  /* Calcul du résultat */
  res = nb1 + nb2;
  sleep(3); // simule un traitement long, n'effectue aucune synchronisation
  /* Ecriture du resultat dans le tube */
  write(tube, &res, sizeof(int));
  /* Envoie de SIGUSR1 pour prevenir le processus client de la mise 
   a disposition du resultat */
  kill(pid_client,SIGUSR1);

  /* 3- NETTOYAGE DE L'ENVIRONNEMENT DE COMMUNICATION */
  close(tube); // Fermeture du tube

  exit(EXIT_SUCCESS);
}
