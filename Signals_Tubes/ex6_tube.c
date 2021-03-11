#include<stdio.h>
#include<stdlib.h>
#include<string.h> //strlen

#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <sys/types.h> //kill
#include <unistd.h> // fork, pipe



int main(){
  int tube[2];
  pid_t qui_suis_je;
  char message[100];
  
  // On crée le tube qui permet au père d'envoyer un message au fils
  if (pipe(tube) == -1) {
    perror("Erreur de création de tube");
    exit(EXIT_FAILURE);
  }

  qui_suis_je = fork();

  if(qui_suis_je == 0){ // Processus Luke
    close(tube[1]); //On ferme le descripteur qui permet d'écrire sur le tube

    read(tube[0], message, 100);
    printf("Luke reçoit le message: %s\n", message);
    printf("Luke dit: NOOOOOOOOOOOOOOOOOOOOOOOOOON\n");
    close(tube[0]); //On ferme le descripteur qui permet de lire sur le tube
  }
  else { // Processus Vador
    close(tube[0]); //On ferme le descripteur qui permet de lire sur le tube

    sprintf(message, "Luke, je suis ton père");
    write(tube[1], message, strlen(message));
    close(tube[1]); //On ferme le descripteur qui permet d'écrire sur le tube
  }
  
  return EXIT_SUCCESS;
}
