#include<stdio.h>
#include<stdlib.h>

#include <sys/types.h> //kill
#include <unistd.h> // fork et sleep
#include <signal.h> // signal

#define FAUX 0
#define VRAI 1


char continue_a_travailler;

void graceful_shutdown(int parametre){
  printf("Je termine ce que je fais puis je m'arrête\n");
  continue_a_travailler = FAUX;
}


int main(){
  continue_a_travailler = VRAI;
  signal(SIGINT, graceful_shutdown);

  while(continue_a_travailler){

    printf("Je fais un calcul de la plus haute importance\n");
    sleep(1);
    printf("Je sauvegarde mon résultat\n");
    
  }

  printf("Je libère proprement l'espace mémoire\n");
  printf("Je sauvegarde d'autres informations importantes\n");
  
  return EXIT_SUCCESS;
}
