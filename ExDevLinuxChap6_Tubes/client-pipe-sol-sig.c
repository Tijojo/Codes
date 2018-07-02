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
#include <unistd.h> // read, write, close, getpid
#include <sys/types.h> // mkfifo
#include <sys/stat.h> // mkfifo

// PROCESSUS CLIENT

void traiteReponse(int numSignal);
  
int tube;

int main(void)
{
  int nb1, nb2;
  pid_t pid_this = getpid();

  /* Ouverture du tube de communication */
  tube = open("tubeBiDirection", O_RDWR);
  if (tube == -1){
    perror ("(client) Ouverture du tube de communication impossible ");
    exit(EXIT_FAILURE);
  }

  /* Nouveau gestionnaire associe a SIGUSR1 */
  if(signal(SIGUSR1,traiteReponse)==SIG_ERR){
    perror ("(client) Affectation gestionnaire de recuperation de reponse ");
    exit(EXIT_FAILURE);
  }

  /* Demande d'entree de l'utilisateur */
  printf("(client) Entrez les nombres de maximum deux nombres a additionner\n");
  scanf("%d %d", &nb1, &nb2);

  /* Envoi des donnees dans le tube pour traitement, commencant par 
     l'envoi du pid pour pouvoir etre prevenu de la mise 
     a disposition du resultat par le serveur */
  write(tube, &pid_this, sizeof(pid_t));
  write(tube, &nb1, sizeof(int));
  write(tube, &nb2, sizeof(int));

  // Mise en attente de la reception d'un signal
  pause();
 
  exit(EXIT_SUCCESS);
}


void traiteReponse(int numSignal)
{
  int res;
  /* Recuperation du resultat du traitement dans le tube */
  read(tube, &res, sizeof(int));
  /* Restitution a l'utilisateur */
  printf("Le resultat est : %d\n", res);

  close(tube);
  unlink("tubeBiDirection");
}
