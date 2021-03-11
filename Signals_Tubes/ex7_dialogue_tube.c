#include<stdio.h>
#include<stdlib.h>
#include<string.h> //strlen

#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <sys/types.h> //kill
#include <unistd.h> // fork, pipe
#include <signal.h> // signal


void kevin(int ines_a_kevin, int kevin_a_ines){
  char reception[100];
  char * reponse = "Tu veux aller au, chais pas, McDo, Tacos?";
  
  //Kévin écoute le message d'Inès
  read(ines_a_kevin, reception, 100);
  
  printf("Kévin a reçu le message: %s\n", reception);

  //Kévin répond à Inès
  write(kevin_a_ines, reponse, strlen(reponse) +1);

  //Kévin écoute la réponse d'Inès
  read(ines_a_kevin, reception, 100);
  
  printf("Kévin a reçu le message: %s\n", reception);  

  //Kévin clôt la conversation
  close(ines_a_kevin);
  close(kevin_a_ines);
}


void ines(int ines_a_kevin, int kevin_a_ines){
  char reception[100];
  char * message = "Où est-ce qu'on va manger ce soir?";
  char * message2 = "Kévin tu me dégoutes, j'veux des paillettes dans ma vie moi!";
  
  //Inès envoie un premier message à Kévin
  write(ines_a_kevin, message, strlen(message)+1);

  //Inès écoute la réponse
  read(kevin_a_ines, reception, 100);
  
  printf("Inès a reçu le message: %s\n", reception);

  //Inès réponds à Kévin
  write(ines_a_kevin, message2, strlen(message2)+1);

  //Inès clôt la conversation
  close(ines_a_kevin);
  close(kevin_a_ines);
}



int main(){
  int ines_a_kevin[2];
  int kevin_a_ines[2];
  pid_t qui_suis_je;
  
  //On crée les tubes pour permettre aux processus de communiquer
  if (pipe(ines_a_kevin) == -1 || pipe(kevin_a_ines)) {
    perror("Erreur de création de tube");
    exit(EXIT_FAILURE);
  }

  qui_suis_je = fork();

  if(qui_suis_je == 0){
    close(ines_a_kevin[1]); //On ferme le descripteur qui permet d'écrire sur le tube
    close(kevin_a_ines[0]); //On ferme le descripteur qui permet de lire sur le tube
    kevin(ines_a_kevin[0], kevin_a_ines[1]);
  }
  else{
    close(ines_a_kevin[0]); //On ferme le descripteur qui permet de lire sur le tube
    close(kevin_a_ines[1]); //On ferme le descripteur qui permet d'écrire sur le tube
    ines(ines_a_kevin[1], kevin_a_ines[0]);
  }
  
  return EXIT_SUCCESS;
}
